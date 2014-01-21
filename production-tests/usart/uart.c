/**
  * @file uart.c
  * @brief UART functions implementation.
  */

#include <pic18f2520.h>

#include "uart.h"

void uart_send_string(unsigned char str[], unsigned char str_size) {

    unsigned char incr = 0;

    while(incr < str_size) {

        TXREG = str[incr];
        while(!TXIF)
            ;
    }
}

void uart_init(void) {

    TXSTA |= 0x24u;
    RCSTA |= 0x80u;

    /* Select 16-bit mode */
    BAUDCON |= 0x04u;

    SPBRGH = 0;
    SPBRG  = 51u;
}
