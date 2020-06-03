/*
 * userCharStruct.h
 *
 *  Created on: Dec 16, 2019
 *      Author: who_you_are
 */

#ifndef USERCHARSTRUCT_H_
#define USERCHARSTRUCT_H_

//--------------------------------START---------------------------------------
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
	GROUP =4,
    ONOFF = 6,
	LEVELCONTROL =8,
	MANAGER =0xFC10
} CLusterId;

typedef enum
{
	ONOFFATT =0

} LightAttributeID;
typedef enum
{
	TRIGGER =16,
    SUBCRIBER = 17,
	SCHEDUAL =18
} AttributeID;

#define SIZE_NAME 17
typedef struct {
	uint16_t	Address;
	uint8_t     Type;
	uint8_t	    Endpoint;
	uint16_t	ProfileID;
	uint16_t	ClusterID;
	uint16_t	AttributeID;
	uint8_t     ValueType;
	char        StrValue[8];
} Sub;

typedef struct {
	uint16_t	Address;
	uint8_t	    Type;
	uint8_t	    Endpoint;
	char	    Name[SIZE_NAME];
	uint32_t	DateHoMuSe;
	uint16_t	ProfileID;
	uint16_t	ClusterID;
	uint16_t	AttributeID;
	uint8_t     ValueType;
	char        StrValue[8];
} Schedule;

typedef enum {
    STRING = 0,
    INT8,
    INT16,
    INT32,
    INT64
} valueType_t;

int64_t getIntFromString(char* str, valueType_t type);
Sub convert2sub(char* raw);
Schedule convert2schedule(char* raw);
Sub convert2group(char* raw);

#endif /* USERCHARSTRUCT_H_ */
