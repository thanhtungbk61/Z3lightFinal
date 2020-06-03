/*
 * userPeripheral.h
 *
 *  Created on: Apr 23, 2020
 *      Author: who_you_are
 */

#ifndef USERPERIPHERAL_H_
#define USERPERIPHERAL_H_
#include "af.h"
#include "em_timer.h"
// define for pwm
#define LED_PORT  gpioPortC
#define LED_PIN    9
#define TIMER_TOP                   100
#define TIMER_CHANNEL               0
#define  DUTY_CYCLE_ 10

uint16_t dimmingValue;
void pwmInit(void);
void setLevel(uint16_t level);
#endif /* USERPERIPHERAL_H_ */
