/*
 * Honey_StateMachine.h
 *
 *  Created on: 21.02.2025
 *  The MIT License.
 *      Author: Szymon Frydrych
 *      szfrydrych@gmail.com
 */

#ifndef INC_HONEY_STATEMACHINE_H_
#define INC_HONEY_STATEMACHINE_H_

/*
 * Definitions
 */
#define WEIGHT_500_GRAMS 				500
#define WEIGHT_1000_GRAMS 				1000

#define WAIT_1_MS						1
#define WAIT_2_MS						2
#define WAIT_10_MS						10
#define WAIT_20_MS						20
#define WAIT_50_MS						50
#define WAIT_100_MS						100
#define WAIT_200_MS						200
#define WAIT_1_SEC						1000
#define WAIT_2_SEC						2000
#define WAIT_4_SEC						4000

#define BOTTLING_1ST_LVL				0.75
#define BOTTLING_2ND_LVL				0.85
#define BOTTLING_3RD_LVL				0.95

#define MIN_VALUE_OF_REFERENCE			10000
#define MIN_VALUE_OF_EMPTY_JAR			100


/*
 * Honey's states
 */
typedef enum
{
	IDLE = 0,
	WAITING_FOR_CHOOSE,
	CALIBRATION_PREPERE,
	CALIBRATION_MEASURE_EMPTY,
	CALIBRATION_WAIT_FOR_REFERENCE,
	CALIBRATION_MEASURE_REFERENCE,
	CALIBRATION_SAVE_TO_EEPROM,
	BOTTLING_ENTERING_DISPLAY,
	BOTTLING_CHECK_CALIBRATION,
	BOTTLING_MAIN_ROUTINE,
	BOTTLING_CLOSE_TAP,
	BOTTLING_DISPLAY_FINISH,
	EMERGENCY_CLOSE_TAP,
	EMERGENCY_PRESENT_WARNING,
}THoneyState;

/*
 * Helper structs
 */
typedef struct
{
	uint32_t 		ReferenceEmptyWeight;
	uint32_t 		CalibValue;
}TCalibration;

typedef struct
{
	uint32_t		BeginWeight;
	uint32_t		TargetWeight;
}TBottlingValues;

/*
 * Struct of Honey
 */
typedef struct
{
	THoneyState 	State;

	TCalibration 	Calibration;
	TBottlingValues Bottling;
}THoney;

/*
 * Prototypes
 */

void HoneyInit(THoney* Honey);

void HoneyTask(THoney* Honey);

#endif /* INC_HONEY_STATEMACHINE_H_ */
