/* 
 * File:   i2c_slave.h
 * Author: olivierdez
 *
 * Created on 7 décembre 2013, 18:59
 */

#ifndef I2C_SLAVE_H
#define	I2C_SLAVE_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef enum {
        I2C_SET_DEV_REG,
        I2C_DATA
    }i2c_state_machine_e;

    /**
     * @brief Initializes the microcontroller as a I2C slave.
     * @param id    ID on the I2C bus. 
     */
    void i2c_slave_init(unsigned char id);




#ifdef	__cplusplus
}
#endif

#endif	/* I2C_SLAVE_H */

