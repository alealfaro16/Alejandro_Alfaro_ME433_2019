#include "imu.h"

void initIMU(void){
    //Initialize CTRL1_XL and set sample rate to 1.66kHz
    //with 2g sensitivity and 100Hz filter
    //Initialize CTRL2_G and set sample rate to 1.66kHz 
    //with 1000 dps sensitivity
    //Initialize CTRL3_C and turn on IF_INC on
    
    //CTRL1_XL:
    i2c_master_start(); // make the start bit
    i2c_master_send(SLAVE_ADDR_W); // address to write
    i2c_master_send(CTRL1_XL); // the register to TRIS
    i2c_master_send(0b10000010); // Settings 0b1000 for 1000dps, 00 for 2g sensitivity and 10 for 100Hz filter
    i2c_master_stop(); // make the stop bit
    
    //CTRL2_G:
    i2c_master_start(); // make the start bit
    i2c_master_send(SLAVE_ADDR_W); // address to write
    i2c_master_send(CTRL2_G); // the register to TRIS
    i2c_master_send(0b10001000); // Settings - Gyroscope full-scale at 125dps disabled
    i2c_master_stop(); // make the stop bit 
    
    //CTRL3_C:
    i2c_master_start(); // make the start bit
    i2c_master_send(SLAVE_ADDR_W); // address to write
    i2c_master_send(CTRL3_C); // the register to TRIS
    i2c_master_send(0b00000100); // Settings - 
    i2c_master_stop(); // make the stop bit 
}

void I2C_read_multiple(unsigned char address, unsigned char reg, unsigned char * data, int length){
    //Function will read from OUT_TEMP_L to OUTZ_H_XL (14 bytes)
    //Then combine them into 7 16 bit shorts
    int i;
    i2c_master_start(); // make the start bit
    i2c_master_send(address<<1); // address to write
    i2c_master_send(reg); // the register
    i2c_master_restart();
    i2c_master_send((address<<1)|0b1); //address to read
    
    for(i=0;i<length-1;i++){
        *(data+i) = i2c_master_recv();
        i2c_master_ack(0);
    }
    *(data+length-1) = i2c_master_recv();
    i2c_master_ack(1);    
    i2c_master_stop();
   
    
}
