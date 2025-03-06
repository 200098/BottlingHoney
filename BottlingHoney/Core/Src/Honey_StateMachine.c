/*
 * Honey_StateMachine.c
 *
 *  Created on: Feb 21, 2025
 *  The MIT License.
 *      Author: Szymon Frydrych
 *      szfrydrych@gmail.com
 */

#include "main.h"
#include "stdbool.h"

#include "Honey_StateMachine.h"
#include "SSD1306_OLED.h"
#include "GFX_BW.h"
#include "Eeprom.h"
#include "Servo.h"
#include "Button.h"
#include "HX711.h"
#include "Buzzer.h"
#include "Honey_Display.h"

extern I2C_HandleTypeDef hi2c2;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;


TServo Servo;
TServo HelperServo;
TBuzzer Buzzer;

TButton ButtonOne;
TButton ButtonTwo;
TButton ButtonThree;
TButton ButtonFour;


struct ActualWeight
{
	int actualWeightBrutto;
	int actualWeightNetto;
}Weight;

static int lastTick;

/*
 * Local functions to update display
 */
void InterinalTickTimer_Init()
{
	lastTick = HAL_GetTick();
}

_Bool InterinalTickTimer_WaitMillisecond(int32_t Milliseconds)
{
	if (HAL_GetTick() - lastTick >= Milliseconds)
	{
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		lastTick = HAL_GetTick();
		return true;
	}
	return false;
}

/*
 * Initialization of main state machine
 */

void HoneyInit(THoney* Honey)
{
	Honey->State = IDLE;
	Honey->Calibration.ReferenceEmptyWeight = 1;
	Honey->Calibration.CalibValue = 1;

	ButtonInit(&ButtonOne,GPIOC,GPIO_PIN_2);
	ButtonInit(&ButtonTwo,GPIOC,GPIO_PIN_3);
	ButtonInit(&ButtonThree,GPIOC,GPIO_PIN_1);
	ButtonInit(&ButtonFour,GPIOC,GPIO_PIN_0);

	Servo_Init(&Servo, &htim3, TIM_CHANNEL_1, MAIN_TAP_CLOSED);
	Servo_Init(&HelperServo, &htim4, TIM_CHANNEL_1, HELPER_TAP_CLOSED);

	Eeprom_Init(&hi2c2);
	DisplayInit(&hi2c2);
	HX711_Init(&htim2);
	BuzzerInit(&Buzzer,GPIOB,GPIO_PIN_0);

}

/*
 * Main state machine
 */

