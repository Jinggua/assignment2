
#ifndef _SENSOR_READING_H_
#define _SENSOR_READING_H_

#include <stdio.h>

typedef struct {
    unsigned long tsms; // millisecond timestamp
    float value;        // sensor value
} SensorReading;

void sr_Print(FILE *stream, const char *prefix, const SensorReading *s);

#endif // _SENSOR_READING_H_
