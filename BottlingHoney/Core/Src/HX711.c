/*
 * HX711.c
 *
 *  Created on: Feb 22, 2025
 *  The MIT License.
 *      Author: Szymon Frydrych
 *      szfrydrych@gmail.com
 */
#include "main.h"
#include "Honey_StateMachine.h"
#include "HX711.h"

/*
 * Initialization peripheral for HX711
 */
void HX711_Init(TIM_HandleTypeDef *htim)
{
	HAL_TIM_Base_Start(htim);
	HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_RESET);
	HAL_Delay(10);
}

/*
 * Read raw data, code from documentation (update 05.03.2025)
 * https://cdn.sparkfun.com/datasheets/Sensors/ForceFlex/hx711_english.pdf
 */
int32_t HX711_getRawData(void)
{
	  uint32_t data = 0;
	  while(HAL_GPIO_ReadPin(DT_PORT, DT_PIN) == GPIO_PIN_SET)
	  {
	  }

	  for(int8_t len=0; len<24 ; len++)
	  {
	    HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_SET);
	    data = data << 1;
	    HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_RESET);
	    if(HAL_GPIO_ReadPin(DT_PORT, DT_PIN) == GPIO_PIN_SET)
	    {
	    	data ++;
	    }
	  }

	  HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_SET);
	  data = data ^ 0x800000;
	  HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_RESET);

	  return data;

}

/*
 * Calculate average weight
 */

int32_t HX711_getAverageWeight(uint8_t NumberOfSamples)
{
	int32_t  total = 0;
	for(uint16_t i=0 ; i<NumberOfSamples ; i++)
	{
		total += HX711_getRawData();
    }
	int32_t average = (int32_t)(total / NumberOfSamples);
	return average;
}

/*
 * Calculate weight to milligrams
 */

int32_t HX711_getCalculatedWeight(TCalibration Calibration)
{
  int32_t  average;
  int milligram;

  average = HX711_getAverageWeight(BOTTLING_NUM_OF_PROBES);

  milligram = (int32_t)((average-Calibration.ReferenceEmptyWeight)/Calibration.CalibValue);
  if(milligram > MAXIMUM_WEIGHT || milligram < MINIMUM_WEIGHT)
  {
	  return 0;
  }
  return milligram;
}

/*
 * Prepere calibration of HX711 when reference weight is on the platform
 */

TCalibration HX711_calibration(TCalibration CalibrationWithEmptyWeight)
{
	TCalibration Calibration;
	int weightOfReference = HX711_getAverageWeight(CALIBRATION_NUM_OF_PROBES);
	Calibration.ReferenceEmptyWeight = CalibrationWithEmptyWeight.ReferenceEmptyWeight;
	Calibration.CalibValue = (int)((weightOfReference-CalibrationWithEmptyWeight.ReferenceEmptyWeight)/OWN_REFERENCE_WEIGHT_GRAMS);

	return Calibration;
}






