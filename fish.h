// fish.h
#ifndef FISH_H
#define FISH_H

#include "ocean.h"

/** @struct Fish
 * @brief Represents a fish in the ocean.
 * @param age Age of the fish (int)
 * @param breedAge Age at which the fish can breed (int)
 * @param maxAge Maximum age of the fish (int)
 */
typedef struct {
    int age;
    int breedAge;
    int maxAge;
} Fish;

// Function prototypes
void move_fish(Fish* fish, Ocean* ocean);

#endif


