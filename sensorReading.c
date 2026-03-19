

#include "sensorReading.h"

void sr_Print(FILE *stream, const char *prefix, const SensorReading *s) {
    fprintf(stream, "%s ts=%lu ms, value=%.3f\n", prefix, s->tsms, s->value);
}
