/*
 * File:   main.c
 * Author: Nathan Ante, Dominic Choi, Justin Pham
 *
 * Created on September 25, 2023, 2:54 PM
 */
// LINKED .h SOURCE FILES HERE
#include "xc.h"
#include <p24fxxxx.h>
#include <p24F16KA101.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>

#include "IOs.h"
#include "ChangeClk.h"
#include "TimeDelay.h"

//// CONFIGURATION BITS - PRE-PROCESSOR DIRECTIVES ////

// Code protection 
#pragma config BSS = OFF // Boot segment code protect disabled
#pragma config BWRP = OFF // Boot sengment flash write protection off
#pragma config GCP = OFF // general segment code protecion off
#pragma config GWRP = OFF

// CLOCK CONTROL 
#pragma config IESO = OFF    // 2 Speed Startup disabled
#pragma config FNOSC = FRC  // Start up CLK = 8 MHz
#pragma config FCKSM = CSECMD // Clock switching is enabled, clock monitor disabled
#pragma config SOSCSEL = SOSCLP // Secondary oscillator for Low Power Operation
#pragma config POSCFREQ = MS  //Primary Oscillator/External clk freq betwn 100kHz and 8 MHz. Options: LS, MS, HS
#pragma config OSCIOFNC = ON  //CLKO output disabled on pin 8, use as IO. 
#pragma config POSCMOD = NONE  // Primary oscillator mode is disabled

// WDT
#pragma config FWDTEN = OFF // WDT is off
#pragma config WINDIS = OFF // STANDARD WDT/. Applicable if WDT is on
#pragma config FWPSA = PR32 // WDT is selected uses prescaler of 32
#pragma config WDTPS = PS1 // WDT postscler is 1 if WDT selected

//MCLR/RA5 CONTROL
#pragma config MCLRE = OFF // RA5 pin configured as input, MCLR reset on RA5 diabled

//BOR  - FPOR Register
#pragma config BORV = LPBOR // LPBOR value=2V is BOR enabled
#pragma config BOREN = BOR0 // BOR controlled using SBOREN bit
#pragma config PWRTEN = OFF // Powerup timer disabled
#pragma config I2C1SEL = PRI // Default location for SCL1/SDA1 pin

//JTAG FICD Register
#pragma config BKBUG = OFF // Background Debugger functions disabled
#pragma config ICS = PGx2 // PGC2 (pin2) & PGD2 (pin3) are used to connect PICKIT3 debugger

// Deep Sleep RTCC WDT
#pragma config DSWDTEN = OFF // Deep Sleep WDT is disabled
#pragma config DSBOREN = OFF // Deep Sleep BOR is disabled
#pragma config RTCOSC = LPRC// RTCC uses LPRC 32kHz for clock
#pragma config DSWDTOSC = LPRC // DeepSleep WDT uses Lo Power RC clk
#pragma config DSWDTPS = DSWDTPS7 // DSWDT postscaler set to 32768 

// MACROS
#define Nop() {__asm__ volatile ("nop");}
#define ClrWdt() {__asm__ volatile ("clrwdt");}
#define Sleep() {__asm__ volatile ("pwrsav #0");}   // set sleep mode
#define Idle() {__asm__ volatile ("pwrsav #1");}
#define dsen() {__asm__ volatile ("BSET DSCON, #15");}

// Global Variables
uint8_t CNflag = 0;
uint8_t run_flag = 0;
uint8_t alarm_flag = 0;
extern uint8_t minutes;
extern uint8_t seconds;


int main(void) {
    // Initialization function calls
    NewClk(500);
    InitIO();
    InitUART2();
    
    // initial print of 00m : 00s
    DispTime(minutes, seconds);
    
    while(1) {

        if (CNflag == 1) {                          // if a Change Notification was sent
            CNflag = 0;                             // reset the flag
            uint8_t counter = 0;                    // reset counter
            while (PORTAbits.RA4 == 0) {            // check if button is being held
                counter++;                          // increment the counter
                delay_ms(250, 1);                   // wait 250ms
            }
            if (counter >= 12) {                    // button was held for more than 3 seconds (3sec * 4(quarter sec) = 12)
                // reset variables
                alarm_flag = 0;
                run_flag = 0;
                minutes = 0;
                seconds = 0;
                DispTime(minutes, seconds);         // display 0 min 0 sec
            } else {                                // button was short pressed, toggle pause/start timer
                run_flag = !run_flag;          
            }
        }
         
        if (run_flag == 1 && (minutes != 0 || seconds != 0)) {
            doClock();
            DispTime(minutes, seconds);
            if (minutes == 0 && seconds == 0) {
                alarm_flag = 1;
                run_flag = 0;
                Disp2String("\r00 m : 00 s -- ALARM");
                while(alarm_flag == 1) {    // while alarming
                    LATBbits.LATB8 = 1;     // turn on LED
                    delay_sec();            // wait 1 sec
                    LATBbits.LATB8 = 0;     // turn off LED
                    delay_sec();            // wait 1 sec
                }
                DispTime(minutes, seconds); // update display when we stop alarming
                
            } else {
                LATBbits.LATB8 = 0; // make sure LED is off
                delay_sec();        // wait 1 second
            }
        } else {
            Idle();
        }
    }
    return 0;
}

void doClock(){
    if(seconds == 0 && minutes > 0){    // if there are still minutes, and seconds are 0
        minutes--;                      // decrement minutes
        seconds = 59;                   // reset to 60 - 1 seconds
    } else {
        seconds--;                      // decrement 1 second
    }
    
    return;
}
/*---------------------- CN interrupt ----------------------*/
void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void) {
    IFS1bits.CNIF = 0;
    if (PORTAbits.RA4 == 0) {        // checks to see if button 3 was pressed    
        CNflag = 1;                  // if so, then trigger a flag to see if button is being held
        return;
    } else {
        checkIO();                   // check the input
    }    
    return;
}