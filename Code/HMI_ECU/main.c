/*
 * main.c
 *
 *  Created on: Nov 3, 2022
 *      Author: mustafa
 */
#include"Functions.h"

int main()
{
	//Enable Global Interrupt I-Bit
	SREG |= (1<<7);

	UART_ConfigType UART_Ptr;
	UART_Ptr.bit_data=0X03;
	UART_Ptr.baud_rate=9600;
	UART_Ptr.parity=0;
	UART_Ptr.stop_bit=0;


	Timer1_ConfigType Timer_Ptr;
	Timer_Ptr.mode=CTC_Mode;
	Timer_Ptr.prescaler=0X05;     //F_CPU/1024
	Timer_Ptr.initial_value=0;
	Timer_Ptr.compare_value=23438;   //three seconds
	//OVF Mode->42098
	//CTC Mode->23438

	LCD_init();
	UART_init(&UART_Ptr);
#ifdef CTC_MODE
		Timer1_setCallBack(Wait_CTC);
#else
		Timer1_setCallBack(Wait_OVF);
#endif


	Create_Password();

	while(1)
	{
		Main_System_Optains(&Timer_Ptr);
	}
}


