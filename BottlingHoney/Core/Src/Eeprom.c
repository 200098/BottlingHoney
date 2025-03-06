/*
 * Honey_Eeprom.c
 *
 *  Created on: Feb 21, 2025
 *  The MIT License.
 *      Author: Szymon Frydrych
 *      szfrydrych@gmail.com
 */
#include "main.h"
#include "Eeprom.h"
#include "Honey_StateMachine.h"

I2C_HandleTypeDef *eeprom_i2c;

/*
 * Initialization of EEPROM
 */

void Eeprom_Init(I2C_HandleTypeDef *i2c)
{
	eeprom_i2c = i2c;
}

/*
 * Read calibration of HX711 saved to EEPROM
 */

TCalibration Eeprom_ReadCalibration(void)
{
	uint8_t ReadDataTable[8];
	TCalibration Calibration;

	HAL_I2C_Mem_Read(eeprom_i2c, EEPROM_ADDRESS, EEPROM_REGISTER, 1, ReadDataTable, 8, EEPROM_TIMEOUT);
	Calibration.ReferenceEmptyWeight = ReadDataTable[3] | (ReadDataTable[2] << 8) | (ReadDataTable[1] << 16) | (ReadDataTable[0] << 24);
	Calibration.CalibValue = ReadDataTable[7] | (ReadDataTable[6] << 8) | (ReadDataTable[5] << 16) | (ReadDataTable[4] << 24);

	return Calibration;
}

/*
 * Saved to EEPROM new calibration of HX711
 */

void Eeprom_SendCalibration(TCalibration Calibration)
{
	uint8_t WriteDataTable[8];

	WriteDataTable[0]=(Calibration.ReferenceEmptyWeight >> 24) & 0xFF;
	WriteDataTable[1]=(Calibration.ReferenceEmptyWeight >> 16) & 0xFF;
	WriteDataTable[2]=(Calibration.ReferenceEmptyWeight >> 8) & 0xFF;
	WriteDataTable[3]=(Calibration.ReferenceEmptyWeight) & 0xFF;

	WriteDataTable[4]=(Calibration.CalibValue >> 24) & 0xFF;
	WriteDataTable[5]=(Calibration.CalibValue >> 16) & 0xFF;
	WriteDataTable[6]=(Calibration.CalibValue >> 8) & 0xFF;
	WriteDataTable[7]=(Calibration.CalibValue) & 0xFF;

	Eeprom_WriteData(WriteDataTable);
}

/*
 * Send Table to EEPROM
 */

void Eeprom_WriteData(uint8_t *TableToSend)
{
	HAL_I2C_Mem_Write(eeprom_i2c, EEPROM_ADDRESS, EEPROM_REGISTER, 1, TableToSend, 8, EEPROM_TIMEOUT);
}

