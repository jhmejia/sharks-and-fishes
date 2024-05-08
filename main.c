#include <stdio.h>
#include "grid.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int opt;
    int verbose = 0;

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


    initializeGrid();



    int generations = NUM_GENERATIONS;
    clock_t start, end;
    double duration;

    start = clock(); 

    for (int i = 0; i < generations; i++) {
        if (verbose)
        {
            printf("Generation %d:\n", i);
            printGrid();
            writeGridToFile(i);
        }
        updateGrid();
    }
    
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", duration);



    return 0;
}