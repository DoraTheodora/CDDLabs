# This lab is barries implemented with the use of 3 semaphores

1. The project is protected by "License: GNU Affero General Public License v3.0"
2. Project actors:
    - <b>Author:</b> Theodora Tataru
    - <b>Tutor:</b> Joseph Kehoe
    - <b>Institution:</b> Institute of Technology Carlow
    - <b>Date:</b> 20 November 2020
3. How to install project
    - run 'make' in the root project folder 
    - run ./Barrier_exe 
4. Requirements:
    - <b> Linux </b> environment
    - <b> G++ </b>  for compiling
    - <b> gdp </b>  for debugging
    - <b> make </b>  for managing code
    - <b> pthread </b>  
5. This lab is completed, and works if you type the command "make" in the terminal
    - for any errors please pm C00231174@itcarlow.ie
6. List of files:
    - <b>main.cpp </b>- the main process from where the programs starts
    - <b>semaphore.h </b>- the SEMAPHORE header class, for managing threads
    - <b>semaphore.cpp </b>- the SEMAPHORE class, for managing threads with implemented function
    - <b>barrier.h</b>- the BARRIER header class, for managing threads
    - <b>barrier.cpp </b>- the BARRIER class, for managing threads with implemented function
    - <b>makefile </b>- the script for compiling the program

7. Detailes:
    1. This lab goal is to syncronize N threads in such a way, so that the critical section to don't be executed until all threads had executed the rendezvous 
    2. How the goal was achieved
        - <b>barrier</b> class implements a rendezvous for N threads, using semaphores and mutexs
        - <b>semmaphore</b> class defines the semaphores objects
        - <b>main </b> contains the threads, that need to be ordered in their execution