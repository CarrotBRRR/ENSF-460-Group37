#ifndef TIMEDELAY_H
#define TIMEDELAY_H

void delay_ms(uint8_t ms, uint8_t idle_on);
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void);
void delay_sec();
#endif