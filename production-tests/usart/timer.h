/* 
 * File:   timer.h
 * Author: olivierdez
 *
 * Created on 17 janvier 2014, 01:16
 */

#ifndef DEF_TIMER_H
#define	DEF_TIMER_H

/* Timer 0 reload values for a 100-ms tick. */
#define T0_RELOAD_HIGH  0x3Cu
#define T0_RELOAD_LOW   0xAFu

void timer_init(void); 

#endif	/* DEF_TIMER_H */

