# Program Assignment 2 (c++) COP4250 (Ubuntu 22.04)

## HOW TO RUN

I Included a bash script that will compile and run the c++ files with version 20

1. In the root dir run the command

   ```bash
   bash compileAndRun.bash problem1.cpp
   ```

   or

   ```bash
   bash compileAndRun.bash problem2.cpp
   ```

   depending on which problem you are testing of course

   For both problems the number of threads can be changed by altering

   ```c
   #define NUM_GUESS <int>
   ```

   at the top of the program

## My Approach / Experimental Evaluation (PROBLEM 1)

When I first starting working through the problem I was too focused on the cupcake, and whether or not It played a larger role in solving the problem. I was unsure as of how I would show that all threads with sharing information would communicate to finish the task. When I stopped thinking that all the threads needed to be doing the same thing and 1 of the threads could be used as a counter, things started to make more sense.

So to solve this:

- One of the threads is used as a counter, this thread counts the amount of times it was replaced the cupcake in the labyrinth
  - this thread will also account for it self when going through the labyrinth
- Every other thread will continue through the maze when picked (randomly) and eating the cupcake (only once per thread)

This process is continued until the cupcake has been replace NUM_GUEST(number of threads) times, this will ensure every thread has been through the labyrinth at least once.

## Correctness and Efficiency (PROBLEM 1)

A vector is used to keep track of the threads, and if they has visited the labyrinth or not, a validation check is ran at the end of the main call to ensure all of the threads have had a chance to visit. This check if ran on the main thread after everything else has been finished

We could say the the Runtime of the program would just be O(n) where n equals the number of guess. However, since we are randomly selecting guest this assumption isn't possible

## My Approach / Experimental Evaluation (PROBLEM 2)

This problem was a lot easier to think about than number 1. For a protocol I went with number 2. I think protocol 2 makes the most sense, it allows threads to view the vase when they want as long as the room is available, if not they will have to come back in a few moments to check again. protocol 1 explains its own problem with guess pooling up at the door. And with protocol 3 you would have to wait in a line and not be able to come and go freely.

## Correctness and Efficiency (PROBLEM 2)

A global vector is kept with all thread ids that have viewed the vase. Along with this, the program will not terminate unless every thread has view the vase at least once.

Since we are just dealing with threads here, the runtime should only be O(n) where n is the number of threads used. However, the longer the program operates(the more threads used), the amount of checks happening the view the vase will increase, This will slow down runtime.
