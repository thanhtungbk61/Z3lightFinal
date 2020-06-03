/*
 * userJsonStruct.c
 *
 *  Created on: Apr 19, 2020
 *      Author: who_you_are
 */

#include "userJsonStruct.h"

//----------------------------------- realtime -----------------------------------------
realtime_t realtime_cast(char str[])
{
    char endian[SIZE_REALTIME];
#ifdef BIGENDIAN
    for (int i = 0; i < SIZE_REALTIME; i++)
    {
        endian[i] = str[i];
    }
#else
    for (int i = 0; i < SIZE_REALTIME; i++)
    {
        endian[i] = str[SIZE_REALTIME - 1 - i];
    }
#endif
    return *(realtime_t *)endian;
}

void realtime_string(realtime_t *time, char out[])
{
#ifdef BIGENDIAN
    for (int i = 0; i < SIZE_REALTIME; i++)
    {
        out[i] = ((char *)time)[i];
    }
#else
    for (int i = 0; i < SIZE_REALTIME; i++)
    {
        out[i] = ((char *)time)[SIZE_REALTIME - 1 - i];
    }
#endif
}

//----------------------------------- schedule_time -----------------------------------------
schedule_time_t schedule_time_cast(char str[])
{
    char endian[SIZE_SCHEDULE_TIME];
#ifdef BIGENDIAN
    for (int i = 0; i < n; i++)
    {
        endian[i] = str[i];
    }
#else
    for (int i = 0; i < SIZE_SCHEDULE_TIME; i++)
    {
        endian[i] = str[SIZE_SCHEDULE_TIME - 1 - i];
    }
#endif
    return *(schedule_time_t *)endian;
}

void schedule_time_string(schedule_time_t *time, char out[])
{
#ifdef BIGENDIAN
    for (int i = 0; i < SIZE_SCHEDULE_TIME; i++)
    {
        out[i] = ((char *)time)[i];
    }
#else
    for (int i = 0; i < SIZE_SCHEDULE_TIME; i++)
    {
        out[i] = ((char *)time)[SIZE_SCHEDULE_TIME - 1 - i];
    }
#endif
}

bool schedule_time_check(schedule_time_t *time)
{
    return IS_TIME(time);
}

void set_schedule_time_error(schedule_time_t *time)
{
    SET_TIME_ERROR(time);
}

//----------------------------------- schedule_onoff -----------------------------------------
schedule_onoff_t schedule_onoff_cast(char str[])
{
    char endian[SIZE_SCHEDULE_ONOFF];
#ifdef BIGENDIAN
    for (int i = 0; i < SIZE_SCHEDULE_ONOFF; i++)
    {
        endian[i] = str[i];
    }
#else
    for (int i = 0; i < SIZE_SCHEDULE_ONOFF; i++)
    {
        endian[i] = str[SIZE_SCHEDULE_ONOFF - 1 - i];
    }
#endif
    return *(schedule_onoff_t *)endian;
}

void schedule_onoff_string(schedule_onoff_t *sch, char out[])
{
#ifdef BIGENDIAN
    for (int i = 0; i < SIZE_SCHEDULE_ONOFF; i++)
    {
        out[i] = ((char *)sch)[i];
    }
#else
    for (int i = 0; i < SIZE_SCHEDULE_ONOFF; i++)
    {
        out[i] = ((char *)sch)[SIZE_SCHEDULE_ONOFF - 1 - i];
    }
#endif
}

bool schedule_onoff_check(schedule_onoff_t *sch)
{
    return schedule_time_check(&(sch->time));
}

void schedule_onoff_array_cast(schedule_onoff_t schs[], int n, char str[])
{
    for (int i = 0; i < n; i++)
    {
        schs[i] = schedule_onoff_cast(&str[i * SIZE_SCHEDULE_ONOFF]);
    }
}

void schedule_onoff_array_string(schedule_onoff_t schs[], int n, char out[])
{
    for (int i = 0; i < n; i++)
    {
        schedule_onoff_string(&schs[i], &out[i * SIZE_SCHEDULE_ONOFF]);
    }
}

