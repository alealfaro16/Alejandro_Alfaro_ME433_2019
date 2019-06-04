#include "PIC32.h"


void init_pwm(){
    
   //Digital Ouput:
  ANSELAbits.ANSA0 = 0;
  RPA0Rbits.RPA0R = 0b0101; //Set A0 as OC1
  //TRISAbits.TRISA0 = 0;   //initialize pin A0 as a digital output

  //PWM:
  T2CONbits.ON = 1;       // turn Timer3 on, all defaults are fine (1:1 divider, etc.)
  T2CONbits.TCKPS = 0;   // Prescaler 1:1
  PR2 = 1199;       // For a frequency of 20KHz, check if clock frequency is 48MHz
  TMR2 = 0;        // initialize value of Timer2

  OC1CONbits.OCTSEL = 0;  // use Timer2 for OC1
  OC1CONbits.OCM = 0b110; // PWM mode with fault pin disabled
  OC1CONbits.ON = 1;     // Turn OC1 on
  OC1RS = 0;  //For a duty cycle of 25%
  
  //ISR initialization:
  T3CONbits.ON = 1;       // turn Timer3 on, all defaults are fine (1:1 divider, etc.)
  T3CONbits.TCKPS = 0b100;   // Prescaler 1:16
  PR3 = 29999;  //For desired frequency of 100Hz
  TMR3 = 0;
  IPC3bits.T3IP = 6;                // step 4: interrupt priority
  IPC3bits.T3IS = 0;                // step 4: subp is 0, which is the default
  IFS0bits.T3IF = 0;                // step 5: clear Timer3 interrupt flag
  IEC0bits.T3IE = 1;                // step 6: enable Timer3 interrupt
  
}

void __ISR(12, IPL6SOFT) Timer3ISR(void) {
    static int duty_cycle = 0;
    static int count = 0;
    static int bl = 0;
    
    
    count++;
    if(count == 10){
        count = 0;
        bl = 1;        
    } 
    
    if(bl==1){
    duty_cycle =  duty_cycle + 1;
       bl = 0;
   }
    
    if(duty_cycle==10){
        duty_cycle = 0;
    }
  
    OC1RS = (unsigned int) (duty_cycle)*(120);
            
    
    
    //LATAbits.LATA4 = !LATAbits.LATA4;
    
    IFS0bits.T3IF = 0;
}
