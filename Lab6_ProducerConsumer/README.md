# This lab handles the Producer-Consumer problem, using a queue and threads

1. The project is protected by "License: GNU Affero General Public License v3.0"
2. Project actors:
    - <b>Author:</b> Theodora Tataru
    - <b>Tutor:</b> Joseph Kehoe
    - <b>Institution:</b> Institute of Technology Carlow
    - <b>Date:</b> 20 November 2020
3. How to install project
    - run 'make' in the root project folder 
    - run ./ProducerConsumer_exe
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
    - <b>SafeBuffer.h</b>- the SafeBuffer header class, that defines the abstract methods that need to be implemented
    - <b>SafeBuffer.cpp </b>- the SafeBuffer class, that implements the logic of the queue data structure
    - <b>makefile </b>- the script for compiling the program

7. Detailes:
    1. This lab goal is to syncronize N threads in such a way, so that producers are able to write data to a data structure
        before consumers are allowed to read from the data strucure
    2. How the goal was achieved
        - <b>SafeBuffer</b> class implements a classic queue
        - <b>Semaphore</b> class defines the semaphores objects
        - <b>main </b> contains the threads, that need to be ordered in their execution