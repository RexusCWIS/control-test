#include <p18f2520.h>
#include "i2c_slave.h"


void i2c_slave_init(unsigned char id) {

    SSPSTAT = 0x80;     /* Deactivate slew control */
    SSPCON1 = 0x36;     /* Enable serial port, I2C slave mode, 7-bit address */

    SSPCON2bits.SEN  = 1;   /* Enable clock stretching */

    SSPADD = id;            /* Set address on the I2C bus */
}
