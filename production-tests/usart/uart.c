/**
  * @file uart.c
  * @brief UART functions implementation.
  */

#include <pic18f2520.h>

#include "uart.h"

void uart_send_string(unsigned char str[], unsigned char str_size) {

    unsigned char incr = 0;

    while(incr < str_size) {

        while(!TXIF)
            ;
        TXREG = str[incr];
        incr++; 
    }
}

void uart_init(void) {

    SPBRGH = 0;
    SPBRG  = 102u;

    /* Select 16-bit mode */
    BAUDCON = 0x8u;

    /* Configure and start peripheral */
    RCSTA = 0x80u;
    TXSTA = 0x24u;
    
}
