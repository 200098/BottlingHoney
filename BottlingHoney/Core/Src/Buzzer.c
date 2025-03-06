/*
 * Buzzer.c
 *
 *  The MIT License.
 *  Created on: 2.12.2024
 *      Author: Szymon Frydrych
 *      szfrydrych@gmail.com
 */

#include "main.h"
#include "Buzzer.h"

/*
 * Initialization of buzzer
 */


void BuzzerInit(TBuzzer* Buzzer, GPIO_TypeDef* GpioPort, uint16_t GpioPin)
{
	Buzzer->GpioPort = GpioPort;
	Buzzer->GpioPin = GpioPin;
	HAL_GPIO_WritePin(Buzzer->GpioPort, Buzzer->GpioPin, GPIO_PIN_RESET);
}

/*
 * Setting time of signal in ms
 */
void BuzzerSetSignalTime(TBuzzer* Buzzer, uint32_t TimeToSet)
{
	Buzzer->LastTick = HAL_GetTick();
	Buzzer->SignalTime = TimeToSet;
}

/*
 * Play signal by buzzer
 */

void BuzzerPlay(TBuzzer* Buzzer,TPlayPressed PlaySignal)
{
	switch(PlaySignal)
	{
		case PRESSED:
			HAL_GPIO_WritePin(Buzzer->GpioPort, Buzzer->GpioPin, GPIO_PIN_SET);
			BuzzerSetSignalTime(Buzzer, PRESSED_TIME_MS);
			break;
		case CHANGE_STEP:
			HAL_GPIO_WritePin(Buzzer->GpioPort, Buzzer->GpioPin, GPIO_PIN_SET);
			BuzzerSetSignalTime(Buzzer, CHANGE_STEP_TIME_MS);
			break;
		case FINISH:
			HAL_GPIO_WritePin(Buzzer->GpioPort, Buzzer->GpioPin, GPIO_PIN_SET);
			BuzzerSetSignalTime(Buzzer, FINISH_TIME_MS);
			break;
		case STOP:
			if (HAL_GetTick() - Buzzer->LastTick >= Buzzer->SignalTime)
				HAL_GPIO_WritePin(Buzzer->GpioPort, Buzzer->GpioPin, GPIO_PIN_RESET);
			break;
	}
}
