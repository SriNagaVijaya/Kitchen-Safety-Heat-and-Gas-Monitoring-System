//function definitions

#include "types.h"
#include "delay.h"
#include "LCD_defines.h"
#include "defines.h"
#include <lpc21xx.h>

void WRITE_LCD_CMD(u8 cmd)
{
	 //perform write operation(RW=0)
	SCLRBIT(IOCLR0,LCD_RW);
	//select command register(RS=0)
	SCLRBIT(IOCLR0,LCD_RS);
	//write cmd on to the data pins
	WRITEBYTE(IOPIN0,LCD_DATA,cmd);
	//apply H to L pulse on EN
	SSETBIT(IOSET0,LCD_EN); //EN=1
	//delay for internal process
	delay_us(1);
	SCLRBIT(IOCLR0,LCD_EN); //EN=0;
	//delay for internal process
	delay_ms(2);
}

void Init_LCD(void)
{
	//cfg p0.8 to p0.15(LCD data pins) as output
	WRITEBYTE(IODIR0,LCD_DATA,0XFF);
	//cfg p0.16(RS),p0.17(RW),p0.18(EN) as output
	SETBIT(IODIR0,LCD_RS);
	SETBIT(IODIR0,LCD_RW);
	SETBIT(IODIR0,LCD_EN);
	delay_ms(15);
	WRITE_LCD_CMD(MODE_8BIT_1LINE);
	delay_ms(5);
	WRITE_LCD_CMD(MODE_8BIT_1LINE);
	delay_us(100);
	WRITE_LCD_CMD(MODE_8BIT_1LINE);
	
	WRITE_LCD_CMD(MODE_8BIT_2LINE);
	WRITE_LCD_CMD(DISP_ON_CUR_OFF);
	WRITE_LCD_CMD(CLEAR_LCD);
	WRITE_LCD_CMD(SHIFT_CUR_RIGHT);
}

void WRITE_LCD_DATA(u8 ascii)
{
	SCLRBIT(IOCLR0,LCD_RW);
	//select data registers(RS=1)
	SSETBIT(IOSET0,LCD_RS);
	//write data on to the datapins
	WRITEBYTE(IOPIN0,LCD_DATA,ascii);
	//apply H to L pulse on EN
	SSETBIT(IOSET0,LCD_EN); //EN=1
	delay_us(1);
	SCLRBIT(IOCLR0,LCD_EN); //EN=0
	//delay for internal process
	delay_ms(2);
}

//display string
void StrLCD(s8* str)
{
	while(*str)
	{
		WRITE_LCD_DATA(*str++);
	}
}

//display positive numbers
void U32LCD(u32 n)
{
	u8 a[10];
	s32 i=0;
	if(n==0)
	{
		WRITE_LCD_DATA('0');
	}
	else
	{
		while(n)
		{
			a[i++] =n%10+48;
			n/=10;
		}
		for(--i;i>=0;i--) //array revrsing
		{
			WRITE_LCD_DATA(a[i]);
		}
	}
}

//dispaly negative values
void S32LCD(s32 n)
{
	if(n<0)
	{
		WRITE_LCD_DATA('-');
		n=-n;
		U32LCD(n);
	}
}

//display floating values
void F32LCD(f32 fn, u8 nDP)
{
	u32 iNUM,i;
	if(fn<0)
	{
		WRITE_LCD_DATA('-');
		fn=-fn;
	}
	iNUM=fn;
	U32LCD(iNUM);
	WRITE_LCD_DATA('.');
	for(i=0;i<nDP;i++)
	{
		fn=(fn-iNUM)*10;
		iNUM=fn;
		WRITE_LCD_DATA(iNUM+'0');
	}
}

//customized symbols
void BuildCGRAM(u8* p, u8 nb)
{
	s32 i;
	//select CGRAM
	WRITE_LCD_CMD(GOTO_CGRAM);
	for(i=0;i<nb;i++)
	{
		WRITE_LCD_DATA(p[i]);
	}
	//select DDRAM
	WRITE_LCD_CMD(GOTO_LINE1_POS0+5);
}


