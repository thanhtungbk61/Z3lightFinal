/*
 * userMemory.h
 *
 *  Created on: Dec 13, 2019
 *      Author: who_you_are
 */
#ifndef USERFLASH_H_
#define USERFLASH_H_

#include "stdint.h"
#include "app/framework/include/af.h"
#include "userCharStruct.h"

#define USERDATA 				((uint32_t*)USERDATA_BASE)



#define FLASHMAX 45

//typedef struct
//{
//	uint32_t x;
//	uint16_t y;
//} Sub;


Sub ramSubData[48];
Sub readSubRam(uint16_t add );

void writeCountUsed();
void writeFlash(Sub data);
void deleteFlash(uint16_t add);
void flashToRam();
void ramToFlash();
#endif /* USERFLASH_H_ */
