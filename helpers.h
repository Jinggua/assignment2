
#ifndef _HELPERS_H_
#define _HELPERS_H_

#include "sensorReadingQueue.h"
#include "sensorReadingStack.h"

#include <stdio.h>

void Usage(const char *prog);
void PrintHelp(FILE *stream);

void GetHandler(SR_Queue *q);
void UndoHandler(SR_Queue *q, SR_Stack *undo);
void AvgHandler(SR_Queue *q, char *token);
void AddHandler(SR_Queue *q, SR_Stack *undo, char *token);

#endif // _HELPERS_H_
