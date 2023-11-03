#include <p24F16KA101.h>

#include "TimeDelay.h"
#include "ChangeClk.h"

#ifndef Idle()
#define Idle() {__asm__ volatile ("pwrsav #1");}
#endif

uint8_t TMR2flag = 0;   // global variable to see if timer was completed
uint8_t HOLDflag = 0;   // global variable to see if button was held or not

void InitTimer() {
    //Timer 1
    T1CONbits.TCKPS = 0; // set pre-scaler
    T1CONbits.TCS = 0; // use internal clock
    // T1CONbits.TGATE = 0;
    T1CONbits.TSIDL = 0; // operate in idle mode
    
    //timer 1 config
    IPC0bits.T1IP = 2;  // timer 1 interrupt priority
    IFS0bits.T1IF = 0;  // timer 1 interrupt flag
    IEC0bits.T1IE = 1;  // enable interrupt timer 1
    
    //Timer 2
    T2CONbits.T32 = 0; // operate timer 2 as 16 bit timer
    T2CONbits.TCKPS = 0; // set pre-scaler
    T2CONbits.TCS = 0; // use internal clock
    // T2CONbits.TGATE = 0;
    T2CONbits.TSIDL = 0; // operate in idle mode
    
    //timer 2 interrupt config
    IPC1bits.T2IP = 2;  // timer 2 interrupt priority
    IFS0bits.T2IF = 0;  // timer 2 interrupt flag
    IEC0bits.T2IE = 1;  // enable interrupt timer 2
}

void hold_check() {
    TMR2flag = 0;
    IFS0bits.T2IF = 0;  // timer interrupt flag
    PR2 = 16 * 3000; // Set Time in ms
    TMR2 = 0;        // Clear TMR2
    T2CONbits.TON = 1; // Start Timer
    Idle();
    return;
}

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void){
    IFS0bits.T2IF = 0; // clear timer 2 flag
    T2CONbits.TON = 0; // stop the timer
    TMR2flag = 1;
    return;
}