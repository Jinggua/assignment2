#include "helpers.h"
#include "sensorReadingQueue.h"
#include "sensorReadingStack.h"

#include <stdlib.h>
#include <string.h>

int main(void) {
    SR_Queue q;
    SR_Stack undo;
    char *token;
    bool quit = false;

    q_Init(&q);
    s_Init(&undo);
    fprintf(stdout, "Sensor Buffer (FIFO + Undo Stack). Type 'h' for help.");

    char line[128];
    while (quit == false) {
        fprintf(stdout, "\n> ");
        if (!fgets(line, sizeof(line), stdin)) {
            break;
        }

        // Trim leading spaces
        token = line;
        while (*token == ' ' || *token == '\t') {
            ++token;
        }

        switch (*token) {
        case 'q': // quit
            quit = true;
            break;
        case '\n': // ignore
        case '\0': // ignore
            break;
        case 'h': // help
            PrintHelp(stdout);
            break;
        case 'p': // print queue
            if (strncmp(token, "pv", 2) == 0) {
                q_PrintAll(stdout, &q);
            } else if (strncmp(token, "pu", 2) == 0) {
                s_PrintAll(stdout, &undo);
            } else {
                fprintf(stdout, "Unknown command. Type 'h' for help.");
            }
            break;
        case 'g': // get
            GetHandler(&q);
            break;
        case 'u': // undo
            UndoHandler(&q, &undo);
            break;
        case 'a': // add or avg
            if (strncmp(token, "avg", 3) == 0) {
                // avg
                AvgHandler(&q, token);
            } else {
                // add
                AddHandler(&q, &undo, token);
            }
            break;
        default:
            fprintf(stdout, "Unknown command. Type 'h' for help.");
            break;
        }
    }

    fprintf(stdout, "Bye.\n");
    return 0;
}
