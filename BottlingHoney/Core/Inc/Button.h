/*
 * Button.h
 *
 *  The MIT License.
 *  Created on: 22.02.2025
 *      Author: Szymon Frydrych
 *      szfrydrych@gmail.com
 */

#ifndef INC_FONTS_BUTTON_H_
#define INC_FONTS_BUTTON_H_

/*
 * Definitions
 */

#define DEBOUNCE_TIME_MS 10
#define BUTTON_PRESSED 0
#define BUTTON_RELEASED 1

/*
 * Button's states
 */
typedef enum
{
	IDLE_BUTTON = 0,
	DEBOUNCE_BUTTON,
	PRESSED_BUTTON,
}TButtonState;

/*
 * Struct of button
 */
typedef struct
{
	TButtonState 	State;

	GPIO_TypeDef* 	GpioPort;
	uint16_t 		GpioPin;

	uint32_t 		LastTick;
	uint32_t 		TimerDebounce;

	_Bool 			IsPressed;
	_Bool  PressedAfterDebounce;

}TButton;

/*
 * Prototypes
 */
void ButtonInit(TButton* Button, GPIO_TypeDef* GpioPort, uint16_t GpioPin);
void ButtonHandleIRQ(TButton* Button);
void ButtonTask(TButton* Button);
_Bool ButtonIsPressed(TButton* Button);


#endif /* INC_FONTS_BUTTON_H_ */
