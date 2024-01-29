/*
 * buzzer.c
 *
 *  Created on: Nov 3, 2022
 *      Author: mustafa
 */

#include"buzzer.h"

/*
Description
⮚ Setup the direction for the buzzer pin as output pin through the
GPIO driver.
⮚ Turn off the buzzer through the GPIO.
*/
void Buzzer_init()
{
	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, 0);
}


/*
Description
⮚ Function to enable the Buzzer through the GPIO.
*/
void Buzzer_on()
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, 1);
}

/*
Description
⮚ Function to disable the Buzzer through the GPIO.
*/
void Buzzer_off()
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, 0);
}
