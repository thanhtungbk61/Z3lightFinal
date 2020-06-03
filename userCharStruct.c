/*
 * userCharStruct.c
 *
 *  Created on: Dec 16, 2019
 *      Author: who_you_are
 */


//--------------------------------START---------------------------------------
#include "userCharStruct.h"

// get gia tri int64 tu char*, neu type = string --> return 0
// gia tri tra ve = int64, sau do ep ve kieu mong muon:
// vi du: int16_t a = (int16_t) getIntFromString(str, INT16)


int64_t getIntFromString(char* str, valueType_t type)
{
    int len = 0;
    char arrayInt[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    switch (type)
    {
        case INT8:
            len = 1;
            break;
        case INT16:
            len = 2;
            break;
        case INT32:
            len = 4;
            break;
        case INT64:
            len = 8;
            break;
        default:
            len = 0;
            break;
    }
    for(int i = 0; i < len; i++)
    {
        arrayInt[len - 1 - i] = str[i];
    }
    return *((int64_t*)arrayInt);
}

Sub convert2sub(char* raw) {
    Sub s;
    s.Address       = (int16_t) getIntFromString(raw, INT16);
    s.Type          = (int8_t) getIntFromString(raw + 2, INT8);
    s.Endpoint      = (int8_t) getIntFromString(raw + 3, INT8);
    s.ProfileID     = (int16_t) getIntFromString(raw + 4, INT16);
    s.ClusterID     = (int16_t) getIntFromString(raw + 6, INT16);
    s.AttributeID   = (int16_t) getIntFromString(raw + 8, INT16);
    s.ValueType     = (int8_t) getIntFromString(raw + 10, INT8);
    memcpy(s.StrValue, raw + 11, sizeof(s.StrValue));
    return s;
}

Sub convert2group(char* raw) {
    Sub s;
    s.Address       = (int16_t) getIntFromString(raw, INT16);
    s.Type          = (int8_t) getIntFromString(raw + 2, INT8);
    s.Endpoint      = (int8_t) getIntFromString(raw + 3, INT8);
    s.ProfileID     = 0;
    s.ClusterID     = 0;
    s.AttributeID   = 0;
    s.ValueType     = 0;
   // memcpy(s.StrValue, raw + 11, sizeof(s.StrValue));
    return s;
}

Schedule convert2schedule(char* raw) {
    Schedule s;

    s.Address       = (int16_t) getIntFromString(raw, INT16);
    s.Type          = (int8_t) getIntFromString(raw + 2, INT8);
    s.Endpoint      = (int8_t) getIntFromString(raw + 3, INT8);
    memcpy(s.Name, raw + 4, SIZE_NAME);
    s.DateHoMuSe    = (int32_t) getIntFromString(raw + SIZE_NAME + 4, INT32);
    s.ProfileID     = (int16_t) getIntFromString(raw + SIZE_NAME + 8, INT16);
    s.ClusterID     = (int16_t) getIntFromString(raw + SIZE_NAME + 10, INT16);
    s.AttributeID   = (int16_t) getIntFromString(raw + SIZE_NAME + 12, INT16);
    s.ValueType     = (int8_t) getIntFromString(raw + SIZE_NAME + 14, INT8);
    memcpy(s.StrValue, raw + SIZE_NAME + 15, sizeof(s.StrValue));
    return s;
}
