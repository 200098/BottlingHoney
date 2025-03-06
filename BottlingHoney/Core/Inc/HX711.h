/*
 * HX711.h
 *
 *  Created on: Feb 22, 2025
 *  The MIT License.
 *      Author: Szymon Frydrych
 *      szfrydrych@gmail.com
 */

#ifndef INC_HX711_H_
#define INC_HX711_H_

/*
 * Definitions
 */
#define DT_PIN GPIO_PIN_8
#define DT_PORT GPIOB
#define SCK_PIN GPIO_PIN_9
#define SCK_PORT GPIOB

#define CALIBRATION_NUM_OF_PROBES 	10
#define BOTTLING_NUM_OF_PROBES 		5

#define MINIMUM_WEIGHT				0
#define MAXIMUM_WEIGHT				5000

/*
 *Set own Reference
 */
#define OWN_REFERENCE_WEIGHT_GRAMS 1261

/*
 * Prototypes
 */

int32_t HX711_getRawData(void);

int32_t HX711_getAverageWeight(uint8_t NumberOfSamples);

int32_t HX711_getCalculatedWeight(TCalibration Calibration);

TCalibration HX711_calibration(TCalibration CalibrationWithEmptyWeight);

void HX711_Init(TIM_HandleTypeDef *htim);

#endif /* INC_HX711_H_ */
