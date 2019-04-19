#include "io_expander.h"
#define SLAVE_ADDR_R 0x4F //Read
#define SLAVE_ADDR_W 0x4E //Write

unsigned char TRIS_REG = 0x00;
unsigned char PORT_REG = 0x09;
unsigned char LAT_REG = 0x0A;
    
void initExpander(){
    
    //Set inputs and ouputs
    i2c_master_start(); // make the start bit
    i2c_master_send(SLAVE_ADDR_W); // address to write
    i2c_master_send(TRIS_REG); // the register to TRIS
    i2c_master_send(0xF0); // Set GP0-3 to outputs and GP4-7 to inputs
    i2c_master_stop(); // make the stop bit      
}

void setExpander(char pin, char clear){
    unsigned char LAT_REG = 0x0A;
    i2c_master_start(); // make the start bit
    i2c_master_send(SLAVE_ADDR_W); // address to write
    i2c_master_send(LAT_REG); // the register to LAT
    i2c_master_send(0x00 | (clear << pin)); // Set desired pin to high
    i2c_master_stop(); // make the stop bit 
}
char getExpander(){
    
    i2c_master_start(); // make the start bit
    i2c_master_send(SLAVE_ADDR_W); // write the address, shifted left by 1, or'ed with a 0 to indicate writing
    i2c_master_send(PORT_REG); // the register to read from
    i2c_master_restart(); // make the restart bit
    i2c_master_send(SLAVE_ADDR_R); // write the address, shifted left by 1, or'ed with a 1 to indicate reading
    char r = i2c_master_recv(); // save the value returned
    i2c_master_ack(1); // make the ack so the slave knows we got it
    i2c_master_stop(); // make the stop bit
    return r;
}
