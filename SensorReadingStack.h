
#ifndef _SENSOR_READING_STACK_H_
#define _SENSOR_READING_STACK_H_

#include "SensorReading.h"

#include <stdbool.h>

#define STACK_SZ 8

#define STACK_PREV(cur) ((cur - 1 + STACK_SZ) % STACK_SZ)

typedef struct SensorReadingStack {
    SensorReading buf[STACK_SZ];
    int top; // next free slot (size)
    int cnt; // number of elements
} SR_Stack;

void s_Init(SR_Stack *s);
bool s_isEmpty(const SR_Stack *s);
bool s_isFull(const SR_Stack *s);

void s_Push(SR_Stack *s, SensorReading v);
bool s_Pop(SR_Stack *s, SensorReading *out);

void s_PrintAll(FILE *stream, const SR_Stack *u);

#endif // _SENSOR_READING_STACK_H_
