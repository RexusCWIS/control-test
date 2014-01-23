/**
 * @file main.c
 * @brief USART production test.
 * @details This test prompts a message using the USART serial line
 *          of the CWIS experiment. A timer flashes the 3 software controlled
 *          LEDs at a
 */

#include <p18f2520.h>

#include "board_config.h"
#include "timer.h"
#include "uart.h"

#pragma config OSC = INTIO7
#pragma config WDT = OFF   

static test_state_e current_state = RXSM_SIGNALS;

/** @brief Time, in multiples of 100-ms. */
static unsigned int time = 0;
static unsigned char led_cntr = 0;

static unsigned char boot_msg[68] = "\n\rThis is the CWIS control module. Starting functional tests...\n\r\n\r\0";


static inline void board_config(void); 

void main(void) {

    unsigned char flags = 0; 

    board_config(); 
    timer_init();
    uart_init();

    uart_send_data(boot_msg, sizeof(boot_msg));

    while(flags != 0x7) {

        if(LO == 1) {
            flags |= 0x1; 
            LED3  ^= 1;
        }

        if(SODS == 1) {
            flags |= 0x2;
            LED2  ^= 1;
        }

        if(SOE == 1) {
            flags |= 0x4;
            LED1  ^= 1;
        }
    }

    current_state = LASER_POWER;

    LASER = 1; 

    while(1)
        ;
}

void interrupt isr(void) {

    if(TMR0IF) {
        /* Restart timer 0 */
        TMR0H = T0_RELOAD_HIGH;
        TMR0L = T0_RELOAD_LOW;
        TMR0IF = 0;
        
        time++;
        led_cntr++;
        
        if(led_cntr > 10u) {
            led_cntr = 0; 
        }

        if(current_state != RXSM_SIGNALS) {
            switch(led_cntr) {

                case 0:
                    LED1 = ~LED1;
                    LED2 = ~LED2;
                    LED3 = ~LED3;
                    break;

                case 2:
                    LED1 = ~LED1;
                    break;

                case 4:
                    LED1 = ~LED1;
                    break;

                case 5:
                    LED2 = ~LED2;
                    break;

                case 6:
                    LED1 = ~LED1;
                    break;

                case 8:
                    LED1 = ~LED1;

                default:
                    break;
            }
        }
    }
}

/**
 * @brief Configures the MCU according to the board layout.
 * @details Sets I/O states and configure interruptions. 
 */
static inline void board_config(void) {

    /* Set LO, SODS and SOE pads as inputs */
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;
    TRISBbits.TRISB3 = 1;

    /* Switch off laser and set pad as output */
    LASER = 0; 
    TRISBbits.TRISB4 = 0; 

    /* Set LED pads as outputs */
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC5 = 0;

    /* ADC configuration */

    /* Set V3 as +REF (1V), set analog input channels ( last 0b00011100) */
    ADCON1 = 0b00011010;
    
    /* Set bits right shifted, acquisition time 16 Tad = 64us,
     * conversion clock Fosc/16 = 4us (default 100 Fosc/4) */
    ADCON2 = 0b10110101;


    /* Enable timer interrupts */
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;

    /* Enable interrupts */
    INTCONbits.PEIE = 1;
    ei();
}
