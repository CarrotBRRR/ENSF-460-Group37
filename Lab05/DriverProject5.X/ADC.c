/*
 * le:   ADC.c
 * Author: Macante
 *
 * Created on November 1, 2023, 2:32 PM
 */

#include "xc.h"
#include "ADC.h"
#include "UART2.h"

uint16_t do_ADC(void){
    uint16_t ADCvalue; // 16 bit register used to hold AADC converted digital output ADC1BUF0
    /*--------------- ADC INITIALIZATION ---------------*/

    AD1CON1bits.ADON = 1;
    // configure ADC by settings in AD1CON1 register here...
    // ADCON1bits.ADSIDL = // stop in Idle Mode bit
    AD1CON1bits.FORM = 0b00; // data output format bits
    AD1CON1bits.SSRC = 0b111; // Conversion Trigger Source Select bits
    AD1CON1bits.ASAM = 0; // A/DSample Auto-Start bit
    
    // configure ADC by settings in AD1CON2 register here...
    AD1CON2bits.VCFG = 0b000; // Voltage Reference Configuration bits
    AD1CON2bits.CSCNA = 0; // Scan Input Selections for CH0+ during Sample A bit
    AD1CON2bits.SMPI = 0b0000; // Sample/Conversion Sequence Interrupt Mode bits
    AD1CON2bits.BUFM = 0; // Buffer Fill Mode Select bit    
    AD1CON2bits.ALTS = 0; // Alternate Input Sample Mode Select bit

    // configure ADC by settings in AD1CON3 register here...
    AD1CON3bits.ADRC = 0; // ADC Conversion Clock Source bit
    AD1CON3bits.SAMC = 0b11111; // Auto Sample Time bits
    AD1CON3bits.ADCS = 0b11111; // ADC Conversion Clock Select bits

    // configure ADC by settings in AD1CHS register here...
    // // MUX A
    AD1CHSbits.CH0NA = 0; // Channel 0 Negative Input Select bits
    AD1CHSbits.CH0SA = 0b0101; // Channel 0 Positive Input Select bits
    // // MUX B
    // AD1CHSbits.CH0NB = 0; // Channel 0 Negative Input Select bits
    // AD1CHSbits.CH0SB = 0b0101; // Channel 0 Positive Input Select bits
    
    // configure ADC by settings in AD1PCFG register here...
    AD1PCFG = 0x0000;
    // configure ADC by settings in AD1CSSL register here...
    AD1CSSL = 0x0000; // Analog Input Pin Scan Selection bits
    
    /*----------------------------- ADC SAMPLING AND CONVERSION -----------------------------*/

    AD1CON1bits.SAMP = 1; // Start sampling, conversion starts automatically after SSRC and SAMC settings
    while  ( AD1CON1bits.DONE == 0 ) {}  // idle while ADC conversion is not done
    
    ADCvalue = ADC1BUF0;
    
    AD1CON1bits.SAMP = 0; // Stop sampling
    AD1CON1bits.ADON = 0; // Turn of ADC, ADC value stored in ADC1BUF0
    
    return ADCvalue;
}

uint16_t oldbars;

void displayADC(uint16_t ADCval){
    uint16_t bars = (ADCval + 1) / 32; // get a number between 0 and 32
    XmitUART2('\r', 1); // Return to beginning of the line

    // Update Chart if Changed
    if (bars != oldbars){
        oldbars = bars;
        XmitUART2(' ', 40);     // clear chart
        XmitUART2('\r', 1);        // return to start of line

        XmitUART2('*', 1);      // first *
        XmitUART2('*', bars);   // print length of bar
        XmitUART2(' ', 1);      // print spacer
        Disp2Hex(ADCval);       // print value
    }

    return;
}

//// ADC interrupt service routine
//void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void){
//    IFS0bits.AD1IF = 0; // clear ADC interrupt flag
//}