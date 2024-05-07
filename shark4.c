#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>

#define MAX_GRID_SIZE 100
#define MAX_THREADS 4

typedef struct {
    int type;  // 0: empty, 1: fish, 2: shark
    int age;
    int hunger;
} Cell;

int GRID_SIZE;
int SHARK_BREED_AGE;
int SHARK_STARVE_AGE;
int SHARK_MAX_AGE;
int FISH_BREED_AGE;
int FISH_MAX_AGE;

Cell grid[MAX_GRID_SIZE][MAX_GRID_SIZE][MAX_GRID_SIZE];
Cell newGrid[MAX_GRID_SIZE][MAX_GRID_SIZE][MAX_GRID_SIZE];

void initializeGrid(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    fscanf(file, "%d", &GRID_SIZE);
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            for (int k = 0; k < GRID_SIZE; k++) {
                fscanf(file, "%d", &grid[i][j][k].type);
                grid[i][j][k].age = 0;
                grid[i][j][k].hunger = 0;
            }
        }
    }

    fclose(file);
}

void updateGrid() {
    // Update the grid based on the rules of the cellular automata
    #pragma omp parallel for num_threads(MAX_THREADS) collapse(3)
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            for (int k = 0; k < GRID_SIZE; k++) {
                // ... (rest of the code remains the same)
            }
        }
    }

    // Copy newGrid to grid
    #pragma omp parallel for num_threads(MAX_THREADS) collapse(3)
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            for (int k = 0; k < GRID_SIZE; k++) {
                grid[i][j][k] = newGrid[i][j][k];
            }
        }
    }
}

void printGrid() {
    // Print the current state of the grid
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            for (int k = 0; k < GRID_SIZE; k++) {
                printf("%d ", grid[i][j][k].type);
            }
            printf("\n");
        }
        printf("\n");
    }
}

void writeGridToFile(int generation) {
    char filename[20];
    sprintf(filename, "output/generation%d.txt", generation);
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            for (int k = 0; k < GRID_SIZE; k++) {
                fprintf(file, "%d ", grid[i][j][k].type);
            }
            fprintf(file, "\n");
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void readConfigFile(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening config file!\n");
        exit(1);
    }

    fscanf(file, "%d", &SHARK_BREED_AGE);
    fscanf(file, "%d", &SHARK_STARVE_AGE);
    fscanf(file, "%d", &SHARK_MAX_AGE);
    fscanf(file, "%d", &FISH_BREED_AGE);
    fscanf(file, "%d", &FISH_MAX_AGE);

    fclose(file);
}

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