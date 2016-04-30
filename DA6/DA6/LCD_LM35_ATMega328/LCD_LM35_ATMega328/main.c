#ifndef F_CPU
#define F_CPU 1600000UL
#endif
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
void adc_init()
{
	ADMUX = (1<<REFS0);
	ADCSRA = (1<<ADEN);
}
// read adc value
uint16_t adc_read(uint8_t ch)
{
	
	ch &= 0b00000111;  // AND operation with 7
	ADMUX = (ADMUX & 0xF7)|ch;
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	return (ADC);
}
int main()
{
	uint16_t adc_result0;
	int temp;
	char buffer[10];
	// initialize adc and lcd
	adc_init();
	lcd_init(LCD_DISP_ON_CURSOR);
	lcd_clrscr();
	lcd_gotoxy(0,0);
	_delay_ms(50);
	while(1)
	{
		adc_result0 = adc_read(0);// read adc value at PC0
		temp=adc_result0/16.0;    // finding the temperature
		lcd_gotoxy(0,0);
		itoa(temp,buffer,10);
		lcd_puts("Temperature="); //display temperature
		lcd_puts(buffer);
		lcd_puts(" ");            //display temperature
		lcd_puts(" ");            //display temperature
           lcd_gotoxy(0,1);
           lcd_puts(" ");            //display temperature
           lcd_puts("By Noor Blum ");//display temperature
		_delay_ms(500);
	}
}