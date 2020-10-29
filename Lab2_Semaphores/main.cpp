/*!   \mainpage Lab 2 - Semaphores 
      \author Theodora Tataru, Student No: C00231174\n  
      \date 27 October 2020 
      \copyright  License: GNU Affero General Public License v3.0 
      \name Lab 2 - Semaphores 
      \subsection Semaphores, another important contribution by E. W. Dijkstra, can be viewed as an extension to mutex locks. \n A semaphore is an object with two methods Wait and Signal, a private integer counter and a private queue (of threads). \n The semantics of a semaphore is very simple. Suppose S is a semaphore whose private counter has been initialized to a non-negative integer. 
      \subsection Reference: https://pages.mtu.edu/~shene/NSF-3/e-Book/SEMA/basics.html
*/

#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <unistd.h>
/*! \class Signal
    \brief An Implementation of Threads Using Semaphores 
    Uses C++11 features such as mutex and condition variables to implement Semaphores in thread functions 
*/

  /*! 
  \fn void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay)
  \brief This is a thread that sleeps for a certain amount of seconds, and then prints to the screen "I must print first"
  \param theSemaphore controls the control flow of the function
  \param delay indicates the time the thread will sleep
  */
void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay){
  sleep(delay);
  std::cout << "I ";
  std::cout << "must ";
  std::cout << "print ";
  std::cout << "first"<<std::endl;
  theSemaphore->Signal();
}

  /*! 
  \fn void taskTwo(std::shared_ptr<Semaphore> theSemaphore)
  \brief This thread prints to the screen "This will appear second"
  \param theSemaphore controls the control flow of the function
  */
void taskTwo(std::shared_ptr<Semaphore> theSemaphore){
  theSemaphore->Wait();
  std::cout << "This ";
  std::cout << "will ";
  std::cout << "appear ";
  std::cout << "second"<<std::endl;
}
/*!
  \fn main(void)
  \brief This is the main method of the code and starts the threads  
  \return The main method returns 0, for the normal exit of a program
*/
int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem( new Semaphore);

  int taskOneDelay=5;
  threadOne=std::thread(taskTwo,sem);
  threadTwo=std::thread(taskOne,sem,taskOneDelay);
  std::cout << "Launched from the main\n";
  
  threadOne.join();
  threadTwo.join();
  return 0;
}
