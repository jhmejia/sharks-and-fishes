CC=gcc
CFLAGS=-fopenmp
EXECUTABLE=main

all: $(EXECUTABLE)

$(EXECUTABLE): main.o ocean.o fish.o shark.o
	$(CC) -o $@ $^ $(CFLAGS)

main.o: main.c
	$(CC) -c -o $@ $< $(CFLAGS)

ocean.o: ocean.c ocean.h
	$(CC) -c -o $@ $< $(CFLAGS)

fish.o: fish.c fish.h
	$(CC) -c -o $@ $< $(CFLAGS)

shark.o: shark.c shark.h
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f *.o $(EXECUTABLE)

.PHONY: all clean
