#include <stdio.h>
#include "grid.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int opt;
    int verbose = 0;
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {

        if (argc < 2) {
            printf("Usage: %s <config_file> [-v|--verbose]\n", argv[0]);
            return 1;
        }
        
        while ((opt = getopt(argc, argv, "v")) != -1) {
            switch (opt) {
                case 'v':
                    verbose = 1;
                    break;
                default:
                    printf("Usage: %s <config_file> [-v]\n", argv[0]);
                    return 1;
            }
        }

        //Check if there are enough arguments for config file
        if (optind >= argc) {
            printf("Usage: %s <config_file> [-v]\n", argv[0]);
            return 1;
        }

        if (verbose)
            printf("Verbose mode enabled\n");


        printf("Reading config file %s\n", argv[optind]);
        readConfigFile(argv[optind]);
    }

    MPI_Bcast(&GRID_SIZE, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&SHARK_BREED_AGE, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&SHARK_STARVE_AGE, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&SHARK_MAX_AGE, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&FISH_BREED_AGE, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&FISH_MAX_AGE, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&NUM_GENERATIONS, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&NUM_FISH, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&NUM_SHARKS, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        initializeGrid();
    }

    clock_t start, end;
    double duration;

    start = clock(); 

    for (int i = 0; i < NUM_GENERATIONS; i++) {
        if (rank == 0 && verbose) {
            printf("Generation %d:\n", i);
            printGrid();
            writeGridToFile(i);
        }
        updateGrid(rank, size);
        MPI_Barrier(MPI_COMM_WORLD);
    }
    
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", duration);

    MPI_Finalize();

    return 0;
}