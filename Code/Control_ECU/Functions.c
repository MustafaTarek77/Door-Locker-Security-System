/*
 * Functions.c
 *
 *  Created on: Nov 5, 2022
 *      Author: mustafa
 */
#include"Functions.h"

#ifdef CTC_MODE
uint8 com1=5,com2=6,com3=11,com4=20;
#else
uint8 com1=3,com2=4,com3=5,com4=8;
#endif



void Wait_CTC()
{
	TIMER1_g_ticks++;
}


void Wait_OVF()
{
	Timer_Ptr->initial_value=OVF_init;
	TIMER1_g_ticks++;
}


void Ready_To_Send()
{
	//mcu2 is ready to send
	UART_sendByte(MCU2_Ready);

	while(UART_recieveByte()!=MCU1_Ready)                       //wait until mcu1 is ready
	{ }
}



void Ready_To_Recieve()
{
	while(UART_recieveByte()!=MCU1_Ready)                       //wait until mcu1 is ready to send
	{ }

	//mcu2 is ready to recieve
	UART_sendByte(MCU2_Ready);
}


/*************************************************Step1************************************************/
void Taking_Password(uint8* pass)
{
	//wait for pass to be saved
	Ready_To_Recieve();

	for(uint8 i=0;i<5;i++)
		pass[i]=UART_recieveByte();
}


void Saving_Password()
{
	uint8 flag=1,pass1[5],pass2[5],i;
	Taking_Password(pass1);
	Taking_Password(pass2);

	for(i=0;i<5;i++)
		if(pass1[i]!=pass2[i])
			flag=0;

	Ready_To_Send();
	UART_sendByte(flag);

	if(flag==1)
		for(i=0;i<5;i++)
		{
			EEPROM_writeByte(0x0311+i, pass1[i]);
			_delay_ms(10);
		}
	else
		Saving_Password();
}


/*************************************************Step2************************************************/
uint8 Compare_Passwords()
{
	uint8 flag,pass1[5],pass2[5],temp;
	for(uint8 j=0;j<3;j++)
	{
		flag=1;
		Taking_Password(pass1);

		for(uint8 i=0;i<5;i++)
		{
			if(EEPROM_readByte(0x0311+i, &temp))
				pass2[i]=temp;
			_delay_ms(10);
		}

		for(uint8 i=0;i<5;i++)
			if(pass1[i]!=pass2[i])
				flag=0;

		Ready_To_Send();
		UART_sendByte(flag);

		if(flag==1)
			break;
	}
	return flag;
}


void Open_Door();
void Change_Password();

void Main_Options(Timer1_ConfigType* Timer)
{
	Timer_Ptr=Timer;
	uint8 temp;

	Ready_To_Recieve();
	temp=UART_recieveByte();

	if(temp==plus)
	{
		Open_Door();
	}
	else
		Change_Password();
}

/*************************************************Step3************************************************/
void Security_System_Error();

void Open_Door()
{
	uint8 flag= Compare_Passwords();
	if(flag==1)
	{
		TIMER1_g_ticks=0;
		Timer1_init(Timer_Ptr);
		_delay_ms(1500);
		DcMotor_Rotate(Clockwise);
		while(TIMER1_g_ticks<com1)
		{}
		_delay_ms(1000);
		DcMotor_Rotate(Stop);
		while(TIMER1_g_ticks<com2)
		{}
		_delay_ms(1000);
		DcMotor_Rotate(Anticlockwise);
		while(TIMER1_g_ticks<com3)
		{}
		_delay_ms(1000);
		DcMotor_Rotate(Stop);
		Timer1_deInit();
	}
	else
		Security_System_Error(Timer_Ptr);
}


/*************************************************Step4************************************************/
void Change_Password()
{
	uint8 flag=Compare_Passwords();
	if(flag==1)
		Saving_Password();
	else
		Security_System_Error(Timer_Ptr);
}



/*************************************************Step5************************************************/
void Security_System_Error()
{
	TIMER1_g_ticks=0;
	Timer1_init(Timer_Ptr);
	_delay_ms(1000);
	Buzzer_on();
	while(TIMER1_g_ticks<com4)
	{}
	_delay_ms(1000);
	Buzzer_off();
	Timer1_deInit();
}
























