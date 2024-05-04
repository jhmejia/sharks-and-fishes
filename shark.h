// shark.h
#ifndef SHARK_H
#define SHARK_H

/** @struct Shark
 * @brief Represents a shark in the ocean.
 * @param age Age of the shark (int)
 * @param breedAge Age at which the shark can breed (int)
 * @param maxAge Maximum age of the shark (int)
 * @param starveTime Maximum time since last meal before the shark dies (int)
 * @param timeSinceLastMeal Time since last meal (int)
 * 
*/
typedef struct {
    int age;
    int breedAge;
    int maxAge;
    int starveTime;
    int timeSinceLastMeal;
} Shark;

// Function prototypes
void move_shark(Shark* shark, Ocean* ocean);

#endif