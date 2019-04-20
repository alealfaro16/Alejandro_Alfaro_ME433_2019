#include "PIC32.h"  
#include "ili9341.h"

//#define ILI9341_GREEN   0x07E0

int main(){
    
    //Initializations
    PIC32_Startup();
    SPI1_init();
    LCD_init();
    int i = 0; 
    char m[100];
    int time1;
    int time2;
   
    
    LCD_clearScreen(ILI9341_WHITE);
    sprintf(m,"Hello World!");
    LCD_print(m,28,32,ILI9341_BLACK,ILI9341_WHITE);
    LCD_printRectangle(20,50,100,10,ILI9341_WHITE);
 
    while(1){
        time1 = _CP0_GET_COUNT();
        int k = i%100;
        sprintf(m,"%d",k);
        LCD_print(m,90,32,ILI9341_BLACK,ILI9341_WHITE);
        LCD_printRectangle(20+k,50,1,10,ILI9341_GREEN);
        
        if(k==0){
         LCD_printRectangle(20,50,100,10,ILI9341_WHITE);   
        }
        
        
        int t1 =_CP0_GET_COUNT();
        while(_CP0_GET_COUNT()-t1<2400000){;} //100ms
        
        time2 = _CP0_GET_COUNT();
        float fps = 24000000/(time2-time1);
        sprintf(m,"FPS: %3.2f",fps);
        LCD_print(m,90,100,ILI9341_BLACK,ILI9341_WHITE);
        i++;
    }
    
    return 0;
}
