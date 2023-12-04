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
#include "UART2.h"
#include "ADC.h"

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

#define LED_ON LATBbits.LATB8 = 1;
#define LED_OFF LATBbits.LATB8 = 0;

uint16_t result;
// uint16_t adc_val;
unsigned int adc_val;
uint8_t PB1_flag = 0;
uint8_t PB2_flag = 0;

int main(void) {
    NewClk(32);
    IOinit();
    InitUART2();

    while(1) {

        // When PB1 is pressed, system is in ON MODE
        if (PB1_flag == 1) {
            // Get ADC Value
            NewClk(8);
            adc_val = do_ADC();    
            
            // Calculate Duty Cycle
            float duty_cycle = (((float)adc_val * 100)) / 1024;

            // send duty_cycle through UART
            Disp2Dec((uint16_t)duty_cycle);
            

            // // Need to play around with this pulse_period value
            float pulse_period = 25;
            
            // Flicker LED based on potentiometer level
            if (((int)duty_cycle > 2 ) && ((int)duty_cycle < 95)){
                
                duty_cycle = duty_cycle / 5;
                
                float on_time = (pulse_period * duty_cycle) / 100;
                float off_time = pulse_period - off_time;
                
                NewClk(32);
                LED_ON;
                delay_ms(((uint32_t)on_time) + 1);
                LED_OFF;
                delay_ms(((uint32_t)off_time) + 1);
            }

            // LED OFF if duty_cycle <= 3 
            else if (duty_cycle <= 2){ 
                LED_OFF;
            }

            // LED ON if duty_cycle >= 95 
            else if (duty_cycle >= 95){
                LED_ON;
            }
            
        // Blink LED at full brightness for 500ms when PB2 is pressed
        } else if (PB2_flag == 1) {
            NewClk(32);
            LED_ON;
            // delay_ms is in quarters miliseconds
            delay_ms(500);
            LED_OFF;
            delay_ms(500);
        // System is in OFF MODE and saves power.
        } else { 
            NewClk(32);
            Idle();
        }
    }
    
    return 0;
}

