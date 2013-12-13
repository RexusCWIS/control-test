/**
 * @file i2c_frames.h
 * @brief Defines the first byte of data frames sent over I2C. 
 */

#ifndef DEF_I2C_FRAMES_H
#define DEF_I2C_FRAMES_H

/** @brief Specifies that the data frame contains values acquired by the sensors. */
#define DATA    0x0
/** @brief Specifies that the data frame contains orders to the acquisition board. */
#define ORDER   0xFF

typedef struct {
    unsigned char data[2];
}pressure_data_s;

typedef struct {
    unsigned char data[2]; 
}temperature_data_s; 

typedef enum {
    START_ACQUISITION = 'G', 
    STOP_ACQUISITION  = 'S'
} i2c_order_e; 

/**
 * @brief I2C data frame.
 * @details This frame represents the actual data sent over the I2C bus. 
 *          All data are filled at acquisition time and are read when 
 *          the I2C bus master performs a read operation. 
 */
typedef struct {
    int time;                               /**< @brief Time at which data acquisition occured. */
    temperature_data_s temperatures[3];     /**< @brief Temperature sensors data. */
    pressure_data_s pressure;               /**< @brief Pressure sensor data. */
    unsigned char status[2];                /**< @brief Control module status. */
} i2c_frame_s; 

#endif  /* DEF_I2C_FRAMES_H */

