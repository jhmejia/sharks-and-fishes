#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <stdbool.h>
#include "grid.h"
#include <mpi.h>

int GRID_SIZE;
int SHARK_BREED_AGE;
int SHARK_STARVE_AGE;
int SHARK_MAX_AGE;
int FISH_BREED_AGE;
int FISH_MAX_AGE;
int NUM_GENERATIONS;
int NUM_FISH;
int NUM_SHARKS;


Cell grid[MAX_GRID_SIZE][MAX_GRID_SIZE][MAX_GRID_SIZE];
Cell newGrid[MAX_GRID_SIZE][MAX_GRID_SIZE][MAX_GRID_SIZE];

/** @brief Initializes the grid with randomly placed fish and sharks
 * 
 * The grid is initialized with randomly placed fish and sharks based on
 * the values of NUM_FISH and NUM_SHARKS. Error checking is performed to
 * ensure that the total number of fish and sharks does not exceed the
 * grid size cubed.
 * 
*/
void initializeGrid() {
    // Check if the total number of fish and sharks exceeds the grid size cubed
    if (NUM_FISH + NUM_SHARKS > GRID_SIZE * GRID_SIZE * GRID_SIZE) {
        printf("Error: Total number of fish and sharks exceeds the grid size cubed!\n");
        exit(1);
    }

    // Initialize the grid with empty cells
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            for (int k = 0; k < GRID_SIZE; k++) {
                grid[i][j][k].type = EMPTY;
                grid[i][j][k].age = 0;
                grid[i][j][k].hunger = 0;
            }
        }
    }

    // Randomly place fish in the grid
    int fishCount = 0;
    while (fishCount < NUM_FISH) {
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;
        int z = rand() % GRID_SIZE;

        if (grid[x][y][z].type == EMPTY) {
            grid[x][y][z].type = FISH;
            fishCount++;
        }
    }

    // Randomly place sharks in the grid
    int sharkCount = 0;
    while (sharkCount < NUM_SHARKS) {
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;
        int z = rand() % GRID_SIZE;

        if (grid[x][y][z].type == EMPTY) {
            grid[x][y][z].type = SHARK;
            sharkCount++;
        }
    }
}



