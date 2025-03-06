/*
 * Honey_Display.h
 *
 *  Created on: Mar 4, 2025
 *  The MIT License.
 *      Author: Szymon Frydrych
 *      szfrydrych@gmail.com
 */

#ifndef INC_HONEY_DISPLAY_H_
#define INC_HONEY_DISPLAY_H_

/*
 * Enum for display without parameters
 */
typedef enum
{
	DISPLAY_IDLE,
	DISPLAY_REMOVE_ALL_FROM_DESK,
	DISPLAY_MEASURING,
	DISPLAY_PUT_REFERENCE,
	DISPLAY_SAVE_TO_EEPROM,
	DISPLAY_PREPERE_START,
	DISPLAY_WRONG_CALIBRATION,
	DISPLAY_PUT_JAR,
	DISPLAY_EMERGENCY_CLOSE

}THoneyDisplayWOParameter;

/*
 * Enum for display with parameters
 */
typedef enum
{
	DISPLAY_MAIN_MENU,
	DISPLAY_BOTTLING,
	DISPLAY_END,
}THoneyDisplayWithParameter;

/*
 * Prototypes
 */

void DisplayInit(I2C_HandleTypeDef *i2c);

void DisplayWithoutParameters(THoneyDisplayWOParameter Display);

void DisplayWithParameters(THoneyDisplayWithParameter Display, THoney* Honey, int32_t ActualWeight);


#endif /* INC_HONEY_DISPLAY_H_ */
