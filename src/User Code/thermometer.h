/*******************************************************************************
* File:     	thermometer.h
* Brief:    	Header file for thermometer.c
* Author: 		Krzysztof Koch
* Version:		V1.00
* Date created:	15/02/2017
* Last mod: 	09/03/2017
*
* Note: 
*******************************************************************************/
#include "KrisOS.h"



/*-------------------------------------------------------------------------------
* Start conditions - they control whether the I2C START condition is 
* generated for the current byte transmitted. Start condition pulls the SDA
* line low and then the SCL line low
--------------------------------------------------------------------------------*/
typedef enum {
	START,
	CONTINUED,
} StartCond;



/*-------------------------------------------------------------------------------
* Stop conditions - they control whether the I2C STOP condition is 
* generated for the current byte transmitted. Stop condition releases the SCL
* then SDA. (requires the use of pull-up resistors)
--------------------------------------------------------------------------------*/
typedef enum {
	STOP,
	CONTINUE,
} StopCond;



/*-------------------------------------------------------------------------------
* Number of temperature values to average before displaying the temperature on
* the LCD screen
--------------------------------------------------------------------------------*/
#define TEMP_AVERAG_SAMPLE_NO 20



/*-------------------------------------------------------------------------------
* Number of temperature readings the intertask queue can fit
--------------------------------------------------------------------------------*/
#define THERMOMETER_QUEUE_SIZE 5



/*-------------------------------------------------------------------------------
* Temperature conversion delay
--------------------------------------------------------------------------------*/
#define TEMPERATURE_CONVERSION_DELAY 1250



/*-------------------------------------------------------------------------------
* Function:    	i2c_init
* Purpose:    	Configure the I2C Module as Master with 100kb/s transmission rate.
* Arguments:	-
* Returns: 		-	
--------------------------------------------------------------------------------*/
void i2c_init(void);



/*-------------------------------------------------------------------------------
* Function:    	i2c_slave_addr
* Purpose:    	Set the slave address for the following I2C communication.
* Arguments:
*		address - slave address (7bit)
* Returns: 		-	
--------------------------------------------------------------------------------*/
void i2c_slave_addr(uint8_t address);



/*-------------------------------------------------------------------------------
* Function:    	i2c_write
* Purpose:    	Send a byte of data to the current slave. 
* Arguments:
*		data - data to send (1 byte)
*		start - controls the generation of START condition
*		stop - controls the generation of STOP condition
* Returns: 
*		EXIT STATUS
--------------------------------------------------------------------------------*/
uint32_t i2c_write(uint8_t data, StartCond start, StopCond stop);



/*-------------------------------------------------------------------------------
* Function:    	i2c_read
* Purpose:    	Receive a byte of data from the current slave. 
* Arguments:
*		start - controls the generation of START condition
*		stop - controls the generation of STOP condition
* Returns: 
*		EXIT STATUS
--------------------------------------------------------------------------------*/
uint8_t i2c_read(StartCond start, StopCond stop);

