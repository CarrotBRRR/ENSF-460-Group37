/*
 * File:   main.c
 * Author: dominic
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

void wait(uint32_t time);
        
int main(void) {
     //Clock output on REFO pin - pin 18 RB15
     TRISBbits.TRISB15 = 0;  // Set RB15 as output for REFO
     REFOCONbits.ROEN = 1; // Ref oscillator is enabled
     REFOCONbits.ROSSLP = 0; // Ref oscillator is disabled in sleep
     REFOCONbits.ROSEL = 0; // Output base clk showing clock switching
     REFOCONbits.RODIV = 0b0000;
     
     //IO Inititalizations
     AD1PCFG = 0xFFFF;  // Turn all analog pins to digital
     CNPU1bits.CN0PUE = 1; // Enables pull up resistor on RA4/CN0 butt 3
     CNPU1bits.CN1PUE = 1; // Enables pull up resistor on RB4/CN1 butt 2
     CNPU2bits.CN30PUE = 1; // Enables pull up resistor on RA2/CN30 butt 1
    
     TRISAbits.TRISA2 = 1; // Butt 1
     TRISBbits.TRISB4 = 1; // Butt 2
     TRISAbits.TRISA4 = 1; // Butt 3
             
     TRISBbits.TRISB8 = 0; // LED
     
    
    while(1){
        wait(16000);
        unsigned int input = 0b0000;
        if(PORTAbits.RA2 == 0){
            input = input | 0b0001;
        }
        if(PORTBbits.RB4 == 0){
            input = input | 0b0010;
        }
        if(PORTAbits.RA4 == 0){
            input = input | 0b0100;
        }
        if(input == 0){
            LATBbits.LATB8 = 0;
        }
        
        else if(input == 0b0001){
            LATBbits.LATB8 = 1;
            wait(320000);
            LATBbits.LATB8 = 0;
            wait(320000);
            
        }
        
        else if(input == 0b0010){
            LATBbits.LATB8 = 1;
            wait(640000);
            LATBbits.LATB8 = 0;
            wait(640000);
        }
        
        else if(input == 0b0100){
            LATBbits.LATB8 = 1;
            wait(960000);
            LATBbits.LATB8 = 0;
            wait(960000);
        }

        else {
            LATBbits.LATB8 = 1;
        }
        
        LATAbits.LATA2 = 1;
        LATBbits.LATB4 = 1;
        LATAbits.LATA4 = 1;
     }
    return 0;
}

void wait(uint32_t time) {
    while(time > 0){
        time--;
    }
    
    return;
}
