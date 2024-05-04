#ifndef OCEAN_H
#define OCEAN_H

/**
 * Defines the Ocean struct and function prototypes for creating, deleting, and updating an ocean.
*/


// Each cell in the ocean can be empty, contain a fish, or contain a shark
/** @struct Cell
 * @brief Represents a cell in the ocean that can contain either a Fish, Shark, or be empty.
 * @param inhabitant Pointer to either a Fish or Shark, NULL if empty (void*)
 * @param type 0 for empty, 1 for fish, 2 for shark (int)
 * @param hasNewborn Flag to indicate presence of a new born that hasn't moved (int)
*/
typedef struct {
    void* inhabitant;
    int type;   
    int hasNewborn;
} Cell;



/** @struct Ocean
 * @brief Represents a 3D ocean with cells that can contain either a Fish, Shark, or be empty.
 * @param cells 3D array of cells (Cell***)
 * @param width Width of the ocean (int)
 * @param height Height of the ocean (int)
 * @param depth Depth of the ocean (int)
*/
typedef struct {
    Cell*** cells;     // 3D array of cells
    int width;
    int height;
    int depth;
} Ocean;


// Function prototypes
Ocean* create_ocean(int width, int height, int depth);
void delete_ocean(Ocean* ocean);
void update_ocean(Ocean* ocean);

#endif
