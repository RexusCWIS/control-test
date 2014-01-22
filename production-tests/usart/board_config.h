/* 
 * File:   board_config.h
 * Author: olivierdez
 *
 * Created on 17 janvier 2014, 00:47
 */

#ifndef DEF_BOARD_CONFIG_H
#define	DEF_BOARD_CONFIG_H

#include <p18f2520.h>

/** @brief Oscillator frequency, in 1/ms. */
#define OSC_FREQUENCY   ((unsigned int) 8000u)

#define LED1    LATCbits.LATC0
#define LED2    LATCbits.LATC1
#define LED3    LATCbits.LATC5

#define SODS    PORTBbits.RB1
#define SOE     PORTBbits.RB2
#define LO      PORTBbits.RB3

#endif	/* DEF_BOARD_CONFIG_H */

