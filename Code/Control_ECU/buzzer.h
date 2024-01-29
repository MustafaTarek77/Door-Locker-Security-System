/*
 * buzzer.h
 *
 *  Created on: Nov 3, 2022
 *      Author: mustafa
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include"gpio.h"
#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define BUZZER_PORT_ID                 PORTB_ID
#define BUZZER_PIN_ID                  PIN0_ID


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void Buzzer_init(void);
void Buzzer_on(void);
void Buzzer_off(void);

#endif /* BUZZER_H_ */
