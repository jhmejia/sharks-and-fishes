
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "ocean.h"
#include "shark.h"
#include "fish.h"


Coordinates move_shark(Shark* shark, Ocean* ocean) {
    // Get the current coordinates of the shark
    Coordinates current = {shark->x, shark->y, shark->z};
    // Get the possible moves
    Coordinates moves[6] = {
        {current.x + 1, current.y, current.z},
        {current.x - 1, current.y, current.z},
        {current.x, current.y + 1, current.z},
        {current.x, current.y - 1, current.z},
        {current.x, current.y, current.z + 1},
        {current.x, current.y, current.z - 1}
    };
    // Randomly shuffle the moves
    for (int i = 0; i < 6; i++) {
        int j = rand() % 6;
        Coordinates temp = moves[i];
        moves[i] = moves[j];
        moves[j] = temp;
    }
    // Move to the first possible move
    for (int i = 0; i < 6; i++) {
        Coordinates move = moves[i];
        if (move.x >= 0 && move.x < ocean->width && move.y >= 0 && move.y < ocean->height && move.z >= 0 && move.z < ocean->depth) {
            if (ocean->cells[move.x][move.y][move.z].type == 0) {
                // Move the shark
                ocean->cells[move.x][move.y][move.z].inhabitant = shark;
                ocean->cells[move.x][move.y][move.z].type = 2;
                ocean->cells[move.x][move.y][move.z].hasNewborn = 1;
                // Update the shark's coordinates
                shark->x = move.x;
                shark->y = move.y;
                shark->z = move.z;
                // Clear the current cell
                ocean->cells[current.x][current.y][current.z].inhabitant = NULL;
                ocean->cells[current.x][current.y][current.z].type = 0;
                ocean->cells[current.x][current.y][current.z].hasNewborn = 0;
                break;
            }
        }
    }
    return current;
}


/**
 * @brief One generation step for a shark. Moves the shark, eats if possible, starves if necessary, and breeds if possible.
 * 
 * @param shark Pointer to the shark
 * @param ocean Pointer to the ocean
 * @param coordinates Pointer to the coordinates of the shark
 * @return Shark The updated shark
*/
Shark shark_step(Shark* shark, Ocean* ocean, Coordinates* coordinates) {
    // Move the shark
    move_shark(shark, ocean);
    // Eat if possible
    shark_eat(shark, ocean, coordinates);
    // Starve if necessary
    shark_starve(shark, ocean, coordinates);
    // Breed if possible
    shark_breed(shark, ocean, coordinates);
    return *shark;
}