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

/* LED pads */
#define LED1    LATCbits.LATC0
#define LED2    LATCbits.LATC1
#define LED3    LATCbits.LATC5

/* RXSM input signals */
#define SODS    PORTBbits.RB1
#define SOE     PORTBbits.RB2
#define LO      PORTBbits.RB3

/* Laser control pad */
#define LASER   LATBbits.LATB4

typedef enum {
    RXSM_SIGNALS = 1,
    LASER_POWER = 2,
    DOWNLINK = 3,
    ANALOG_SENSORS = 4


} test_state_e;

#endif	/* DEF_BOARD_CONFIG_H */

