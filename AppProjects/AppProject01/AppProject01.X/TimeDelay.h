#ifndef TIMEDELAY_H
#define TIMEDELAY_H

void InitTimer();
void delay_sec();
void hold_check();
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void);
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void);

#endif