#include <iostream>
#include <stdlib.h>
#include <time.h>

/*GLOBALS*/
bool cupCakeOnPlate = true;

/*PROTOTYPES*/
void labyrinth();
int genRandomNumber(int upperBound, bool zeroBased);

int main()
{
    // seed once at the start of the program
    srand(time(NULL));

    return 0;
}

// Used to pick which thread to go next
int genRandomNumber(int upperBound, bool zeroBased)
{
    // would usually plus "upperbound + 1" to get 1 - upperbound
    // but this will be used to index and array so 0 - (upperbound - 1) is fine
    // TODO: fix comments, just add param to see which one we should do
    // TODO: rand is critical sections, watch out for this later
    return zeroBased ? rand() % upperBound : rand() % upperBound + 1;
}

/*
 * This method will be used as a way to think of the labyrinth
 * A Thread will enter and decide weather it eats to cupcake or not
 * Inside this method should have a critical sections, not allowing threads to alter
 * "cupCakeOnPlate" at the same time.
 * Whether or not the cupcake is eaten can be decided with rng
 *
 * If rng is 1 - eat the cupcake
 * If rng is 0 - leave the cupcake
 */
void labyrinth()
{
    int rand = 0;

    // will generate numbers between 0 - 1
    rand = genRandomNumber(2, true);

    // if cupcake on the plate
    if (cupCakeOnPlate && rand == 1)
    {
        cupCakeOnPlate == false;
    }
    else if (cupCakeOnPlate && rand == 0)
    {
        // TODO: same as leaving cupcake at value it enter as
        // TODO: no need to change (?)
        cupCakeOnPlate = true;
    }
}