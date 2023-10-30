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

uint8_t userInput = 0;

int main(void) {
    NewClk(0x55);
    IOinit();
    InitUART2();
    while(1) {
        /* button logic */
        
        switch(userInput) {
            
            case 0b0000:
                Disp2String("Nothing is pressed");
                LATBbits.LATB8 = 0;
                    
                while (userInput == 0b0000) { 
                    // do nothing
                }
                
                break;
            // button 1
            case 0b0001:
                Disp2String("PB1 is pressed");
                while(userInput == 0b0001) {
                    LATBbits.LATB8 = 1;
                    delay_ms(500);
                    LATBbits.LATB8 = 0;
                    delay_ms(500);
                }
                break;
            // button 2
            case 0b0010:
                Disp2String("PB2 is pressed");
                while(userInput == 0b0010) {
                    LATBbits.LATB8 = 1;
                    delay_ms(2000);
                    LATBbits.LATB8 = 0;
                    delay_ms(2000);
                }
                break;
            // button 3
            case 0b0100:
                Disp2String("PB3 is pressed");
                while(userInput == 0b0100) {
                    LATBbits.LATB8 = 1;
                    delay_ms(3000);
                    LATBbits.LATB8 = 0;
                    delay_ms(3000);
                }
                break;
            // all buttons
            case 0b0111:
                Disp2String("All PBs are pressed");
                LATBbits.LATB8 = 1;
                while (userInput == 0b0111) { 
                    // do nothing
                }
            // 2 buttons
            default:
                
                LATBbits.LATB8 = 1;
                uint8_t changeCheck = userInput;
                if (userInput == 0b0011){ Disp2String("PB1 and PB2 are pressed"); } // button 1 and 2
                if (userInput == 0b0101){ Disp2String("PB1 and PB3 are pressed"); } // button 1 and 3
                if (userInput == 0b0110){ Disp2String("PB2 and PB3 are pressed"); } // button 2 and 3
                
                while(userInput == changeCheck) {
                    // do nothing
                }
                
                break;
        }
     }
    return 0;
}

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void){
    if (IFS1bits.CNIF == 1) {
        userInput = IOcheck();
    }
    IFS1bits.CNIF = 0;
}
