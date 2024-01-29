/*
 * Functions.h
 *
 *  Created on: Nov 5, 2022
 *      Author: mustafa
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include"keypad.h"
#include"lcd.h"
#include"uart.h"
#include"timer1.h"
#include <avr/io.h> /* To use the SREG register */
#include <util/delay.h>
#define MCU1_Ready 1
#define MCU2_Ready 2

#define plus  3
#define minus 4

#define OVF_init 42098
Timer1_ConfigType* Timer_Ptr;

uint16 TIMER1_g_ticks;

#define CTC_MODE             //for Compare mode

void Create_Password();
void Wait_CTC();
void Wait_OVF();
void Main_System_Optains(Timer1_ConfigType* Timer_Ptr);

#endif /* FUNCTIONS_H_ */
