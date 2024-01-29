/*
 * Functions.h
 *
 *  Created on: Nov 5, 2022
 *      Author: mustafa
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include"PWM_timer.h"
#include"buzzer.h"
#include"DC_motor.h"
#include"external_eeprom.h"
#include"timer1.h"
#include"uart.h"
#include"std_types.h"
#include <avr/io.h> /* To use the SREG register */
#include <util/delay.h>
#define MCU1_Ready 1
#define MCU2_Ready 2

#define plus  3
#define minus 4

uint16 TIMER1_g_ticks;

#define OVF_init 42098
Timer1_ConfigType* Timer_Ptr;
#define CTC_MODE             //for Compare mode


void Wait_CTC();
void Wait_OVF();
void Saving_Password();
void Main_Options(Timer1_ConfigType* Timer_Ptr);

#endif /* FUNCTIONS_H_ */
