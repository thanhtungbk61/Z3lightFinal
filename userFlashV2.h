/*
 * userFlashV2.h
 *
 *  Created on: Apr 19, 2020
 *      Author: who_you_are
 */

#ifndef USERFLASHV2_H_
#define USERFLASHV2_H_

#include "stdint.h"
#include "app/framework/include/af.h"
#include "userCharStruct.h"
#include "userJsonStruct.h"

#define USERDATAV2 				((uint32_t*)USERDATA_BASE)

#define ONOFFSCHEDULEDATA				(uint32_t*)(USERDATA_BASE)//GROUPDATA
#define GROUPSCHDATA 					(uint32_t*)(USERDATA_BASE+336)  // ONOFFSCHEDULEMAX*ONOFFSCHEDULEDATA*FLASHMAXV2
#define DIMMINGSCHEDULEDATA     (uint32_t*)(USERDATA_BASE+636)  // ONOFFSCHEDULEMAX*ONOFFSCHEDULEDATA*FLASHMAXV2 +GROUPSCHDATA...


#define ONOFFSCHEDULEMAX 16   // 48/16
#define GROUPSCHMAX      50   // 48/2
#define DIMMINGSCHMAX    16    // 48/16
//
#define FLASHMAXV2 3
#define ONOFFSCHEDULESIZE 7   // 48/16
#define GROUPSCHSIZE      2   // 48/2
#define DIMMINGSCHSIZE    8    // 48/16

#define SELFADDRESS		  0xFFFE
typedef enum
{
	groupSch =0,
	onOffSch,
	dimmingSch
}typeSch;
//v2
// ramData
schedule_onoff_t onOffSchRam[ONOFFSCHEDULEMAX];
schedule_dimming_t dimmingSchRam[DIMMINGSCHMAX];
group_t  groupSchRam[GROUPSCHMAX];

// v2.1
void updateFlash(char* String,uint8_t type); // use for dimming onoff and group when write flash max time ,typeSch type

// onoffsch function
void writeOnOffSch2FlashV2(char* str);
void onOfffSchFlash2RamV2();
//
void deletePeriousOnOffSch(uint8_t pointer);
void resetOnOffSchRam();


// dimming_schedule
void writeDimmingSch2FlashV2(char* str);
void dimmingSchFlash2RamV2();
//
void deletePeriousDimmingSch(uint8_t pointer);
void resetDimmingSchRam();


// group sch
void writeGroupSch2FlashV2(char* str);
void groupSchFlash2RamV2();
//
void deletePeriousGroupSch(uint8_t pointer);
void resetGroupSchRam();
#endif /* USERFLASHV2_H_ */

