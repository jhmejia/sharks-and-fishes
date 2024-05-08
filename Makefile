CC = gcc
CFLAGS = -Wall -Wextra -fopenmp
MPICC = mpicc
MPICFLAGS = -Wall -Wextra

SRCS = main.c grid.c
MPI_SRCS = mpi_main.c mpi_grid.c
OBJS = $(SRCS:.c=.o)
EXEC = simulation
MPI_EXEC = mpi_simulation

.PHONY: all clean mpi

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

mpi: $(MPI_SRCS)
	# module load openmpi/gnu
	$(MPICC) $(MPICFLAGS) $(MPI_SRCS) -o $(MPI_EXEC)
	echo "#!/bin/bash" > run_mpi.sh
	echo "mpiexec -n 4 ./$(MPI_EXEC)" >> run_mpi.sh
	chmod +x run_mpi.sh

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC) $(MPI_EXEC) run_mpi.sh