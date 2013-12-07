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

static unsigned int time = 0; 

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
        SSPIF = 0; 
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
    //PIR1bits.SSPIF = 0;
    //PIE1bits.SSPIE = 1;

    /* Enable interrupts */
    //INTCONbits.PEIE = 1;
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
