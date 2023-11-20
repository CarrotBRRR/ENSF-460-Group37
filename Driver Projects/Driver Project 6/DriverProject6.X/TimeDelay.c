#include <p24F16KA101.h>
#include "xc.h"
#include "TimeDelay.h"
#include "ChangeClk.h"

#ifndef Idle()
#define Idle() {__asm__ volatile ("pwrsav #1");}
#endif

uint8_t TMR2flag = 0;

void delay_ms(uint32_t time) {
    TMR2flag = 0;
    //T2CON
    T2CONbits.T32 = 0; // operate timer 2 as 16 bit timer
    T2CONbits.TCKPS = 0; // set pre-scaler
    T2CONbits.TCS = 0; // use internal clock
    // T2CONbits.TGATE = 0;
    T2CONbits.TSIDL = 0; // operate in idle mode
    
    //timer 2 config
    IPC1bits.T2IP = 2;
    IFS0bits.T2IF = 0;  // timer interrupt flag
    IEC0bits.T2IE = 1;  // enable interrupt timer
    
    PR2 = 16 * time; // Set Time in ms
    TMR2 = 0;        // Clear TMR2
    T2CONbits.TON = 1; // Start Timer
    while(TMR2flag != 1){
        Idle();
    }
    return;
}

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void){
    IFS0bits.T2IF = 0; // clear timer 2 flag
    T2CONbits.TON = 0; // stop the timer
    TMR2flag = 1;
    return;
}