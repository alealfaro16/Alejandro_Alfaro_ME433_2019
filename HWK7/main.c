//#include "i2c_slave.h"
#include "lcd.h"
#include "imu.h"
#include "PIC32.h"
#include "i2c_master_noint.h"
// Get the IMU working and use the LCD to show movement
// Master will use SDA2 (B2) and SCL2 (B3). 
// SDA2 -> SDA
// SCL2 -> SCL
// Two bytes will be written to the slave and then read back to the slave.
// A0,A1,A2 are high
#define CS LATBbits.LATB7


int main() {
 // some initialization function to set the right speed setting
    unsigned char data[14];
    short real_data[7];
    int i;
    unsigned char check;
    char m1[100];
    char m2[100];
    
    //initializations
    __builtin_disable_interrupts();
    PIC32_Startup(); 
    SPI1_init();
    LCD_init();
    i2c_master_setup(); // init I2C2, which we use as a master
    initIMU();
    __builtin_enable_interrupts();
    
    
    LCD_clearScreen(ILI9341_WHITE);
    LCD_printRectangle(0, 160, 240,10,ILI9341_BLACK);
    LCD_printRectangle(110, 0, 10,320,ILI9341_BLACK);
            
  
  while(1){
      
      LCD_printRectangle(0, 160, 240,10,ILI9341_BLACK);
      LCD_printRectangle(110, 0, 10,320,ILI9341_BLACK);
      //i2c_master_start(); // make the start bit
      //i2c_master_send(SLAVE_ADDR_W); // address to write
      //i2c_master_send(OUT_TEMP_L); // the register to TRIS
      //i2c_master_restart();
      //i2c_master_send(SLAVE_ADDR_R); //address to read
      //check = i2c_master_recv();
      //i2c_master_ack(1);    
      //i2c_master_stop();
      
      
     
      
      I2C_read_multiple(SLAVE_ADDR, OUT_TEMP_L, data , 14);
      for(i=0;i<7;i++){ //Combine 14 8bit bytes into 7 16bits shorts
          real_data[i] = (data[i*2+1] << 8) | data[i*2];
      }
     
      sprintf(m1,"AX = %d   AY = %d ",  real_data[4],real_data[5]);
      LCD_print(m1,0,32,ILI9341_BLACK,ILI9341_WHITE);
      
      //Horizontal rectangle
      if(real_data[4]<0){
          LCD_printRectangle(110, 160, 3*(real_data[4]-500)/-400,10,ILI9341_GREEN);
      }
      else{
          LCD_printRectangle(120-(3*(real_data[4]-500)/400),160,3*(real_data[4]-500)/400,10,ILI9341_GREEN);
      }
      
   
      //Vertical rectangle
      if(real_data[5]<0){
          LCD_printRectangle(110, 160, 10,(real_data[5]-500)/-100,ILI9341_GREEN);
      }
      else{
          LCD_printRectangle(110, 160-((real_data[5]-500)/100),10,((real_data[5]-500)/100),ILI9341_GREEN);
      }
      
      _CP0_SET_COUNT(0);
     LATAbits.LATA4 = 1;
     while( _CP0_GET_COUNT()< 600000){;} //25ms
     LATAbits.LATA4 = 0;
     _CP0_SET_COUNT(0);
     while(_CP0_GET_COUNT()<600000){;} //25ms

      
  }
  return(0);
}