void HoneyTask(THoney* Honey)
{

	BuzzerPlay(&Buzzer,STOP);

	ButtonTask(&ButtonOne);
	ButtonTask(&ButtonTwo);
	ButtonTask(&ButtonThree);
	ButtonTask(&ButtonFour);


	if(ButtonIsPressed(&ButtonFour))
	{
		DisplayWithoutParameters(DISPLAY_EMERGENCY_CLOSE);
		Servo_SetPWMSignal(&Servo, MAIN_TAP_CLOSED);
		BuzzerPlay(&Buzzer,FINISH);
		Honey->State = EMERGENCY_CLOSE_TAP;
	}


	switch(Honey->State)
	{
		case IDLE:
		{
			DisplayWithoutParameters(DISPLAY_IDLE);
			if(hi2c2.State == HAL_I2C_STATE_READY)
			{
				Honey->Calibration=Eeprom_ReadCalibration();
				Honey->State = WAITING_FOR_CHOOSE;
				InterinalTickTimer_Init();
			}
			break;
		}
		case WAITING_FOR_CHOOSE:
		{
			if(InterinalTickTimer_WaitMillisecond(WAIT_20_MS))
			{
				DisplayWithParameters(DISPLAY_MAIN_MENU,Honey,(int)HX711_getCalculatedWeight(Honey->Calibration));

				if(ButtonIsPressed(&ButtonOne))
				{
					BuzzerPlay(&Buzzer,PRESSED);
					Honey->State = CALIBRATION_PREPERE;
					DisplayWithoutParameters(DISPLAY_REMOVE_ALL_FROM_DESK);
					break;
				}
				else if(ButtonIsPressed(&ButtonTwo))
				{
					Honey->Bottling.TargetWeight = (uint32_t)WEIGHT_500_GRAMS;
					Honey->State = BOTTLING_ENTERING_DISPLAY;
					break;
				}
				else if(ButtonIsPressed(&ButtonThree))
				{
					Honey->Bottling.TargetWeight = (uint32_t)WEIGHT_1000_GRAMS;
					Honey->State = BOTTLING_ENTERING_DISPLAY;
					break;
				}
			}
			break;
		}
		case CALIBRATION_PREPERE:
		{
			if(InterinalTickTimer_WaitMillisecond(WAIT_100_MS))
			{
				if(ButtonIsPressed(&ButtonOne))
				{
					BuzzerPlay(&Buzzer,PRESSED);
					Honey->State = CALIBRATION_MEASURE_EMPTY;
					DisplayWithoutParameters(DISPLAY_MEASURING);
					break;
				}
			}
			break;
		}
		case CALIBRATION_MEASURE_EMPTY:
		{
			Honey->Calibration.ReferenceEmptyWeight = (uint32_t)HX711_getAverageWeight(CALIBRATION_NUM_OF_PROBES);
			Honey->State = CALIBRATION_WAIT_FOR_REFERENCE;
			DisplayWithoutParameters(DISPLAY_PUT_REFERENCE);
			break;
		}
		case CALIBRATION_WAIT_FOR_REFERENCE:
		{
			if(ButtonIsPressed(&ButtonOne))
			{
				BuzzerPlay(&Buzzer,PRESSED);
				Honey->State = CALIBRATION_MEASURE_REFERENCE;
				DisplayWithoutParameters(DISPLAY_MEASURING);
				break;
			}
			break;
		}
		case CALIBRATION_MEASURE_REFERENCE:
		{
			Honey->Calibration = HX711_calibration(Honey->Calibration);
			Honey->State = CALIBRATION_SAVE_TO_EEPROM;
			DisplayWithoutParameters(DISPLAY_SAVE_TO_EEPROM);
			break;
		}
		case CALIBRATION_SAVE_TO_EEPROM:
		{
			if((hi2c2.State == HAL_I2C_STATE_READY)
					&&(ButtonIsPressed(&ButtonOne)))
			{
				BuzzerPlay(&Buzzer,PRESSED);
				Eeprom_SendCalibration(Honey->Calibration);
				Honey->State = IDLE;
				break;
			}
			break;
		}
		case BOTTLING_ENTERING_DISPLAY:
		{
			BuzzerPlay(&Buzzer,PRESSED);
			DisplayWithoutParameters(DISPLAY_PREPERE_START);
			Honey->State = BOTTLING_CHECK_CALIBRATION;
			break;
		}
		case BOTTLING_CHECK_CALIBRATION:
		{

			if((Honey->Calibration.ReferenceEmptyWeight) < MIN_VALUE_OF_REFERENCE)
			{
				/*
				 * Some error with calibration.
				 * Need to create new one
				 */
				BuzzerPlay(&Buzzer,CHANGE_STEP);
				DisplayWithoutParameters(DISPLAY_WRONG_CALIBRATION);
				Honey->State = EMERGENCY_PRESENT_WARNING;
				break;
			}

			Honey->Bottling.BeginWeight = (int)HX711_getCalculatedWeight(Honey->Calibration);

			if(Honey->Bottling.BeginWeight < MIN_VALUE_OF_EMPTY_JAR)
			{
				/*
				 * Platform is empty
				 */
				BuzzerPlay(&Buzzer,CHANGE_STEP);
				DisplayWithoutParameters(DISPLAY_PUT_JAR);
				Honey->State = EMERGENCY_PRESENT_WARNING;
				break;

			}

			Servo_SetPWMSignal(&HelperServo, HELPER_TAP_OPENED);

			if(InterinalTickTimer_WaitMillisecond(WAIT_2_SEC))
			{
				Servo_SetPWMSignal(&Servo, MAIN_TAP_100_PERCENT_OPEN);
				Honey->State = BOTTLING_MAIN_ROUTINE;
			}

			break;
		}
		case BOTTLING_MAIN_ROUTINE:
		{
			if(InterinalTickTimer_WaitMillisecond(WAIT_10_MS))
			{
				Weight.actualWeightBrutto = HX711_getCalculatedWeight(Honey->Calibration);
				Weight.actualWeightNetto = Weight.actualWeightBrutto - Honey->Bottling.BeginWeight;

				DisplayWithParameters(DISPLAY_BOTTLING,Honey,Weight.actualWeightNetto);

				if(Weight.actualWeightNetto > (BOTTLING_3RD_LVL)*Honey->Bottling.TargetWeight)
				{
					Servo_SetPWMSignal(&Servo, MAIN_TAP_CLOSED);
					BuzzerPlay(&Buzzer,FINISH);
					DisplayWithParameters(DISPLAY_END,Honey,Weight.actualWeightNetto);
					Honey->State = BOTTLING_CLOSE_TAP;
					break;
				}
				else if(Weight.actualWeightNetto > (BOTTLING_2ND_LVL)*Honey->Bottling.TargetWeight)
				{
					Servo_SetPWMSignal(&Servo, MAIN_TAP_10_PERCENT_OPEN);
					break;

				}
				else if(Weight.actualWeightNetto > (BOTTLING_1ST_LVL)*Honey->Bottling.TargetWeight)
				{
					Servo_SetPWMSignal(&Servo, MAIN_TAP_20_PERCENT_OPEN);
					break;
				}
			}
			break;
		}
		case BOTTLING_CLOSE_TAP:
		{
			if(InterinalTickTimer_WaitMillisecond(WAIT_2_SEC))
			{
				Servo_SetPWMSignal(&HelperServo, HELPER_TAP_CLOSED);
				Honey->State = BOTTLING_DISPLAY_FINISH;
			}
			break;
		}
		case BOTTLING_DISPLAY_FINISH:
		{
			if(InterinalTickTimer_WaitMillisecond(WAIT_2_SEC))
			{
				Honey->State = WAITING_FOR_CHOOSE;
			}
			break;
		}
		case EMERGENCY_CLOSE_TAP:
		{
			if(InterinalTickTimer_WaitMillisecond(WAIT_2_SEC))
			{
				Servo_SetPWMSignal(&HelperServo, HELPER_TAP_CLOSED);
				Honey->State = EMERGENCY_PRESENT_WARNING;
			}
			break;
		}
		case EMERGENCY_PRESENT_WARNING:
		{
			if(InterinalTickTimer_WaitMillisecond(WAIT_4_SEC))
			{
				Honey->State = WAITING_FOR_CHOOSE;
			}
			break;
		}

	}
}
