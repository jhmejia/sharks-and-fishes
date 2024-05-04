#include "ocean.h"
#include <stdlib.h>
#include <omp.h>

Ocean* create_ocean(int width, int height, int depth) {
    Ocean* o = malloc(sizeof(Ocean));
    o->width = width;
    o->height = height;
    o->depth = depth;
    o->cells = malloc(width * sizeof(Cell**));

    #pragma omp parallel for
    for (int i = 0; i < width; i++) {
        o->cells[i] = malloc(height * sizeof(Cell*));
        for (int j = 0; j < height; j++) {
            o->cells[i][j] = malloc(depth * sizeof(Cell));
            for (int k = 0; k < depth; k++) {
                o->cells[i][j][k].inhabitant = NULL;
                o->cells[i][j][k].type = 0;
                o->cells[i][j][k].hasNewborn = 0;
            }
        }
    }
    return o;
}

/**
 * @brief Deletes the ocean and all its cells.
 * 
 * @param ocean Pointer to the ocean to be deleted.
 * @note This function does not free the Fish or Shark structs contained in the cells.
*/
void delete_ocean(Ocean* ocean) {

    #pragma omp parallel for
    for (int i = 0; i < ocean->width; i++) {
        for (int j = 0; j < ocean->height; j++) {
            free(ocean->cells[i][j]);
        }
        free(ocean->cells[i]);
    }
    free(ocean->cells);
    free(ocean);
}

void update_ocean(Ocean* ocean) {
    // Placeholder for update logic to be implemented
}


