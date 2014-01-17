/**
 * @file timer.c
 * @brief Basic timer configuration functionalities.
 */

#include <p18f2520.h>

#include "board_config.h"
#include "timer.h"


void timer_init(void) {

    /* Set the internal oscillator to 8MHz */
    OSCCON |= 0x70;

    /* Use timer 0 to generate an interrupt each 100 ms */
    T0CONbits.TMR0ON = 0;   /* Disable timer */
    T0CON &= ~0xF8;         /* Set the timer in 16-bit mode */
    T0CON |= 0x3;           /* Set a 1:16 prescaler */

    TMR0H = T0_RELOAD_HIGH;
    TMR0L = T0_RELOAD_LOW;

    T0CONbits.TMR0ON = 1;   /* Restart timer */

    return; 
}
