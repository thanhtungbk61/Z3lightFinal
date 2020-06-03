/*
 * userJsonStruct.h
 *
 *  Created on: Apr 19, 2020
 *      Author: who_you_are
 */

#ifndef USERJSONSTRUCT_H_
#define USERJSONSTRUCT_H_

#include <stdbool.h>
#include <stdint.h>

/*
#define BIGENDIAN
*/

//----------------- cau truc cac Attribute dac biet -----------------
//----------------- realtime -----------------
#define SIZE_REALTIME 8
typedef struct __attribute__((packed))
{
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint16_t year;
    uint8_t reserve;
} realtime_t;

realtime_t realtime_cast(char str[8]);
void realtime_string(realtime_t *time, char out[8]);

//----------------- schedule_time -----------------
#define TIME_ERROR 0x00000000
#define IS_TIME(t) (*(uint32_t*)((char*)t) != TIME_ERROR)
#define SET_TIME_ERROR(t) (*(uint32_t*)((char*)t) = TIME_ERROR)
#define SIZE_SCHEDULE_TIME 4
typedef struct __attribute__((packed))
{
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t reserve;
} schedule_time_t;

schedule_time_t schedule_time_cast(char str[4]);
void schedule_time_string(schedule_time_t *time, char out[4]);
bool schedule_time_check(schedule_time_t *time);
void set_schedule_time_error(schedule_time_t *time);

//----------------- schedule_onoff -----------------
#define SIZE_SCHEDULE_ONOFF (3 + SIZE_SCHEDULE_TIME)
typedef struct __attribute__((packed))
{
	uint8_t value;// 8bit // 16bit
    schedule_time_t time;
    uint16_t address;
} schedule_onoff_t;

schedule_onoff_t schedule_onoff_cast(char str[]);
void schedule_onoff_string(schedule_onoff_t *sch, char out[]);
bool schedule_onoff_check(schedule_onoff_t *sch);
//
void schedule_onoff_array_cast(schedule_onoff_t schs[], int n, char str[]);  // ---> luu vao bo nho
void schedule_onoff_array_string(schedule_onoff_t schs[], int n, char out[]);

//----------------- schedule_dimming -----------------
#define SIZE_SCHEDULE_DIMMING (4 + SIZE_SCHEDULE_TIME)
typedef struct __attribute__((packed))
{
    uint16_t value;
    schedule_time_t time;
    uint16_t address;
} schedule_dimming_t;

schedule_dimming_t schedule_dimming_cast(char str[]);
void schedule_dimming_string(schedule_dimming_t *sch, char out[]);
//
bool schedule_dimming_check(schedule_dimming_t *sch);
void schedule_dimming_array_cast(schedule_dimming_t schs[], int n, char str[]);
void schedule_dimming_array_string(schedule_dimming_t schs[], int n, char out[]);

//----------------- group -----------------
#define IS_GROUP(t) (*(uint16_t*)((char*)t) != 0x0000)
#define SIZE_GROUP 2
typedef struct __attribute__((packed))
{
    uint16_t address;
} group_t;

group_t group_cast(char str[]);
void group_string(group_t *gr, char out[]);
bool group_check(group_t *gr);
void group_array_cast(group_t grs[], int n, char str[]);
void group_array_string(group_t grs[], int n, char out[]);

//----------------- extended functions -----------------
#define MY_ADDRESS 0x0000
bool combine_schedule_onoff_withgroup(schedule_onoff_t schs[], int n_schs, group_t grs[], int n_grs);
bool combine_schedule_dimming_withgroup(schedule_dimming_t schs[], int n_schs, group_t grs[], int n_grs);


#endif /* USERJSONSTRUCT_H_ */
