//#include "i2c_slave.h"
#include "PIC32.h"
#include "i2c_master_noint.h"
// Demonstrate I2C by having the  PIC32 (PIC32MX795F512H) talk to MCP23008 I/O expander
// Master will use SDA2 (B2) and SCL2 (B3). 
// The MCP23008 GP0-GP3 will be intialized as ouputs and GP4-7 as inputs
// GPO will have an LED Circuit while GPO7 will have a pushbutton. Eve
// Everytime GPO7 is low, GPO will be high and turn on the LED
// SDA2 -> SDA
// SCL2 -> SCL
// Two bytes will be written to the slave and then read back to the slave.
// A0,A1,A2 are high
#define SLAVE_ADDR_R 0x4F //Read
#define SLAVE_ADDR_W 0x4E //Write


int main() {
  // some initialization function to set the right speed setting
  unsigned char TRIS_REG = 0x00;
  unsigned char PORT_REG = 0x09;
  unsigned char LAT_REG = 0x0A;

  // some initialization function to set the right speed setting
  PIC32_Startup(); 
  __builtin_disable_interrupts();
  i2c_master_setup();                       // init I2C2, which we use as a master
   initExpander(); //initialize outputs and inputs in I/O expander
  __builtin_enable_interrupts();
  
  while(1) {
     // setExpander(0);
    _CP0_SET_COUNT(0);
    LATAbits.LATA4 = 1;
       if( _CP0_GET_COUNT() > 12000){ //0.5ms
           LATAbits.LATA4 = 0;
           _CP0_SET_COUNT(0);
           while(_CP0_GET_COUNT()<12000){;} //0.5ms
           _CP0_SET_COUNT(0);
      }
    i2c_master_start(); // make the start bit
    i2c_master_send(SLAVE_ADDR_W); // write the address, shifted left by 1, or'ed with a 0 to indicate writing
    i2c_master_send(PORT_REG); // the register to read from
    i2c_master_restart(); // make the restart bit
    i2c_master_send(SLAVE_ADDR_R); // write the address, shifted left by 1, or'ed with a 1 to indicate reading
    char r = i2c_master_recv(); // save the value returned
    i2c_master_ack(1); // make the ack so the slave knows we got it
    i2c_master_stop(); // make the stop bit
    char b = (r>>7);
    //char b = (getExpander()>>7);
    
    if(b == 0){
        //setExpander(0,1);
        i2c_master_start(); // make the start bit
        i2c_master_send(SLAVE_ADDR_W); // address to write
        i2c_master_send(LAT_REG); // the register to LAT
        i2c_master_send(0x01); // | (clear << pin)); // Set desired pin to high
        i2c_master_stop(); // make the stop bit 
    }
    else {
        //setExpander(0,0);
        i2c_master_start(); // make the start bit
        i2c_master_send(SLAVE_ADDR_W); // address to write
        i2c_master_send(LAT_REG); // the register to LAT
        i2c_master_send(0x00); // | (clear << pin)); // Set desired pin to high
        i2c_master_stop(); // make the stop bit 
    } 
    
  }
  return 0;
}
