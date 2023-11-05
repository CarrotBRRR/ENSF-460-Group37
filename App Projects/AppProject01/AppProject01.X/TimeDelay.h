#ifndef TIMEDELAY_H
#define TIMEDELAY_H

void hold_check();
void delay_sec();
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void);
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void);

#endif