
CC=gcc
OUTPUT=queues.bin
CFLAGS=-std=c11 -Wall -Wextra -Wpedantic 

CFILES=\
main.c\
helpers.c\
sensorReadingStack.c\
sensorReadingQueue.c\
sensorReading.c

HFILES=\
helpers.h\
sensorReading.h\
sensorReadingQueue.h\
sensorReadingStack.h

all:
	$(CC) $(CFLAGS) $(CFILES) -o $(OUTPUT)

format: $(CFILES) $(HFILES)
	clang-format -i $(CFILES) $(HFILES)

clean:
	rm $(OUTPUT)
