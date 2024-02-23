#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <vector>
#include <mutex>

#define NUM_GUEST 1000

enum RoomStatus
{
    AVAILABLE,
    BUSY
};

/*GLOBALS*/
std::vector<int> ids; /*list of thread ids that have seen the vase*/
std::mutex mutex;
RoomStatus roomStatus = AVAILABLE;
int randomGuestId = -1;

/*PROTOTYPES*/
void viewVase(int threadID);
int genRandomNumber(int lowerBound, int upperBound);

int main()
{
    std::vector<std::jthread> jthreads;

    for (int i = 0; i < NUM_GUEST; i++)
    {
        jthreads.push_back(std::jthread(viewVase, i));
    }

    // allow random guess to enter the room
    // not necessary, just does not make since if
    // the guess are lining up and not using the available
    // we can say if they are picked, then that felt the need to go
    // visit the vase, and then they check if available
    while (ids.size() < NUM_GUEST)
    {
        randomGuestId = genRandomNumber(0, NUM_GUEST);
    }

    return 0;
}

void viewVase(int threadID)
{

    // check if threadID is in visitedVase
    bool currentThreadHasVisited = false;

    // we can stop the program after each guess has
    // viewed the vase at least once
    while (ids.size() < NUM_GUEST)
    {
        mutex.lock();

        currentThreadHasVisited = std::find(ids.begin(), ids.end(), threadID) != ids.end();
        // let this thread view the room
        if (roomStatus == RoomStatus::AVAILABLE && !currentThreadHasVisited && randomGuestId == threadID)
        {
            roomStatus == RoomStatus::BUSY;
            std::cout << "thread: " << threadID << " is viewing the vase" << std::endl;
            roomStatus = RoomStatus::AVAILABLE;

            ids.push_back(threadID);
        }

        mutex.unlock();
    }
}

// Used to pick which thread to go next
int genRandomNumber(int lowerBound, int upperBound)
{
    // Generate a random number between lowerBound and upperBound (inclusive)
    return rand() % (upperBound - lowerBound + 1) + lowerBound;
}