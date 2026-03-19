#include "sensorReadingQueue.h"
#include <string.h>
/* ---------- FIFO Queue (circular) ---------- */
void q_Init(SR_Queue *q) {
    // TODO
    memset(q->buf, 0, sizeof(q->buf));
    q->head = 0;
    q->tail = 0;
    q->cnt  = 0;
    // (void)q;
}

bool q_isEmpty(const SR_Queue *q) { 
    // TODO return true if queue is empty
    // (void)q;
    // if(q->cnt == 0) {
    //     return true
    // } else {
    //     return false;
    // }
    return (q->cnt == 0);
}

bool q_isFull(const SR_Queue *q) { 
    // TODO return true if queue is full
    // (void)q;
    return (q->cnt == QUEUE_SZ);;
}

int q_Count(const SR_Queue *q) { 
    // TODO return the number of elements in the queue
    // (void)q;
    int num = q->cnt;
    return num;
}

void q_Enqueue(SR_Queue *q, SensorReading s) {
    // TODO add an element to the tail of the queue
    q->buf[q->tail] = s;
    q->tail = QUEUE_NEXT(q->tail);
 
    if (q->cnt == QUEUE_SZ) {
        /* Queue was full: oldest entry overwritten, advance head */
        q->head = QUEUE_NEXT(q->head);
    } else {
        q->cnt++;
    }
}

bool q_Dequeue(SR_Queue *q, SensorReading *out) {
    // TODO remove an element from the head of the queue
    if (q_isEmpty(q)) {
        return false;
    }
 
    *out = q->buf[q->head];
    q->head = QUEUE_NEXT(q->head);
    q->cnt--;
    return true;
}

// Remove from the "newest" (tail) side once (used by undo).
bool q_PopNewestIfMatch(SR_Queue *q, SensorReading match) {
    if (q_isEmpty(q)) {
        return false;
    }
 
    /* The newest element is one position before tail */
    int newest = QUEUE_PREV(q->tail);
 
    if (q->buf[newest].tsms == match.tsms &&
        q->buf[newest].value == match.value) {
        /* Match found: move tail back and decrease count */
        q->tail = newest;
        q->cnt--;
        return true;
    }
 
    return false;
}

/* ---------- Utility: compute average of most recent N in queue ---------- */
float q_AverageRecent(const SR_Queue *q, int N) {
    // TODO
    // if N == 0, avg = 0
    // if N > cnt, N = cnt
    int use = N;
 
    /* Clamp N to the actual number of elements */
    if (use > q->cnt) {
        use = q->cnt;
    }
 
    float sum = 0.0f;
 
    /* Start from the newest and walk backwards */
    int idx = QUEUE_PREV(q->tail);
 
    for (int i = 0; i < use; i++) {
        sum += q->buf[idx].value;
        idx = QUEUE_PREV(idx);
    }
 
    return sum / (float)use;
}

void q_PrintAll(FILE *stream, SR_Queue *q) {
    if (q_isEmpty(q)) {
        fprintf(stream, "(queue empty)");
    } else {
        int idx = q->head;
        for (int i = 0; i < q->cnt; ++i) {
            SensorReading *s = &q->buf[idx];
            sr_Print(stdout, "", s);
            idx = (idx + 1) % QUEUE_SZ;
        }
    }
}

