#include "PIC32.h"  
#include "lcd.h"


int main(){
    
    int i = 0; 
    char m[100];
    unsigned short x,y, xr, yr; 
    int z = 0; 
    
    __builtin_disable_interrupts();
    PIC32_Startup();
    SPI1_init();
    LCD_init();
    __builtin_enable_interrupts();
    
    LCD_clearScreen(ILI9341_WHITE);
    sprintf(m,"Hello World!");
    LCD_print(m,28,32,ILI9341_BLACK,ILI9341_WHITE);
    LCD_printRectangle(20,50,100,10,ILI9341_GREEN);
    LCD_printRectangle(95,150,50,50,ILI9341_GREEN);
    LCD_printRectangle(95,240,50,50,ILI9341_GREEN);
    sprintf(m,"i+");
    LCD_print(m,115,175,ILI9341_BLACK,ILI9341_WHITE);
    sprintf(m,"i-");
    LCD_print(m,115,265,ILI9341_BLACK,ILI9341_WHITE);
   
    while(1){
        
        
        XPT2046_read(&xr, &yr, &z);
        if(z<1000){
            x = 0;
            y = 0;
        }
        else{
            x = (xr-511)/14;
            y = (3900-yr)/11;
        }
        
        if(100<x & x<150 & 150<y & y<200){
            i++;
        }
        
        if(100<x & x<150 & 240<y & y<290){
            i--;
        }
        
        sprintf(m,"Raw values are: %d  %d  %d  ",xr,yr,z);
        LCD_print(m,10,100,ILI9341_BLACK,ILI9341_WHITE);
        
        sprintf(m,"TS values are: %d  %d  ",x,y);
        LCD_print(m,10,120,ILI9341_BLACK,ILI9341_WHITE);
        
        sprintf(m,"i = %d ",i);
        LCD_print(m,115,215,ILI9341_BLACK,ILI9341_WHITE);
        
        int t1 =_CP0_GET_COUNT();
        while(_CP0_GET_COUNT()-t1<2400000){;} //100ms
        
    }
    
    return(0);
}
