
#ifndef _SAMPLEQUEUE_H_
#define _SAMPLEQUEUE_H_

#include "sensorReading.h"

#include <stdbool.h>

#define QUEUE_SZ 16

#define QUEUE_PREV(cur) ((cur - 1 + QUEUE_SZ) % QUEUE_SZ)
#define QUEUE_NEXT(cur) ((cur + 1) % QUEUE_SZ)

/* ---------- FIFO Queue (circular) ---------- */
typedef struct SensorReadingQueue {
    SensorReading buf[QUEUE_SZ];
    int head; // index of oldest element
    int tail; // index one past the newest element
    int cnt;  // number of elements
} SR_Queue;

void q_Init(SR_Queue *q);

bool q_isEmpty(const SR_Queue *q);
bool q_isFull(const SR_Queue *q);
int q_Count(const SR_Queue *q);

void q_Enqueue(SR_Queue *q, SensorReading s);
bool q_Dequeue(SR_Queue *q, SensorReading *out);
bool q_PopNewestIfMatch(SR_Queue *q, SensorReading match);
float q_AverageRecent(const SR_Queue *q, int N);

void q_PrintAll(FILE *stream, SR_Queue *q);

#endif // _SAMPLEQUEUE_H_
