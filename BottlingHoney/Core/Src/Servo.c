/*
 * Servo.c
 *
 *  Created on: Feb 22, 2025
 *  The MIT License.
 *      Author: Szymon Frydrych
 *      szfrydrych@gmail.com
 */
#include "main.h"
#include "Servo.h"
#include "Honey_StateMachine.h"

void Servo_Init(TServo* Servo, TIM_HandleTypeDef *htim, uint32_t Channel, uint8_t InitSignal)
{
	Servo->servo_tim = htim;
	Servo->Channel = Channel;
	Servo->InitSignal = InitSignal;

	HAL_TIM_PWM_Start(Servo->servo_tim, Servo->Channel);
	__HAL_TIM_SET_COMPARE(Servo->servo_tim, Servo->Channel, InitSignal * OFFSET);
}

void Servo_SetPWMSignal(TServo* Servo, uint8_t Signal)
{
	__HAL_TIM_SET_COMPARE(Servo->servo_tim, Servo->Channel, Signal * OFFSET);
}
