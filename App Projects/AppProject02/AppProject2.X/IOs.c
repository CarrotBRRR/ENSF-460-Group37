#include <p24F16KA101.h>
#include "xc.h"
#include "IOs.h"

extern uint8_t PB1_flag;
extern uint8_t PB2_flag;

void IOinit(){
   //Clock output on REFO pin - pin 18 RB15
   TRISBbits.TRISB15 = 0;  // Set RB15 as output for REFO
   REFOCONbits.ROEN = 1; // Ref oscillator is enabled
   REFOCONbits.ROSSLP = 0; // Ref oscillator is disabled in sleep
   REFOCONbits.ROSEL = 0; // Output base clk showing clock switching
   REFOCONbits.RODIV = 0b0000;
    
   AD1PCFG=0xFFFF; //Set all bits as digital
   TRISAbits.TRISA3 = 1;  //Set pin8/RA3/AN5 as input
    AD1PCFGbits.PCFG5 = 0; 	//Set only pin8/AN5/RA3 as Analog input for ADC
       
    CNPU2bits.CN30PUE = 1; // Enables pull up resistor on RA2/CN30 butt 1
    CNPU1bits.CN1PUE = 1; // Enables pull up resistor on RB4/CN1 butt 2
//    CNPU1bits.CN0PUE = 1; // Enables pull up resistor on RA4/CN0 butt 3
    
    TRISAbits.TRISA2 = 1; // Butt 1
    TRISBbits.TRISB4 = 1; // Butt 2
//    TRISAbits.TRISA4 = 1; // Butt 3
            
    TRISBbits.TRISB8 = 0; // LED
    
    CNEN2bits.CN30IE = 1; // CN30 RA2
    CNEN1bits.CN1IE = 1;  // CN1  RB4
//    CNEN1bits.CN0IE = 1;  // CN0  RA4

    IPC4bits.CNIP = 6;    // 7 is highest priority, 0 is disabled
    IFS1bits.CNIF = 0;    // Clear Interrupt Flag
    IEC1bits.CNIE = 1;    // Enables CN Interrupts
}

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void)
{   
    // Interrupt flags
    if (IFS1bits.CNIF == 1)
    {
        // If Button 1 is pressed
        if (PORTAbits.RA2 == 0) 
        {
            PB1_flag = !PB1_flag;
            PB2_flag = 0;
        } 
        // If Button 2 is pressed
        else if (PORTBbits.RB4 == 0) 
        {
            PB2_flag = !PB2_flag;
            PB1_flag = 0;
        }
    }
    
    IFS1bits.CNIF = 0;
    return;
}