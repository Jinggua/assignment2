#include "helpers.h"

#define TIMESTEP (100) // ms

static unsigned long nextts = 0; // ms

void PrintHelp(FILE *stream) {
    fprintf(stream, "  Commands:\n");
    fprintf(stream, "    a <value>  - add sample (value: float)\n");
    fprintf(stream, "    g          - get (dequeue) oldest sample\n");
    fprintf(stream, "    u          - undo last add\n");
    fprintf(stream, "    avg <N>    - average of most recent N samples\n");
    fprintf(stream, "    pv         - print values (oldest -> newest)\n");
    fprintf(stream, "    pu         - print undo stack (newest -> oldest)\n");
    fprintf(stream, "    h          - help\n");
    fprintf(stream, "    q          - quit\n");
}

/******************************************************************************/
/*                                                                            */
/*                                 HANDLERS                                   */
/*                                                                            */
/******************************************************************************/
void GetHandler(SR_Queue *q) {
    SensorReading out;
    if (q_Dequeue(q, &out)) {
        sr_Print(stdout, "DEQUEUE:", &out);
    } else {
        fprintf(stdout, "Queue empty\n");
    }
}

void UndoHandler(SR_Queue *q, SR_Stack *undo) {
    SensorReading last;
    if (!s_Pop(undo, &last)) {
        fprintf(stdout, "Nothing to undo\n");
    } else {
        nextts -= TIMESTEP;
        if (q_PopNewestIfMatch(q, last)) {
            sr_Print(stdout, "UNDO removed:", &last);
        } else {
            fprintf(stdout, "Undo stack popped, but matching newest sample not "
                            "found in "
                            "queue\n");
        }
    }
}

void AvgHandler(SR_Queue *q, char *token) {
    int n;
    if (sscanf(token, "avg %d", &n) == 1 && n >= 1) {
        if (q_isEmpty(q)) {
            fprintf(stdout, "Queue empty\n");
        } else {
            float avg = q_AverageRecent(q, n);
            printf("Average of most recent %d = %.3f\n",
                   (n > q->cnt ? q->cnt : n), avg);
        }
    } else {
        fprintf(stdout, "Usage: avg <N>   (N >= 1)\n");
    }
}

void AddHandler(SR_Queue *q, SR_Stack *undo, char *token) {
    // Expect: a <value>
    float v;
    if (sscanf(token, "a %f", &v) == 1) {
        SensorReading s = {.tsms = nextts, .value = v};
        q_Enqueue(q, s);
        s_Push(undo, s);
        sr_Print(stdout, "ENQUEUE:", &s);
        nextts += TIMESTEP; // simulate 100 ms between samples
    } else {
        fprintf(stdout, "Usage: a <value>\n");
    }
}
