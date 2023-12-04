/* 
 * File:   ADC.h
 * Author: Macante
 *
 * Created on November 1, 2023, 2:31 PM
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif



#ifdef	__cplusplus
}
#endif
//void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void);

void ADC_init(void);
uint16_t do_ADC(void);

#endif	/* ADC_H */

