
/**
 *  @brief      OpenMP and MPI implementation of the a 
 *
 *  @author     JHMejia
 *  @version    1.0
 *  @date       05/05/2024
 *
 */

//Imports
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "ocean.h"


#define EMPTY '0'
#define FISH 'F'
#define SHARK 'S'

int main() {
    // Create an ocean with dimensions 5x5x5
    Ocean* ocean = create_ocean(5, 5, 5);

    // print ocean dimensions
    printf("Ocean dimensions: %dx%dx%d\n", ocean->width, ocean->height, ocean->depth);
    // Delete the ocean
    delete_ocean(ocean);

    return 0;
}

