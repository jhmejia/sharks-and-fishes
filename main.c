//Imports
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "ocean.h"


int main() {
    // Create an ocean with dimensions 5x5x5
    Ocean* ocean = create_ocean(5, 5, 5);
    // Delete the ocean
    delete_ocean(ocean);
    return 0;
}

