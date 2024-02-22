#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <vector>
#include <mutex>

#define NUM_GUEST 20

/*GLOBALS*/
std::mutex mutex;
bool cupCakeOnPlate = true;
int numTimesReplaced = 0;
std::vector<bool> threadsThatHaveEaten(NUM_GUEST, false);
int threadAllowedInLabyrinth = -1;

/*PROTOTYPES*/
void labyrinth(int threadIndex);
int genRandomNumber(int lowerBound, int upperBound);
void checkCupcakeAndUpdate();
int validation();

int main()
{

    std::vector<std::jthread> jthreads;
    // seed once at the start of the program
    srand(time(NULL));

    jthreads.push_back(std::jthread(checkCupcakeAndUpdate));

    for (int i = 1; i < NUM_GUEST; i++)
    {

        jthreads.push_back(std::jthread(labyrinth, i));
    }

    // keep guessing random numbers until everyone has been through the maze
    // the main thread will be running this over and over
    // since this is also using the main thread, this has to go below the rest of the code
    // so the program does not get stuck here before making the other threads
    while (numTimesReplaced < NUM_GUEST)
    {
        threadAllowedInLabyrinth = genRandomNumber(0, NUM_GUEST);
    }

    return validation();
}

// Used to pick which thread to go next
int genRandomNumber(int lowerBound, int upperBound)
{
    // Generate a random number between lowerBound and upperBound (inclusive)
    return rand() % (upperBound - lowerBound + 1) + lowerBound;
}

void labyrinth(int threadIndex)
{
    while (numTimesReplaced < NUM_GUEST)
    {
        mutex.lock();
        if (threadIndex == threadAllowedInLabyrinth && cupCakeOnPlate && !threadsThatHaveEaten.at(threadIndex))
        {
            cupCakeOnPlate = false;                      /*eat cupcake*/
            threadsThatHaveEaten.at(threadIndex) = true; /*set the thread to have eaten the cupcake*/
            std::cout << "thread: " << threadIndex << " has eaten " << std::endl;
        }
        mutex.unlock();
    }
}

// this should only be called by 1 thread
void checkCupcakeAndUpdate()
{
    while (numTimesReplaced < NUM_GUEST)
    {
        mutex.lock();

        // this is so the counter thread has eaten the cupcake at least once as well
        if (cupCakeOnPlate && !threadsThatHaveEaten.at(0))
        {

            // counter thread does not really have to eat the cupcake
            // this is more so that we know counter thread has seen the cupcake
            // so we can leave the cupcake, but increase the counter so the rest of the
            // programs checks still work (i.e numTimesReplaced < NUM_GUEST)
            numTimesReplaced += 1; /*increase counter*/
            cupCakeOnPlate = true;
            threadsThatHaveEaten.at(0) = true;
            std::cout << "thread: " << 0 << " has ate " << std::endl;
        }

        // if its this threads turn to be allowed in the labyrinth
        if (threadAllowedInLabyrinth == 0)
        {
            // if the cupcake is not on the place replace it, and add to counter
            if (!cupCakeOnPlate)
            {
                numTimesReplaced += 1;
                cupCakeOnPlate = true;
            }
        }

        mutex.unlock();
    }
}

int validation()
{

    for (auto ans : threadsThatHaveEaten)
    {
        if (ans == false)
        {
            std::cout << "Every thread has not visited the labyrinth at least once" << std::endl;
            return -1;
        }
    }

    std::cout << "Every thread has visited the labyrinth at least once" << std::endl;
    return 0;
}