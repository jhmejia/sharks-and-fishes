#include <stdio.h>
#include "grid.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <config_file> <grid_file>\n", argv[0]);
        return 1;
    }

    readConfigFile(argv[1]);
    initializeGrid(argv[2]);

    int generations = 10;
    for (int i = 0; i < generations; i++) {
        printf("Generation %d:\n", i);
        printGrid();
        writeGridToFile(i);
        updateGrid();
    }

    return 0;
}