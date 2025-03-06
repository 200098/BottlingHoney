/*
 * Honey_Display.c
 *
 *  Created on: Mar 4, 2025
 *  The MIT License.
 *      Author: Szymon Frydrych
 *      szfrydrych@gmail.com
 */

#include "main.h"
#include "SSD1306_OLED.h"
//#include "tim.h"

#include "GFX_BW.h"
#include "stdio.h"
//#include "Eeprom.h"
//
//#include "Servo.h"

#include "Honey_StateMachine.h"

#include "stdbool.h"

//#include "Button.h"

#include "fonts/fonts.h"
//#include "HX711.h"
//#include "Buzzer.h"
#include "Honey_Display.h"

/*
 * Table to handle string
 */
char text[32];

/*
 * Initialization of display with default values
 */

void DisplayInit(I2C_HandleTypeDef *i2c)
{
	SSD1306_Init(i2c);
	GFX_SetFont(font_8x5);
	GFX_SetFontSize(1);
	SSD1306_Clear(BLACK);
}

/*
 * Display messages without parameters
 */
void DisplayWithoutParameters(THoneyDisplayWOParameter Display)
{
	switch(Display)
	{
		case DISPLAY_IDLE:
		{
			SSD1306_Clear(BLACK);
			GFX_SetFontSize(2);
			GFX_DrawString(20 , 20, "Start up", WHITE, BLACK);
			SSD1306_Display();
			GFX_SetFontSize(1);
			break;
		}
		case DISPLAY_REMOVE_ALL_FROM_DESK:
		{
			SSD1306_Clear(BLACK);
			GFX_SetFontSize(2);
			GFX_DrawString(10 , 15, "Remove All", WHITE, BLACK);
			GFX_SetFontSize(1);
			GFX_DrawString(30 ,40, "And Click ONE", WHITE, BLACK);
			SSD1306_Display();
			GFX_SetFontSize(1);
			break;
		}
		case DISPLAY_MEASURING:
		{
			SSD1306_Clear(BLACK);
			GFX_SetFontSize(1);
			GFX_DrawString(30 , 30, "Measuring...", WHITE, BLACK);
			SSD1306_Display();
			GFX_SetFontSize(1);
			break;
			break;
		}
		case DISPLAY_PUT_REFERENCE:
		{
			SSD1306_Clear(BLACK);
			GFX_SetFontSize(2);
			GFX_DrawString(15 , 15, "Put 1000g", WHITE, BLACK);
			GFX_SetFontSize(1);
			GFX_DrawString(30 ,40, "And Click ONE", WHITE, BLACK);
			SSD1306_Display();
			GFX_SetFontSize(1);
			break;
		}
		case DISPLAY_SAVE_TO_EEPROM:
		{
			SSD1306_Clear(BLACK);
			GFX_SetFontSize(1);
			GFX_DrawString(15 , 10, "Save calibration", WHITE, BLACK);
			GFX_DrawString(35 , 25, "to EEPROM", WHITE, BLACK);
			GFX_SetFontSize(1);
			GFX_DrawString(30 ,50, " Click ONE", WHITE, BLACK);
			SSD1306_Display();
			GFX_SetFontSize(1);
			break;
			break;
		}
		case DISPLAY_PREPERE_START:
		{
			SSD1306_Clear(BLACK);
			GFX_SetFontSize(2);
			GFX_DrawString(10 , 15, "Prepere to", WHITE, BLACK);
			GFX_DrawString(40 ,40, "START", WHITE, BLACK);
			SSD1306_Display();
			GFX_SetFontSize(1);
			break;
			break;
		}
		case DISPLAY_WRONG_CALIBRATION:
		{
			SSD1306_Clear(BLACK);
			GFX_SetFontSize(2);
			GFX_DrawString(40 , 15, "Wrong", WHITE, BLACK);
			GFX_DrawString(5 ,40, "Calibration", WHITE, BLACK);
			SSD1306_Display();
			GFX_SetFontSize(1);
			break;
		}
		case DISPLAY_PUT_JAR:
		{
			SSD1306_Clear(BLACK);
			GFX_SetFontSize(2);
			GFX_DrawString(05 , 20, "Put the JAR", WHITE, BLACK);
			SSD1306_Display();
			GFX_SetFontSize(1);
			break;
		}
		case DISPLAY_EMERGENCY_CLOSE:
		{
			SSD1306_Clear(BLACK);
			GFX_SetFontSize(2);
			GFX_DrawString(10 , 15, "Emergency", WHITE, BLACK);
			GFX_DrawString(30 ,40, "Close", WHITE, BLACK);
			SSD1306_Display();
			GFX_SetFontSize(1);
			break;
		}
	}
}

/*
 * Display messages with parameters
 */
void DisplayWithParameters(THoneyDisplayWithParameter Display, THoney* Honey, int32_t ActualWeight)
{
	switch(Display)
	{
		case DISPLAY_MAIN_MENU:
		{
			SSD1306_Clear(BLACK);
			GFX_DrawRectangle(01, 19, 127, 43, WHITE);
			GFX_DrawRectangle(01, 30, 60, 15, WHITE);
			GFX_DrawRectangle(01, 47, 60, 15, WHITE);
			GFX_DrawRectangle(68, 30, 60, 15, WHITE);
			GFX_DrawRectangle(68, 47, 60, 15, WHITE);

			GFX_SetFontSize(1);
			GFX_DrawString(5 , 1, "Actual", WHITE, BLACK);
			GFX_DrawString(5 , 9, "weight", WHITE, BLACK);
			GFX_DrawString(5 , 21, "Options:", WHITE, BLACK);
			GFX_DrawString(5 , 34, "1- Calib", WHITE, BLACK);
			GFX_DrawString(71 , 34, "2- 500g ", WHITE, BLACK);
			GFX_DrawString(5 , 51, "3- 1000g ", WHITE, BLACK);
			GFX_DrawString(71 , 51, "4- Close", WHITE, BLACK);

			GFX_SetFontSize(2);
			GFX_DrawString(42, 1, ":" , WHITE, BLACK);
			GFX_SetFontSize(2);
			sprintf(text, "%4dg", (int)ActualWeight);
			GFX_DrawString(50, 1, text , WHITE, BLACK);
			//GFX_DrawString(25 , 18, "Choose option", WHITE, BLACK);

			GFX_SetFontSize(1);
			SSD1306_Display();

			break;
		}
		case DISPLAY_END:
		case DISPLAY_BOTTLING:
		{
			SSD1306_Clear(BLACK);
			GFX_SetFontSize(1);
			sprintf(text, "Target:%d g", (int)Honey->Bottling.TargetWeight);
			GFX_DrawString(25, 5, text , WHITE, BLACK);
			GFX_SetFontSize(4);
			sprintf(text, "%4dg", (int)ActualWeight);
			GFX_DrawString(5, 25, text , WHITE, BLACK);
			SSD1306_Display();
			GFX_SetFontSize(1);
			break;
		}
	}
}
