

// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "lcd.h"
#include "imu.h"
#include "PIC32.h"
#include "i2c_master_noint.h"
#define CS LATBbits.LATB7

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;
    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
    
    PIC32_Startup();
    SPI1_init();
    LCD_init();
    i2c_master_setup(); // init I2C2, which we use as a master
    initIMU();
    
    
    LCD_clearScreen(ILI9341_WHITE);
    LCD_printRectangle(0, 160, 240,10,ILI9341_BLACK);
    LCD_printRectangle(110, 0, 10,320,ILI9341_BLACK);
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            bool appInitialized = true;
            
       
        
            if (appInitialized)
            {
            
                appData.state = APP_STATE_SERVICE_TASKS;
            }
            break;
        }

        case APP_STATE_SERVICE_TASKS:
        {
            
            unsigned char data[14];
            short real_data[7];
            int i;
            unsigned char check;
            char m1[100];
            char m2[100];
            LCD_printRectangle(0, 160, 240,10,ILI9341_BLACK);
            LCD_printRectangle(110, 0, 10,320,ILI9341_BLACK);

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

        /* TODO: implement your application state machine.*/
        

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}
