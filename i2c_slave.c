#include "i2c_slave.h"

unsigned char I2C_Send[21] = "MICROCHIP:I2C_SLAVE" ;
unsigned char I2C_Recv[21];

void i2c_slave_init(unsigned int id) {

    unsigned char temp = 0;
    unsigned char length = 0; 

    /* Close the I2C device in case it was previously operating */
    CloseI2C();

    OpenI2C(SLAVE_7, SLEW_OFF);

    SSPADD = 0x42;							//initialze slave address
//********************* Read the address sent by master from buffer **************
		while(DataRdyI2C()==0);			//WAIT UNTILL THE DATA IS TRANSMITTED FROM master
		temp = ReadI2C();


//********************* Data reception from master by slave *********************

		do
		{
		while(DataRdyI2C()==0);			//WAIT UNTILL THE DATA IS TRANSMITTED FROM master
		I2C_Recv[length++]=getcI2C();       // save byte received
		}
		while(length!=20);

//******************** write sequence from slave *******************************
		while(SSPSTATbits.S!=1);		//wait untill STOP CONDITION

//********************* Read the address sent by master from buffer **************
		while(DataRdyI2C()==0);			//WAIT UNTILL THE DATA IS TRANSMITTED FROM master
		temp = ReadI2C();

//********************* Slave transmission ************************************
	if(SSPSTAT & 0x04)					//check if master is ready for reception
	while(putsI2C(I2C_Send));			// send the data to master

//-------------TERMINATE COMMUNICATION FROM MASTER SIDE---------------
	CloseI2C();							//close I2C module
}
