/* 
 * File:   i2c_slave.h
 * Author: olivierdez
 *
 * Created on 7 décembre 2013, 18:59
 */

#ifndef I2C_SLAVE_H
#define	I2C_SLAVE_H

/* Awful include directive due to the fact that the editor can't fnd the file */
#include "/Applications/microchip/xc8/v1.21/include/plib/i2c.h"

#ifdef	__cplusplus
extern "C" {
#endif

    /**
     * @brief Initializes the microcontroller as a I2C slave.
     * @param id    ID on the I2C bus. 
     */
    void i2c_slave_init(unsigned int id);




#ifdef	__cplusplus
}
#endif

#endif	/* I2C_SLAVE_H */

