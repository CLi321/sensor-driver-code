#ifndef __DEF_CONFIG_H
#define __DEF_CONFIG_H

#include "stm32f10x.h"

typedef enum
{
    OFF = 0,
    ON = 1,
    REVERSE = 2
} ENUM_STATE;

typedef enum
{
    FALSE = 0,
    TRUE = 1
} ENUM_Judge;

typedef struct {
    uint8_t Usart1;
    uint8_t Usart2;
    uint8_t Usart3;
    uint8_t Rtc;
    uint8_t Tim2;
    uint8_t Tim3;
    uint8_t Tim4;
} STRUCT_NVICPriority;
extern STRUCT_NVICPriority NVICPriority_Structure;

typedef struct {
    ENUM_Judge Flag_200MS;
    ENUM_Judge Flag_1000MS;
} STRUCT_TIME;



#endif

