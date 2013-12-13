/* 
 * File:   main.c
 * Author: olivierdez
 *
 * Created on 5 décembre 2013, 18:04
 */

#include <stdio.h>
#include <stdlib.h>
#include <p18f2520.h>

#include "i2c_slave.h"

#pragma config OSC = INTIO7
#pragma config WDT = OFF   

#define T0_RELOAD_HIGH  0xE1u
#define T0_RELOAD_LOW   0x7Bu

#define I2C_RX_FRAME_SIZE   32u
#define I2C_TX_FRAME_SIZE   32u

#define I2C_ADDRESS 0x22u

static unsigned int time   = 0;
static unsigned char dummy = 0;
static unsigned int i2c_index  = 0;
static unsigned char i2c_register = 0;

static unsigned char i2c_rx_frame[I2C_RX_FRAME_SIZE]; 
static unsigned char i2c_tx_frame[I2C_TX_FRAME_SIZE];

static unsigned char* i2c_rx_registers[1] = {i2c_rx_frame};
static unsigned char* i2c_tx_registers[2] = {i2c_tx_frame, i2c_rx_frame};

static i2c_write_state_e i2c_write_state; 

void interrupt generic_isr(void) {

    /* Timer 0 interrupt */
    if(TMR0IF) {
        time++;
        LATA5 = ~LATA5;
        TMR0H = T0_RELOAD_HIGH;
        TMR0L = T0_RELOAD_LOW;
        TMR0IF = 0;
    }

    /* I2C interrupt */
    if(SSPIF) {
        /* Master READ */
        if(SSPSTATbits.R_nW) {

            /* Last byte was a memory address */
            if(!SSPSTATbits.D_nA) {

                i2c_index = 0u;                     /* Clear index */
                SSPBUF = i2c_rx_frame[i2c_index];   /* Send first byte */
                i2c_index++;
                SSPCON1bits.CKP = 1;    /* Release I2C clock */
            }

            /* Last byte was data (the slave is transmitting the frame) */
            if(SSPSTATbits.D_nA) {

                if(i2c_index < I2C_TX_FRAME_SIZE) {
                    SSPBUF = i2c_rx_frame[i2c_index];
                    i2c_index++; 
                }

                /* If we're done transmitting the frame, empty the I2C buffer */
                else {
                    dummy = SSPBUF; 
                }

                SSPCON1bits.CKP = 1;    /* Release I2C clock */
            }
        }

        /* Master WRITE */
        if(!SSPSTATbits.R_nW) {

            /* Last byte was a memory address */
            if(!SSPSTATbits.D_nA) {
                dummy = SSPBUF;         /* Clear I2C buffer */
                i2c_write_state = I2C_WRITE_SET_REG; 
                SSPCON1bits.CKP = 1;    /* Release I2C clock */
            }

            if(SSPSTATbits.D_nA) {

                if(i2c_write_state == I2C_WRITE_SET_REG) {
                    i2c_register = SSPBUF;
                    i2c_index = 0;
                    i2c_write_state = I2C_WRITE_DATA; 
                }

                else {
                    if(i2c_index < I2C_RX_FRAME_SIZE) {
                        i2c_rx_registers[i2c_register][i2c_index] = SSPBUF;
                        i2c_index++;
                    }

                    else {
                        dummy = SSPBUF;     /* Clear I2C buffer */
                    }
                }
                
                /* Write collision handling */
                if(SSPCON1bits.WCOL) {
                    SSPCON1bits.WCOL = 0;   /* Clear collision flag */
                    dummy = SSPBUF;         /* Clear I2C buffer */
                }

                SSPCON1bits.CKP = 1;        /* Release I2C clock */
            }
        }

        SSPIF = 0; 
    }

    /* I2C Bus collision interrupt */
    if(BCLIF) {

        dummy = SSPBUF;         /* Clear I2C buffer */
        BCLIF = 0;              /* Clear bus collision flag */
        SSPCON1bits.CKP = 1;    /* Release I2C clock */
        SSPIF = 0;              /* Clear I2C interrupt flag */
    }
}

/**
 * @brief Configures the microcontroller according to the board specifications.  
 */
static void board_config(void);
static void timer_init(void); 

/*
 * 
 */
int main(int argc, char** argv) {

    for(unsigned int incr = 0; incr < I2C_RX_FRAME_SIZE; incr++) {
        i2c_rx_frame[incr] = 6u;
    }

    i2c_slave_init(I2C_ADDRESS);
    timer_init(); 
    board_config();

    //PORTAbits.RA5 = 1;

    //i2c_slave_init(42);

    while(1)
        ;
    
    return (EXIT_SUCCESS);
}


static void board_config(void) {

    /* Sets RA5 as an output for the system LED */
    TRISAbits.RA5 = 0;

    /* I2C I/O configuration */
    TRISCbits.RC3 = 1;      /* SCL set as input */
    TRISCbits.RC4 = 1;      /* SDA set as input */

    /* Enable timer and I2C interrupts */
    INTCONbits.TMR0IF = 0; 
    INTCONbits.TMR0IE = 1;
    PIR1bits.SSPIF = 0;
    PIE1bits.SSPIE = 1;

    /* Enable interrupts */
    INTCONbits.PEIE = 1;
    ei();
}

static void timer_init(void) {

    /* Set the internal oscillator to 8MHz */
    OSCCON |= 0x70; 

    /* Use timer 0 to generate an interrupt each second */
    T0CONbits.TMR0ON = 0;   /* Disable timer */
    T0CON &= ~0xF8;         /* Set the timer in 16-bit mode */
    T0CON |= 0x7;           /* Set a 1:256 prescaler */

    TMR0H = T0_RELOAD_HIGH;
    TMR0L = T0_RELOAD_LOW;

    T0CONbits.TMR0ON = 1;   /* Restart timer */
}
