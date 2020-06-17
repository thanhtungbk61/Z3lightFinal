/*
 * userCommand.h
 *
 *  Created on: Apr 27, 2020
 *      Author: who_you_are
 */

#ifndef USERCOMMAND_H_
#define USERCOMMAND_H_

/*
 * userCommand.c
 *
 *  Created on: Dec 16, 2019
 *      Author: who_you_are
 */

#include "af.h"
#include "userFlashV2.h"

#define NIGHT 	0
#define DAY		1
volatile uint8_t dayState;

uint8_t getPing(uint8_t* value);
uint8_t reportPing(uint8_t* value);
uint8_t addGroupRespond(uint8_t stt,EmberNodeId nodeid,uint16_t groupId);
//
void sendAddGroupCommand(uint16_t groupId,uint8_t* groupName,uint16_t destination);
void addGroup();

uint8_t reportSensor();
uint8_t reportLevelAttribute();
uint8_t reportLightAttribute();
uint8_t reportDimming();
uint8_t reportOnOffSchAttribute();


#endif /* USERCOMMAND_H_ */
