#include "stdafx.h"
#include "Pwm.h"
#include <avr/interrupt.h>
#include <util/atomic.h>

Pwm::Pwm() {
	
// 	PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTA_gc;			/* set waveform output on PORT C */
// 
// 	TCA0.SINGLE.CTRLB = TCA_SINGLE_CMP0EN_bm                    /* enable compare channel 2 */
// 							| TCA_SINGLE_WGMODE_DSTOP_gc ;		/* single-slope PWM mode */
// 	
// 	TCA0.SINGLE.EVCTRL &= ~(TCA_SINGLE_CNTAEI_bm);
// 	
// 	TCA0.SINGLE.PERBUF = 0x0039;			/* set PWM frequency*/
// 	TCA0.SINGLE.CMP0BUF = 0x0008;			/* 25% duty cycle */
// 	
// 	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1024_gc	/* set clock source (sys_clk/1) */
// 							| TCA_SINGLE_ENABLE_bm;		/* start timer */
// 							
// 	PORTA.OUTSET = PIN0_bm;
	PORTA.DIRSET |= PIN0_bm;

	PORTMUX.TCAROUTEA = PORTMUX_TCA11_bm;		/* set waveform output on PORT D */

	TCA1.SINGLE.CTRLB = TCA_SINGLE_CMP2EN_bm                    /* enable compare channel 2 */
						| TCA_SINGLE_WGMODE_SINGLESLOPE_gc;		/* single-slope PWM mode */
	
	TCA1.SINGLE.PER = PERIOD_EXAMPLE_VALUE;			/* set PWM frequency*/
}

void Pwm::changePosition(register16_t dutyCycle) {
	this->dutyCycle = dutyCycle;
	TCA1.SINGLE.CMP1 = dutyCycle;
	TCA1.SINGLE.CMP2 = dutyCycle;
			
	TCA1.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1024_gc
						| TCA_SINGLE_ENABLE_bm;
}
