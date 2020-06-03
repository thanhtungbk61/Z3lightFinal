/*
 * userRTCC.c
 *
 *  Created on: Mar 24, 2020
 *      Author: who_you_are
 */
#include"userRTCC.h"

static uint16_t cal_year;
static uint8_t cal_month;
static uint8_t cal_day;
static uint8_t cal_weekday;
static uint8_t cal_hour;
static uint8_t cal_min;
static uint8_t cal_sec;
static uint16_t cal_ms;
static uint16_t cal_tick;
//static int8_t cal_time_zone;
//static uint8_t cal_dst;

static uint32_t last_RTCC_value;

void update_calendar()
{
  uint32_t ticks, ticks_since_last;
  uint8_t diff_day, diff_hour, diff_min, diff_sec;
  uint16_t diff_tick;// diff_sec

  ticks = RTCC_CounterGet();
  ticks_since_last = ticks - last_RTCC_value;   // 32768*2 +5 -  0= 32768*2 +5
  last_RTCC_value = ticks;                       //32768*2 +5

  diff_tick = (ticks_since_last) % TICKS_PER_SECOND; //5
  diff_sec = (ticks_since_last / TICKS_PER_SECOND) % 60;//2
  diff_min = (ticks_since_last / TICKS_PER_SECOND / 60) % 60;//
  diff_hour = (ticks_since_last / TICKS_PER_SECOND / 60 / 60) % 24;
  diff_day = (ticks_since_last / TICKS_PER_SECOND / 60 / 60 / 24);

  // xu ly phan du cua cal_sec
  cal_tick += diff_tick;// 0+5
  if (cal_tick >= TICKS_PER_SECOND) {
    cal_tick -= TICKS_PER_SECOND;
    cal_sec++;
  }

  cal_ms = cal_tick * 1000 / TICKS_PER_SECOND;
  cal_sec += diff_sec;
  if (cal_sec >= 60) {
    cal_sec -= 60;
    cal_min++;
  }

  cal_min += diff_min;
  if (cal_min >= 60) {
    cal_min -= 60;
    cal_hour++;
  }

  cal_hour += diff_hour;
  if (cal_hour >= 24) {
    cal_hour -= 24;
    cal_day++;
    cal_weekday++;
  }

  cal_weekday += diff_day;
  if (cal_weekday > SUNDAY) {
    cal_weekday -= 7;
  }

  cal_day += diff_day;

  switch (cal_month) {
    case JANUARY:
    case MARCH:
    case MAY:
    case JULY:
    case AUGUST:
    case OCTOBER:
      if (cal_day > 31) {
        cal_day -= 31;
        cal_month++;
      }
      break;

    case DECEMBER:
      if (cal_day > 31) {
        cal_day -= 31;
        cal_month = JANUARY;
        cal_year++;
      }
      break;

    case APRIL:
    case JUNE:
    case SEPTEMBER:
    case NOVEMBER:
      if (cal_day > 30) {
        cal_day -= 30;
        cal_month++;
      }
      break;

    case FEBRUARY:
      // Leap year check
      if (cal_year % 4 == 0 && (cal_year % 100 != 0 || cal_year % 400 == 0)) {
        if (cal_day > 29) {
          cal_day -= 29;
          cal_month++;
        }
      } else {
        if (cal_day > 28) {
          cal_day -= 28;
          cal_month++;
        }
      }
      break;
  }
}

void set_date_and_time(uint16_t year,
                    uint8_t month,
                    uint8_t day,
                    uint8_t weekday,
                    uint8_t hour,
                    uint8_t min,
                    uint8_t sec,
                    uint16_t ms)
{
  cal_year = year;
  cal_month = month;
  cal_day = day;
  cal_weekday = weekday;
  cal_hour = hour;
  cal_min = min;
  cal_sec = sec;
  cal_ms = ms;

  last_RTCC_value = RTCC_CounterGet();
}

void get_date_and_time(uint16_t* year,
                    uint8_t* month,
                    uint8_t* day,
                    uint8_t* weekday,
                    uint8_t* hour,
                    uint8_t* min,
                    uint8_t* sec,
                    uint16_t* ms)
{
  update_calendar();
  *year = cal_year;
  *month = cal_month;
  *day = cal_day;
  *weekday = cal_weekday;
  *hour = cal_hour;
  *min = cal_min;
  *sec = cal_sec;
  *ms = cal_ms;
}
