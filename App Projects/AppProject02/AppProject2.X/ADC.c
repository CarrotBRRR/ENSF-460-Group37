/*
 * le:   ADC.c
 * Author: Macante
 *
 * Created on November 1, 2023, 2:32 PM
 */

#include "xc.h"
#include "ADC.h"
#include "UART2.h"

void ADC_init(void)
{
	AD1CON1bits.ADON=0;			//Turn off ADC, turn on before sampling in do_ADC()
	AD1CON1bits.ADSIDL=0;		//Continue ADC operation in idle mode
	AD1CON1bits.FORM=0b00;		//0b00: Int, 01: Signed Int, 10:Fractional, 11:Signed Fract
	AD1CON1bits.SSRC=0b111;	//Start ADC conversion Time set by SAMC has passed
	AD1CON1bits.ASAM=0; 	//Next Sampling begins when SAMP bit is set
	AD1CON1bits.SAMP=0;		//Set this bit in ADC routine to start sampling  

    // Sampling time and ADC Clk select
	AD1CON2bits.VCFG=0b000;	 //Vref+=AVDD   Vref-=AVSS
//	AD1CON2bits.BUFS=1;	//ADC is filling ADC1BUF8-BUFF. Access data in BUF0-7
	AD1CON2bits.CSCNA=0;	//Do not scan inputs; use channel selected by CH0SA bits
	AD1CON2bits.SMPI=0b0000; //Any ADC interrrups occur at completion of each sample/convert seq.
	AD1CON2bits.BUFM=0; //Buffer confugured as 1 16 word buffer 
	AD1CON2bits.ALTS=0; //Always use MUXA input MUX settings
	AD1CON3bits.ADRC=0; //0: Use System clk; 1: ADC uses internal RC clock for idle or sleep mode
	AD1CON3bits.SAMC=0b11111; //Sample time = 31*TAD = 31*1/125e3 = 0.248ms
    AD1CON3bits.ADCS=0b111111; //ADCS conversion clock selet bits. Ignored if using internal AD RC clock. 
	
    // MUX settings
    AD1CHSbits.CH0NB=0;	//Ch0 MUXB -ve Input is VR-
	AD1CHSbits.CH0SB=0b0101;	//Positive input is AN5/RA3/pin8 for MUXB
	AD1CHSbits.CH0NA=0;	//Ch0 -ve Input is VR-
	AD1CHSbits.CH0SA=0b0101;	//Positive input is AN5/RA3/pin8 for MUXA
	
    //IO port selection
    TRISAbits.TRISA3 = 1;  //Set pin8/RA3/AN5 as input
    AD1PCFG=0xFFFF; //Set all bits as digital
	AD1PCFGbits.PCFG5=0; 	//Set only pin8/AN5/RA3 as Analog input for ADC
	AD1CSSL = 0; //Input Scan disabled, 0x0000 is default state.
    
    return;
}

unsigned int do_ADC(void)
{
	unsigned int ADCvalue;
    ADC_init();
    AD1CON1bits.ADON=1;	//Turn on ADC module
	AD1CON1bits.SAMP=1;	//Start Sampling, Conversion starts automatically after SSRC and SAMC settings
	while(AD1CON1bits.DONE == 0)
		{
		}
	AD1CON1bits.SAMP=0;	//Stop sampling
	ADCvalue = ADC1BUF0;
	AD1CON1bits.ADON=0;	//Turn off ADC, ADC value stored in ADC1BUF0;
	return (ADCvalue);
}