/*
 * Functions.c
 *
 *  Created on: Nov 4, 2022
 *      Author: mustafa
 */
#include"Functions.h"

#ifdef CTC_MODE
uint8 com1=5,com2=6,com3=11,com4=20;
#else
uint8 com1=3,com2=4,com3=5,com4=8;
#endif



//func to clear the screen
void Clear()
{
	LCD_moveCursor(0,0);
	LCD_displayString("                ");
	LCD_moveCursor(1,0);
	LCD_displayString("                ");
}


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
	//mcu1 is ready to send
	UART_sendByte(MCU1_Ready);

	while(UART_recieveByte()!=MCU2_Ready)                       //wait until mcu2 is ready
	{ }
}



void Ready_To_Recieve()
{
	while(UART_recieveByte()!=MCU2_Ready)                       //wait until mcu2 is ready to send
	{ }

	//mcu1 is ready to recieve
	UART_sendByte(MCU1_Ready);
}


//func to take pass from keypad
void Taking_Password(uint8* pass)
{
	uint8 temp,i;
	i=0;
	while(1)
	{
		temp=KEYPAD_getPressedKey();
		if(temp>=0&&temp<=9)
		{
			pass[i++]=temp;
			LCD_displayString("*");
		}
		if(i==5)
			break;
		_delay_ms(500);
	}
	do
	{
		temp=KEYPAD_getPressedKey();
	}while(temp!=13);                    //wait until the user press on enter

}
/************************************************Step1*************************************************/
//func to create pass
void Create_Password()
{
	uint8 flag,i;
	uint8 pass1[5],pass2[5];
	do
	{
		//Displaying
		LCD_displayStringRowColumn(0,0,"plz enter pass:");

		//taking first password
		LCD_moveCursor(1,0);
		Taking_Password(pass1);
		Clear();

		LCD_displayStringRowColumn(0,0,"plz re-enter the");
		LCD_displayStringRowColumn(1,0,"same pass:");

		//taking second password
		LCD_moveCursor(1,10);
		Taking_Password(pass2);
		Clear();

		Ready_To_Send();
		for(i=0;i<5;i++)
			UART_sendByte(pass1[i]);

		Ready_To_Send();
		for(i=0;i<5;i++)
			UART_sendByte(pass2[i]);


		Ready_To_Recieve();
		flag=UART_recieveByte();

		if(flag==0)
			LCD_displayStringRowColumn(0,0,"Unmatched Pass");
		else
			LCD_displayStringRowColumn(0,0,"Matched Pass");

		_delay_ms(1000);
		Clear();

	}while(flag==0);    //check if pass is correct

}



/************************************************Step2*************************************************/
void Open_Door();
void Change_Password();
void Security_System_Error();

void Main_System_Optains(Timer1_ConfigType* Timer)
{
	Timer_Ptr=Timer;
	uint8 sign;
	LCD_displayStringRowColumn(0,0,"+ : Open Door");
	LCD_displayStringRowColumn(1,0,"- : Change Pass");
	sign=KEYPAD_getPressedKey();

	Clear();

	if(sign=='+')
	{
		Ready_To_Send();
		UART_sendByte(plus);
		Open_Door();
	}
	else if(sign=='-')
	{
		Ready_To_Send();
		UART_sendByte(minus);
		Change_Password();
	}
}



/************************************************Step3*************************************************/
void Open_Door()
{
	uint8 pass[5];
	uint8 check;
	for(uint8 j=0;j<3;j++)
	{
		//Displaying
		LCD_displayStringRowColumn(0,0,"plz enter pass:");

		//taking password
		LCD_moveCursor(1,0);
		Taking_Password(pass);
		Clear();

		Ready_To_Send();
		for(uint8 i=0;i<5;i++)            //send pass to compare with pass in eeprom
		{
			UART_sendByte(pass[i]);
		}


		Ready_To_Recieve();
		check=UART_recieveByte();               //to check if the passwords matched

		Clear();

		if(check==0)
		{
			LCD_displayStringRowColumn(0,0,"Unmatched Pass");
			_delay_ms(1000);
			Clear();
		}
		else
		{
			LCD_displayStringRowColumn(0,0,"Matched Pass");
			_delay_ms(1000);
			Clear();
			break;
		}
	}

	if(check==1)
	{
		TIMER1_g_ticks=0;
		Timer1_init(Timer_Ptr);

		while(TIMER1_g_ticks<com1)
			LCD_displayStringRowColumn(0,0,"Unlocking Door");
		Clear();

		while(TIMER1_g_ticks<com2)
			LCD_displayStringRowColumn(0,0,"Holding...");
		Clear();

		while(TIMER1_g_ticks<com3)
			LCD_displayStringRowColumn(0,0,"Locking Door");
		Clear();

		Timer1_deInit();
	}
	else if(check==0)
		Security_System_Error();
}




/************************************************Step4*************************************************/
void Change_Password()
{
	uint8 pass[5];
	boolean check=0;
	for(uint8 j=0;j<3&&check!=1;j++)
	{
		//Displaying
		LCD_displayStringRowColumn(0,0,"plz enter pass:");
		_delay_ms(1000);

		//taking password
		LCD_moveCursor(1,0);
		Taking_Password(pass);
		Clear();

		Ready_To_Send();
		for(uint8 i=0;i<5;i++)            //send pass to compare with pass in eeprom
			UART_sendByte(pass[i]);



		Ready_To_Recieve();
		check=UART_recieveByte();               //to check if the passwords matched

		Clear();

		if(check==0)
			LCD_displayStringRowColumn(0,0,"Unmatched Pass");
		else
			LCD_displayStringRowColumn(0,0,"Matched Pass");

		_delay_ms(1000);
		Clear();
	}


	if(check==1)
	{
		Create_Password();
	}
	else if(check==0)
		Security_System_Error();
}


/************************************************Step5*************************************************/
void Security_System_Error()
{
	TIMER1_g_ticks=0;
	Timer1_init(Timer_Ptr);
	while(TIMER1_g_ticks<com4)
		LCD_displayStringRowColumn(0,0,"ERROR!!!");
	Clear();
	Timer1_deInit();
}











