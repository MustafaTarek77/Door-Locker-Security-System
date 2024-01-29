/*
 * timer.c
 *
 *  Created on: Nov 3, 2022
 *      Author: mustafa
 */
#include"timer1.h"
#include"common_macros.h"
#include <avr/io.h> /* To use ICU/Timer1 Registers */
#include <avr/interrupt.h> /* For ICU ISR */
/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}



void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	TCNT1 = Config_Ptr->initial_value;		/* Set timer1 initial count to zero */

	OCR1A = Config_Ptr->compare_value;    /* Set the Compare value to 125 ((125/500) * 100 = 25%) */

	SET_BIT(TIMSK,OCIE1A); /* Enable Timer1 Compare A Interrupt */

	/* Configure timer control register TCCR1A
	 * 1. Disconnect OC1A and OC1B  COM1A1=0 COM1A0=0 COM1B0=0 COM1B1=0
	 * 2. FOC1A=1 FOC1B=0
	 */
	SET_BIT(TCCR1A,FOC1A);


	TCCR1B = (Config_Ptr->mode<<3) | (Config_Ptr->prescaler<<0);
}



void Timer1_deInit(void)
{
	/* Clear Timer Register */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	OCR1A = 0;
	/* Disable Interrupt */
	TIMSK &= ~(1 << OCIE1A);
}



void Timer1_setCallBack(void(*a_ptr)(void))
{

	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}
