/*
 * Button.c
 *
 *  Created on: 2.12.2024
 *  The MIT License.
 *      Author: Szymon Frydrych
 *      szfrydrych@gmail.com
 */
#include "main.h"
#include "stdbool.h"
#include "Button.h"


/*
 * Initialization of button
 */
void ButtonInit(TButton* Button, GPIO_TypeDef* GpioPort, uint16_t GpioPin)
{
	Button->GpioPort = GpioPort;
	Button->GpioPin = GpioPin;
	Button->LastTick = 0;
	Button->State = IDLE_BUTTON;
	Button->TimerDebounce = DEBOUNCE_TIME_MS;
	Button->IsPressed = false;
	Button->PressedAfterDebounce = false;
}

void ButtonHandleIRQ(TButton* Button)
{
	Button->IsPressed = true;
	Button->LastTick = HAL_GetTick();
}

/*
 * Button State Machine
 */
void ButtonTask(TButton* Button)
{
	switch(Button->State)
	{
		case IDLE_BUTTON:
			if(true==Button->IsPressed)
			{
				Button->State= DEBOUNCE_BUTTON;
			}
			break;
		case DEBOUNCE_BUTTON:
			if (HAL_GetTick() - Button->LastTick >= Button->TimerDebounce)
			{
				Button->LastTick = HAL_GetTick();
				if(BUTTON_PRESSED == HAL_GPIO_ReadPin(Button->GpioPort, Button->GpioPin))
				{
					Button->State= PRESSED_BUTTON;
					Button->PressedAfterDebounce = true;
				}
				else
				{
					Button->State= IDLE_BUTTON;
				}
			}
			Button->IsPressed = false;
			break;
		case PRESSED_BUTTON:
			if(BUTTON_RELEASED == HAL_GPIO_ReadPin(Button->GpioPort, Button->GpioPin))
			{
				Button->State= IDLE_BUTTON;
			}
			break;
	}
}

/*
 * Read actual state of button
 */

_Bool ButtonIsPressed(TButton* Button)
{
	if(Button->PressedAfterDebounce)
	{
		Button->PressedAfterDebounce = false;
		return true;
	}
	return false;
}
