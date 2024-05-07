// shark.h
#ifndef SHARK_H
#define SHARK_H

#include "ocean.h"

// Constants for shark properties - can be modified
#define SHARK_BREED_AGE 10
#define SHARK_MAX_AGE 20
#define SHARK_STARVE_TIME 5



/** @struct Shark
 * @brief Represents a shark in the ocean.
 * @param age Age of the shark (int)
 * @param breedAge Age at which the shark can breed (int)
 * @param maxAge Maximum age of the shark (int)
 * @param starveTime Maximum time since last meal before the shark dies (int)
 * @param timeSinceLastMeal Time since last meal (int)
 * @param coordinates Coordinates of the shark (Coordinates)
 * 
*/
typedef struct {
    int age;
    int breedAge;
    int maxAge;
    int starveTime;
    int timeSinceLastMeal;
    Coordinates coordinates;
} Shark;



// Function prototypes
void move_shark(Shark* shark, Ocean* ocean);


Shark* create_shark(int age, int breedAge, int maxAge, int starveTime, int timeSinceLastMeal);

#define create_shark(age) create_shark(age, SHARK_BREED_AGE, SHARK_MAX_AGE, SHARK_STARVE_TIME, 0)

void delete_shark(Shark* shark);

void shark_eat(Shark* shark, Ocean* ocean, Coordinates* coordinates);

void shark_starve(Shark* shark, Ocean* ocean, Coordinates* coordinates);

void shark_breed(Shark* shark, Ocean* ocean, Coordinates* coordinates);



#endif