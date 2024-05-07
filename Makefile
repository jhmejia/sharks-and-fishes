CC = gcc
CFLAGS = -Wall -Wextra -fopenmp

SRCS = main.c grid.c
OBJS = $(SRCS:.c=.o)
EXEC = simulation

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)