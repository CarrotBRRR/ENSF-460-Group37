#include <p24F16KA101.h>

#include "TimeDelay.h"
#include "ChangeClk.h"

#ifndef Idle()
#define Idle() {__asm__ volatile ("pwrsav #1");}
#endif


/* starts a timer for 3 seconds to see if button press is a long press, sets a flag after timer */
void delay_ms(uint8_t ms, uint8_t idle_on) {
    uint8_t TMR2flag = 0;
    //Timer 2
    T2CONbits.TSIDL = 0; // operate in idle mode
    T2CONbits.T32 = 0; // operate timer 2 as 16 bit timer
    // T2CONbits.T32 = 1; // operate timer 2 as 32 bit timer
    T2CONbits.TCKPS = 0; // set pre-scaler
    T2CONbits.TCS = 0; // use internal clock
    // T2CONbits.TGATE = 0;
    
    //timer 2 interrupt config
    IPC1bits.T2IP = 2;  // timer 2 interrupt priority
    IEC0bits.T2IE = 1;  // enable interrupt timer 2
    IFS0bits.T2IF = 0;  // timer 2 interrupt flag

    TMR2flag = 0;
    PR2 = 250 * ms; // Set Time in ms
    TMR2 = 0;        // Clear TMR2
    T2CONbits.TON = 1; // Start Timer
    
    if (idle_on) {
        Idle();
    }

    return;
}

/* timer for 1 sec */
void delay_sec() {
    for(int i = 0; i < 4; i++) {    // delay 250ms, 4 times
        delay_ms(250, 1);
    }
}

/*------------------------- Timer Interrupts -------------------------*/

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void){
    IFS0bits.T2IF = 0; // clear timer 2 flag
    return;
}