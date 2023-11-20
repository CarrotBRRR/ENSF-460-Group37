#include <p24F16KA101.h>
#include "xc.h"
#include "IOs.h"

void IOinit(){
    //Clock output on REFO pin - pin 18 RB15
    TRISBbits.TRISB15 = 0;  // Set RB15 as output for REFO
    REFOCONbits.ROEN = 1; // Ref oscillator is enabled
    REFOCONbits.ROSSLP = 0; // Ref oscillator is disabled in sleep
    REFOCONbits.ROSEL = 0; // Output base clk showing clock switching
    REFOCONbits.RODIV = 0b0000;
    
    // IO Initializations
    AD1PCFG = 0xFFFF;  // Turn all analog pins to digital
    
    TRISAbits.TRISA3 = 1;
//    IPC3bits.AD1IP = 6;
//    IFS0bits.AD1IF = 0;
//    IEC0bits.AD1IE = 1;
    
    // CNPU2bits.CN30PUE = 1; // Enables pull up resistor on RA2/CN30 butt 1
    // CNPU1bits.CN1PUE = 1; // Enables pull up resistor on RB4/CN1 butt 2
    // CNPU1bits.CN0PUE = 1; // Enables pull up resistor on RA4/CN0 butt 3
    
    // TRISAbits.TRISA2 = 1; // Butt 1
    // TRISBbits.TRISB4 = 1; // Butt 2
    // TRISAbits.TRISA4 = 1; // Butt 3
            
    // TRISBbits.TRISB8 = 0; // LED
    
    // CNEN2bits.CN30IE = 1; // CN30 RA2
    // CNEN1bits.CN1IE = 1;  // CN1  RB4
    // CNEN1bits.CN0IE = 1;  // CN0  RA4

    // IPC4bits.CNIP = 6;    // 7 is highest priority, 0 is disabled
    // IFS1bits.CNIF = 0;    // Clear Interrupt Flag
    // IEC1bits.CNIE = 1;    // Enables CN Interrupts
}

uint8_t IOcheck() { 
    uint8_t input = 0;

    if(PORTAbits.RA2 == 0){             // button 1
        input = input | 0b0001;
    }
    if(PORTBbits.RB4 == 0){             // button 2
        input = input | 0b0010;
    }
    if(PORTAbits.RA4 == 0){             // button 3
        input = input | 0b0100;
    }
    
    // return 
    return input;
}
