#include <p24F16KA101.h>

#include "IOs.h"
#include "TimeDelay.h"

void InitIO(){
    //Clock output on REFO pin - pin 18 RB15
    TRISBbits.TRISB15 = 0;  // Set RB15 as output for REFO
    REFOCONbits.ROEN = 1; // Ref oscillator is enabled
    REFOCONbits.ROSSLP = 0; // Ref oscillator is disabled in sleep
    REFOCONbits.ROSEL = 0; // Output base clk showing clock switching
    REFOCONbits.RODIV = 0b0000;
    
    //IO Initializations
    AD1PCFG = 0xFFFF;  // Turn all analog pins to digital
    
    CNPU2bits.CN30PUE = 1; // Enables pull up resistor on RA2/CN30 butt 1
    CNPU1bits.CN1PUE = 1; // Enables pull up resistor on RB4/CN1 butt 2
    CNPU1bits.CN0PUE = 1; // Enables pull up resistor on RA4/CN0 butt 3
    
    TRISAbits.TRISA2 = 1; // Butt 1
    TRISBbits.TRISB4 = 1; // Butt 2
    TRISAbits.TRISA4 = 1; // Butt 3
            
    TRISBbits.TRISB8 = 0; // LED
    
    CNEN2bits.CN30IE = 1; // CN30 RA2 Butt1
    CNEN1bits.CN1IE = 1;  // CN1  RB4 Butt2
    CNEN1bits.CN0IE = 1;  // CN0  RA4 Butt3

    IPC4bits.CNIP = 6;    // 7 is highest priority, 0 is disabled
    IFS1bits.CNIF = 0;    // Clear Interrupt Flag
    IEC1bits.CNIE = 1;    // Enables CN Interrupts    
}

// timer variables
extern alarm_flag;
uint8_t minutes = 0;
uint8_t seconds = 0;

/*
    Checks if timer should increment by a minute or second based on button press
*/
void checkIO() { 
    alarm_flag = 0;                     // reset the alarm flag

    if(PORTAbits.RA2 == 0) {            // button 1
        addSeconds(60);                 // add a minute to timer
        return;
    }

    if(PORTBbits.RB4 == 0) {            // button 2
        addSeconds(1);                  // add a second to timer
        return;
    }
}

/*
    Function to add seconds to our timer
    Takes in integer of how many seconds to add
*/
void addSeconds(uint8_t s) {        
    if( ((minutes*60) + seconds + s) <= 3599 ){
        seconds += s;               // add seconds

        while(seconds >= 60){       // while there are too many seconds
            seconds -= 60;          // decrement by 60 sec
            minutes++;              // increment by 1 min
        }
    }

    DispTime(minutes, seconds);     // display the new time

    return;
}

