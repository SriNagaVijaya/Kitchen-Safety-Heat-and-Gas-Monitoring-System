//ADC.c

#include <lpc21xx.h>
#include "types.h"
#include "delay.h"
#include "ADC_defines.h"

void Init_ADC(void)
{
	//make p0.27 to p0.30 as GPIO
	PINSEL1 =0x15400000;
	//cgf p0.27 as AIN0
	PINSEL1 =AIN0;
	ADCR =1<<PDN_BIT|CLKDIV_VALUE<<CLKDIV;
}

void Read_ADC(u32 chno,u32 *dval,f32 *eAR)
{
	//clear previous channel values
	ADCR &=~(255<<0);
	//select channel
	ADCR |=chno|1<<START_CONV;
	//wait for 3usec
	delay_us(3);
	//check the done bit status
	while(((ADDR>>DONE_BIT)&1)==0);
	//stop conversion
	ADCR &=~(1<<START_CONV);
	//extract 10 bit digital output
	*dval =((ADDR>>RESULT)&1023);
	//find eAR value
	*eAR=(3.3/1023)*(*dval);
}

