#ifndef GRID_H
#define GRID_H

#define MAX_GRID_SIZE 100
#define MAX_THREADS 4

typedef struct {
    int type;  // 0: empty, 1: fish, 2: shark
    int age;
    int hunger;
} Cell;

extern int GRID_SIZE;
extern int SHARK_BREED_AGE;
extern int SHARK_STARVE_AGE;
extern int SHARK_MAX_AGE;
extern int FISH_BREED_AGE;
extern int FISH_MAX_AGE;

extern Cell grid[MAX_GRID_SIZE][MAX_GRID_SIZE][MAX_GRID_SIZE];
extern Cell newGrid[MAX_GRID_SIZE][MAX_GRID_SIZE][MAX_GRID_SIZE];

void initializeGrid(const char* filename);
void updateGrid();
void printGrid();
void writeGridToFile(int generation);
void readConfigFile(const char* filename);

#endif