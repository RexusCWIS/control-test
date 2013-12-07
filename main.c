/* 
 * File:   main.c
 * Author: olivierdez
 *
 * Created on 5 décembre 2013, 18:04
 */

#include <stdio.h>
#include <stdlib.h>
#include <p18f2520.h>

#pragma config OSC = INTIO7
#pragma config WDT = OFF   

/*
 * 
 */
int main(int argc, char** argv) {

    TRISAbits.RA5 = 0;

    PORTAbits.RA5 = 1; 
    return (EXIT_SUCCESS);
}

