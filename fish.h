// fish.h
#ifndef FISH_H
#define FISH_H

#include "ocean.h"

/** @struct Fish
 * @brief Represents a fish in the ocean.
 * @param age Age of the fish (int)
 * @param breedAge Age at which the fish can breed (int)
 * @param maxAge Maximum age of the fish (int)
 * @param coordinates Coordinates of the fish (Coordinates)
 */
typedef struct {
    int age;
    int breedAge;
    int maxAge;
    Coordinates coordinates;
} Fish;

// Function prototypes
void move_fish(Fish* fish, Ocean* ocean);

Fish* create_fish(int age, int breedAge, int maxAge);

#define create_fish(age) create_fish(age, FISH_BREED_AGE, FISH_MAX_AGE)

void delete_fish(Fish* fish);

#endif


