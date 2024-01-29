/*
 * PWM_timer.c
 *
 *  Created on: Oct 6, 2022
 *      Author: mustafa
 */
#include"PWM_timer.h"
#include"avr/io.h"
#include"gpio.h"

void PWM_Timer0_Start(uint8 duty_cycle)
{
	/*1.choose the PWM Mode.
      2.Setup the PWM mode with Non-Inverting.
      3.Setup the prescaler */
	TCCR0=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS01)|(1<<CS00);
	/*Setup the direction for OC0 as output pin through the GPIO driver*/
	GPIO_setupPinDirection(PORTB_ID, PIN3, PIN_OUTPUT);
	/*Setup the compare value based on the required input duty cycle*/
	TCNT0=0;
	OCR0=(duty_cycle/100.0)*255;
}
