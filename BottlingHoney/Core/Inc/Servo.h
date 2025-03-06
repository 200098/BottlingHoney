/*
 * Servo.h
 *
 *  Created on: Feb 22, 2025
 *  The MIT License.
 *      Author: Szymon Frydrych
 *      szfrydrych@gmail.com
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

/*
 * Definitions
 */
#define OFFSET 10

#define CONFIG_1

#ifdef CONFIG_1
#define MAIN_TAP_100_PERCENT_OPEN 		150
#define MAIN_TAP_30_PERCENT_OPEN 		90
#define MAIN_TAP_20_PERCENT_OPEN 		75
#define MAIN_TAP_10_PERCENT_OPEN 		65
#define MAIN_TAP_5_PERCENT_OPEN 		55
#define MAIN_TAP_CLOSED 				50

#define HELPER_TAP_OPENED				50
#define HELPER_TAP_CLOSED				150
#else
#define TAP_100_PERCENT_OPEN 			50
#define TAP_30_PERCENT_OPEN 			150
#define TAP_20_PERCENT_OPEN 			170
#define TAP_10_PERCENT_OPEN 			180
#define TAP_5_PERCENT_OPEN 				190
#define TAP_CLOSED 						200

#define HELPER_TAP_OPENED				50
#define HELPER_TAP_CLOSED				150

#endif

/*
 * Struct of servo
 */
typedef struct
{
	TIM_HandleTypeDef *servo_tim;
	uint32_t Channel;
	uint8_t InitSignal;

}TServo;

/*
 * Prototypes
 */
void Servo_Init(TServo* Servo, TIM_HandleTypeDef *htim,uint32_t Channel, uint8_t InitSignal);

void Servo_SetPWMSignal(TServo* Servo, uint8_t Signal);

#endif /* INC_SERVO_H_ */