//----------------------------------- schedule_dimming -----------------------------------------
schedule_dimming_t schedule_dimming_cast(char str[])
{
    char endian[SIZE_SCHEDULE_DIMMING];
#ifdef BIGENDIAN
    for (int i = 0; i < SIZE_SCHEDULE_DIMMING; i++)
    {
        endian[i] = str[i];
    }
#else
    for (int i = 0; i < SIZE_SCHEDULE_DIMMING; i++)
    {
        endian[i] = str[SIZE_SCHEDULE_DIMMING - 1 - i];
    }
#endif
    return *(schedule_dimming_t *)endian;
}

void schedule_dimming_string(schedule_dimming_t *sch, char out[])
{
#ifdef BIGENDIAN
    for (int i = 0; i < SIZE_SCHEDULE_DIMMING; i++)
    {
        out[i] = ((char *)sch)[i];
    }
#else
    for (int i = 0; i < SIZE_SCHEDULE_DIMMING; i++)
    {
        out[i] = ((char *)sch)[SIZE_SCHEDULE_DIMMING - 1 - i];
    }
#endif
}

bool schedule_dimming_check(schedule_dimming_t *sch)
{
    return schedule_time_check(&(sch->time));
}

void schedule_dimming_array_cast(schedule_dimming_t schs[], int n, char str[])
{
    for (int i = 0; i < n; i++)
    {
        schs[i] = schedule_dimming_cast(&str[i * SIZE_SCHEDULE_DIMMING]);
    }
}

void schedule_dimming_array_string(schedule_dimming_t schs[], int n, char out[])
{
    for (int i = 0; i < n; i++)
    {
        schedule_dimming_string(&schs[i], &out[i * SIZE_SCHEDULE_DIMMING]);
    }
}

//----------------------------------- group -----------------------------------------
group_t group_cast(char str[])
{
    char endian[SIZE_GROUP];
#ifdef BIGENDIAN
    for (int i = 0; i < SIZE_GROUP; i++)
    {
        endian[i] = str[i];
    }
#else
    for (int i = 0; i < SIZE_GROUP; i++)
    {
        endian[i] = str[SIZE_GROUP - 1 - i];
    }
#endif
    return *(group_t *)endian;
}

void group_string(group_t *gr, char out[])
{
#ifdef BIGENDIAN
    for (int i = 0; i < SIZE_GROUP; i++)
    {
        out[i] = ((char *)gr)[i];
    }
#else
    for (int i = 0; i < SIZE_GROUP; i++)
    {
        out[i] = ((char *)gr)[SIZE_GROUP - 1 - i];
    }
#endif
}

bool group_check(group_t *gr)
{
    return IS_GROUP(gr);
}

void group_array_cast(group_t grs[], int n, char str[])
{
    for (int i = 0; i < n; i++)
    {
        grs[i] = group_cast(&str[i * SIZE_GROUP]);
    }
}

void group_array_string(group_t grs[], int n, char out[])
{
    for (int i = 0; i < n; i++)
    {
        group_string(&grs[i], &out[i * SIZE_GROUP]);
    }
}

//----------------- extended functions -----------------
bool combine_schedule_onoff_withgroup(schedule_onoff_t schs[], int n_schs, group_t grs[], int n_grs)
{
    bool is_changed = false;
    for (int s = 0; s < n_schs; s++)
    {
        bool is_exist = false;
        for (int g = 0; g < n_grs; g++)
        {
            if (schs[s].address == MY_ADDRESS || schs[s].address == grs[g].address)
            {
                is_exist = true;
                break;
            }
        }

        // dat schedule_time = error (cac schedule khong co su lien quan nao)
        if (is_exist == false)
        {
            is_changed = true;
            set_schedule_time_error(&schs[s].time);
        }
    }
    return is_changed;
}

bool combine_schedule_dimming_withgroup(schedule_dimming_t schs[], int n_schs, group_t grs[], int n_grs)
{
    bool is_changed = false;
    for (int s = 0; s < n_schs; s++)
    {
        bool is_exist = false;
        for (int g = 0; g < n_grs; g++)
        {
            if (schs[s].address == MY_ADDRESS || schs[s].address == grs[g].address)
            {
                is_exist = true;
                break;
            }
        }

        // dat schedule_time = error (cac schedule khong co su lien quan nao)
        if (is_exist == false)
        {
            is_changed = true;
            set_schedule_time_error(&schs[s].time);
        }
    }
    return is_changed;
}
