/**
  * @file uart.c
  * @brief UART functions implementation.
  */

#include <pic18f2520.h>

#include "uart.h"

void uart_send_data(unsigned char data[], unsigned char data_size) {

    unsigned char incr = 0;

    while(incr < data_size) {

        while(!TXIF)
            ;
        TXREG = data[incr];
        incr++; 
    }
}

void uart_init(void) {

    SPBRGH = 0;
    SPBRG  = 51u;

    /* Select 16-bit mode */
    BAUDCON = 0x8u;

    /* Configure and start peripheral */
    RCSTA = 0x80u;
    TXSTA = 0x24u;
    
}
