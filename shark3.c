#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>



#define GRID_SIZE 10
#define MAX_THREADS 4
#define SHARK_BREED_AGE 10
#define SHARK_STARVE_AGE 3
#define SHARK_MAX_AGE 15
#define FISH_BREED_AGE 5
#define FISH_MAX_AGE 10

typedef struct {
    int type;  // 0: empty, 1: fish, 2: shark
    int age;
    int hunger;
} Cell;

Cell grid[GRID_SIZE][GRID_SIZE][GRID_SIZE];
Cell newGrid[GRID_SIZE][GRID_SIZE][GRID_SIZE];

void initializeGrid() {
    // Initialize the grid with random fish and sharks
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            for (int k = 0; k < GRID_SIZE; k++) {
                int type = rand() % 3;
                grid[i][j][k].type = type;
                grid[i][j][k].age = 0;
                grid[i][j][k].hunger = 0;
            }
        }
    }
}

void updateGrid() {
    // Update the grid based on the rules of the cellular automata
    #pragma omp parallel for num_threads(MAX_THREADS) collapse(3)
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            for (int k = 0; k < GRID_SIZE; k++) {
                // Sharks starve or die
                if (grid[i][j][k].type == 2) {
                    if (grid[i][j][k].hunger >= SHARK_STARVE_AGE || grid[i][j][k].age >= SHARK_MAX_AGE) {
                        newGrid[i][j][k].type = 0;
                        newGrid[i][j][k].age = 0;
                        newGrid[i][j][k].hunger = 0;
                        continue;
                    }
                }

                // Fish die
                if (grid[i][j][k].type == 1 && grid[i][j][k].age >= FISH_MAX_AGE) {
                    newGrid[i][j][k].type = 0;
                    newGrid[i][j][k].age = 0;
                    continue;
                }

                // Sharks determine movement
                if (grid[i][j][k].type == 2) {
                    bool moved = false;
                    for (int di = -1; di <= 1; di++) {
                        for (int dj = -1; dj <= 1; dj++) {
                            for (int dk = -1; dk <= 1; dk++) {
                                int ni = (i + di + GRID_SIZE) % GRID_SIZE;
                                int nj = (j + dj + GRID_SIZE) % GRID_SIZE;
                                int nk = (k + dk + GRID_SIZE) % GRID_SIZE;
                                if (grid[ni][nj][nk].type == 1) {
                                    newGrid[ni][nj][nk].type = 2;
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




int main() {
    initializeGrid();

    int generations = 10;
    for (int i = 0; i < generations; i++) {
        printf("Generation %d:\n", i);
        printGrid();
        writeGridToFile(i);
        updateGrid();
    }

    return 0;
}