
#include "SensorReadingStack.h"

void s_Init(SR_Stack *s) {
    // TODO 
    // (void)s;
    memset(s->buf, 0, sizeof(s->buf));
    s->top = 0;
    s->cnt = 0;
}

bool s_isEmpty(const SR_Stack *s) { 
    // TODO return true if stack is empty
    // (void)s;
    return (s->cnt == 0);
}

bool s_isFull(const SR_Stack *s) {
    // TODO return true if stack is full
    // (void)s;
    return (s->cnt == STACK_SZ);
}

void s_Push(SR_Stack *s, SensorReading v) {
    // TODO: push an element onto the stack
    // (void)s;
    // (void)v;
    s->buf[s->top] = v;
    s->top = (s->top + 1) % STACK_SZ;
 
    if (s->cnt < STACK_SZ) {
        s->cnt++;
    }
}

bool s_Pop(SR_Stack *s, SensorReading *out) {
    // TODO: pop an element off the queue if not empty
    // (void)s;
    // (void)out;
    if (s_isEmpty(s)) {
        return false;
    }
 
    /* top points to the next free slot, so go back one */
    s->top = STACK_PREV(s->top);
    *out = s->buf[s->top];
    s->cnt--;
    return true;
}

void s_PrintAll(FILE *stream, const SR_Stack *undo) {
    if (s_isEmpty(undo)) {
        fprintf(stream, "(stack empty)");
    } else {
        int idx = STACK_PREV(undo->top);
        for (int i = 0; i < undo->cnt; ++i) {
            const SensorReading *s = &undo->buf[idx];
            sr_Print(stdout, "", s);
            idx = STACK_PREV(idx);
        }
    }
}

