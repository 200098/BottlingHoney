/*
 * Honey_Eeprom.h
 *
 *  Created on: Feb 21, 2025
 *  The MIT License.
 *      Author: Szymon Frydrych
 *      szfrydrych@gmail.com
 */

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_

#include "Honey_StateMachine.h"

/*
 * Definitions
 */
#define EEPROM_ADDRESS				((0x50)<<1)
#define EEPROM_REGISTER 			0x01

#define EEPROM_TIMEOUT				1000

/*
 * Prototypes
 */
void Eeprom_Init(I2C_HandleTypeDef *hi2c);

TCalibration Eeprom_ReadCalibration(void);

void Eeprom_SendCalibration(TCalibration Calibration);

void Eeprom_WriteData(uint8_t *TableToSend);


#endif /* INC_EEPROM_H_ */
