#include "PIC32.h"
#include "lcd.h"
#include "motor.h"

void plot_array(int *array,int y_origin,unsigned short color){ //plot array with 240 unsigned chars in LED
    int i;
    
    for(i=0;i<240;i++){
        LCD_drawPixel(i,y_origin - (array[i]>>5)*10, color);
    }
       
}


int main() {
    int array[240];
    int array2[240];
    int array3[240];
    char msg[100];
    int j;
    
    PIC32_Startup();
    SPI1_init();
    LCD_init();
    init_pwm();
    
    for(j=0;j<240;j++)
    {
        if(j>200){
          array[j] = 8<<5;
          array2[j] = 1<<5;
          array3[j] = 2<<5;
          
        }
        else if(j>100){
           array[j] = 5<<5;
           array2[j] = 3<<5;
           array3[j] = 1<<5;
        }
        else{
            array[j] = 0b1<<5;
            array2[j] = 4<<5;
            array3[j] = 8<<5;
        }
    }
    
    LCD_clearScreen(ILI9341_WHITE);
    LCD_printRectangle(0, 210, 240,2,ILI9341_BLACK);
    LCD_printRectangle(0, 110, 240,2,ILI9341_BLACK);
    sprintf(msg,"Red");
    LCD_print(msg,20,20, ILI9341_RED,ILI9341_WHITE );
    sprintf(msg,"Green");
    LCD_print(msg,20,120, ILI9341_GREEN,ILI9341_WHITE );
    sprintf(msg,"Blue");
    LCD_print(msg,20,220, ILI9341_BLUE,ILI9341_WHITE );
    
    
    plot_array(array,310,ILI9341_BLUE);
    plot_array(array2,210,ILI9341_GREEN);
    plot_array(array3,110,ILI9341_RED);
    while(1){
   
    }
            
    return(0);
}


