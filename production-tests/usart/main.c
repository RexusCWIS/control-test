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

/** @brief Time, in multiples of 100-ms. */
static unsigned int time = 0;
static unsigned char led_cntr = 0;

static unsigned char boot_msg[62] = "This is the CWIS control module. Starting functional tests...\0";

static inline void board_config(void); 

void main(void) {

    board_config(); 
    uart_init();
    timer_init();

    //uart_send_string(boot_msg, 62u);

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

/**
 * @brief Configures the MCU according to the board layout.
 * @details Sets I/O states and configure interruptions. 
 */
static inline void board_config(void) {

    /* Set LED pads as outputs */
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC5 = 0;

    /* Enable timer interrupts */
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;

    /* Enable interrupts */
    INTCONbits.PEIE = 1;
    ei();
}