void updateGrid(int rank, int size) {

    int local_size = GRID_SIZE / size;
    int start = rank * local_size;
    int end = (rank == size - 1) ? GRID_SIZE : start + local_size;


    // Update the grid based on the rules of the cellular automata

    for (int i = start; i < end; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            for (int k = 0; k < GRID_SIZE; k++) {
                // Sharks starve or die
                if (grid[i][j][k].type == SHARK) {
                    if (grid[i][j][k].hunger >= SHARK_STARVE_AGE || grid[i][j][k].age >= SHARK_MAX_AGE) {
                        newGrid[i][j][k].type = 0;
                        newGrid[i][j][k].age = 0;
                        newGrid[i][j][k].hunger = 0;
                    } else {
                        newGrid[i][j][k].type = SHARK;
                        newGrid[i][j][k].age = grid[i][j][k].age;
                        newGrid[i][j][k].hunger = grid[i][j][k].hunger;
                    }
                    continue;
                }

                // Fish die
                if (grid[i][j][k].type == 1 && grid[i][j][k].age >= FISH_MAX_AGE) {
                    newGrid[i][j][k].type = 0;
                    newGrid[i][j][k].age = 0;
                    continue;
                }

                // Sharks determine movement
                if (grid[i][j][k].type == SHARK) {
                    bool moved = false;
                    for (int di = -1; di <= 1; di++) {
                        for (int dj = -1; dj <= 1; dj++) {
                            for (int dk = -1; dk <= 1; dk++) {
                                int ni = (i + di + GRID_SIZE) % GRID_SIZE;
                                int nj = (j + dj + GRID_SIZE) % GRID_SIZE;
                                int nk = (k + dk + GRID_SIZE) % GRID_SIZE;
                                if (grid[ni][nj][nk].type == 1) {
                                    newGrid[ni][nj][nk].type = SHARK;
                                    newGrid[ni][nj][nk].age = grid[i][j][k].age + 1;
                                    newGrid[ni][nj][nk].hunger = 0;
                                    moved = true;
                                    break;
                                }
                            }
                            if (moved) break;
                        }
                        if (moved) break;
                    }
                    if (!moved) {
                        for (int di = -1; di <= 1; di++) {
                            for (int dj = -1; dj <= 1; dj++) {
                                for (int dk = -1; dk <= 1; dk++) {
                                    int ni = (i + di + GRID_SIZE) % GRID_SIZE;
                                    int nj = (j + dj + GRID_SIZE) % GRID_SIZE;
                                    int nk = (k + dk + GRID_SIZE) % GRID_SIZE;
                                    if (grid[ni][nj][nk].type == 0) {
                                        newGrid[ni][nj][nk].type = 2;
                                        newGrid[ni][nj][nk].age = grid[i][j][k].age + 1;
                                        newGrid[ni][nj][nk].hunger = grid[i][j][k].hunger + 1;
                                        moved = true;
                                        break;
                                    }
                                }
                                if (moved) break;
                            }
                            if (moved) break;
                        }
                    }
                    if (!moved) {
                        newGrid[i][j][k].type = 2;
                        newGrid[i][j][k].age = grid[i][j][k].age + 1;
                        newGrid[i][j][k].hunger = grid[i][j][k].hunger + 1;
                    }
                }

                // Fish determine movement
                if (grid[i][j][k].type == 1) {
                    bool moved = false;
                    for (int di = -1; di <= 1; di++) {
                        for (int dj = -1; dj <= 1; dj++) {
                            for (int dk = -1; dk <= 1; dk++) {
                                int ni = (i + di + GRID_SIZE) % GRID_SIZE;
                                int nj = (j + dj + GRID_SIZE) % GRID_SIZE;
                                int nk = (k + dk + GRID_SIZE) % GRID_SIZE;
                                if (grid[ni][nj][nk].type == 0) {
                                    newGrid[ni][nj][nk].type = 1;
                                    newGrid[ni][nj][nk].age = grid[i][j][k].age + 1;
                                    moved = true;
                                    break;
                                }
                            }
                            if (moved) break;
                        }
                        if (moved) break;
                    }
                    if (!moved) {
                        newGrid[i][j][k].type = 1;
                        newGrid[i][j][k].age = grid[i][j][k].age + 1;
                    }
                }

                // Fish breeding
                if (grid[i][j][k].type == 1 && grid[i][j][k].age >= FISH_BREED_AGE && newGrid[i][j][k].type == 0) {
                    newGrid[i][j][k].type = 1;
                    newGrid[i][j][k].age = 0;
                }

                // Shark breeding
                if (grid[i][j][k].type == 2 && grid[i][j][k].age >= SHARK_BREED_AGE && newGrid[i][j][k].type == 0) {
                    newGrid[i][j][k].type = 2;
                    newGrid[i][j][k].age = 0;
                    newGrid[i][j][k].hunger = 0;
                }
            }
        }
    }

    // Copy newGrid to grid
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            for (int k = 0; k < GRID_SIZE; k++) {
                grid[i][j][k] = newGrid[i][j][k];
            }
        }
    }

    MPI_Allgather(MPI_IN_PLACE, local_size * GRID_SIZE * GRID_SIZE, MPI_INT, grid, local_size * GRID_SIZE * GRID_SIZE, MPI_INT, MPI_COMM_WORLD);
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
    char filename[100];
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

    char line[100]; // Buffer to hold each line of the file

    // Read each line and extract the first integer
    if (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%d", &GRID_SIZE);
    }
    if (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%d", &SHARK_BREED_AGE);
    }
    if (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%d", &SHARK_STARVE_AGE);
    }
    if (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%d", &SHARK_MAX_AGE);
    }
    if (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%d", &FISH_BREED_AGE);
    }
    if (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%d", &FISH_MAX_AGE);
    }
    if (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%d", &NUM_GENERATIONS);
    }
    if (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%d", &NUM_FISH);
    }
    if (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%d", &NUM_SHARKS);
    }


    printf("Grid size: %d\n", GRID_SIZE);
    printf("Shark breed age: %d\n", SHARK_BREED_AGE);
    printf("Shark starve age: %d\n", SHARK_STARVE_AGE);
    printf("Shark max age: %d\n", SHARK_MAX_AGE);
    printf("Fish breed age: %d\n", FISH_BREED_AGE);
    printf("Fish max age: %d\n", FISH_MAX_AGE);
    printf("Number of generations: %d\n", NUM_GENERATIONS);

    printf("Number of fish: %d\n", NUM_FISH);
    printf("Number of sharks: %d\n", NUM_SHARKS);

    fclose(file);
}