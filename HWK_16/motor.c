#include "motor.h"

void init_pwm(){
    
   //Digital Ouput:
  //ANSELAbits.ANSA0 = 0;
  RPB15Rbits.RPB15R = 0b0101; //Set B15 as OC1
  //TRISAbits.TRISA0 = 0;   //initialize pin A0 as a digital output

  //PWM:
  T3CONbits.ON = 1;       // turn Timer3 on, all defaults are fine (1:1 divider, etc.)
  T3CONbits.TCKPS = 0;   // Prescaler 1:1
  PR2 = 1199;       // For a frequency of 20KHz, check if clock frequency is 48MHz
  TMR2 = 0;        // initialize value of Timer2

  OC1CONbits.OCTSEL = 1;  // use Timer3 for OC1
  OC1CONbits.OCM = 0b110; // PWM mode with fault pin disabled
  OC1CONbits.ON = 1;     // Turn OC1 on
  OC1RS = 300;  //For a duty cycle of 25%
  
  //ISR initialization:
  //T3CONbits.ON = 1;       // turn Timer3 on, all defaults are fine (1:1 divider, etc.)
  //T3CONbits.TCKPS = 0b100;   // Prescaler 1:16
  //PR3 = 29999;  //For desired frequency of 100Hz
  //TMR3 = 0;
  //IPC3bits.T3IP = 6;                // step 4: interrupt priority
  //IPC3bits.T3IS = 0;                // step 4: subp is 0, which is the default
  //IFS0bits.T3IF = 0;                // step 5: clear Timer3 interrupt flag
  //IEC0bits.T3IE = 1;                // step 6: enable Timer3 interrupt
  //*
}


