/*
 * userRTCC.h
 *
 *  Created on: Mar 24, 2020
 *      Author: who_you_are
 */
#include <stdio.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "bsp.h"
#include "em_emu.h"
#include "em_rtcc.h"
#include "em_gpio.h"
//#include "retargetserial.h"
//#include "retargetserialconfig.h"


#define TICKS_PER_SECOND     32767
#define SUNDAY               7
enum month
{
	JANUARY=1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER

};
#ifndef USERRTCC_H_
#define USERRTCC_H_

void update_calendar();

void set_date_and_time(uint16_t year,
                    uint8_t month,
                    uint8_t day,
                    uint8_t weekday,
                    uint8_t hour,
                    uint8_t min,
                    uint8_t sec,
                    uint16_t ms);

void get_date_and_time(uint16_t* year,
                    uint8_t* month,
                    uint8_t* day,
                    uint8_t* weekday,
                    uint8_t* hour,
                    uint8_t* min,
                    uint8_t* sec,
                    uint16_t* ms);

#endif /* USERRTCC_H_ */
