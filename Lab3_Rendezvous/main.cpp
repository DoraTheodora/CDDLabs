/*!   \mainpage Lab 3 -  Semaphores and Mutual Exclusion
      \author Theodora Tataru, Student No: C00231174\n  
      \date 30 October 2020 
      \copyright  License: GNU Affero General Public License v3.0 
      \section Abstract
      \subsection Semaphores 
*/

#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <chrono>

/*! \class Signal
    \brief An Implementation of a Rendezvous using Semaphores

   Uses C++11 features such as mutex and condition variables to implement an example of a rendezvous for threads

*/
  /*! 
  \fn void taskOne(std::shared_ptr<Semaphore> firstSem,std::shared_ptr<Semaphore>  secondSem, int delay)
  \brief This is a thread that sleeps for a certain amount of seconds, and then prints to the screen "I must print first"
  \param firstSem gives the function the control of the first part of the function
  \param secondSem gives the function the control when for the second part of the function
  \param delay indicates the time the thread will sleep
  displays a message that is split in to 2 sections to show how a rendezvous works*/
void taskOne(std::shared_ptr<Semaphore> firstSem,std::shared_ptr<Semaphore>  secondSem, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  firstSem->Signal();
  std::cout << "Task One has arrived! "<< std::endl;
  //THIS IS THE RENDEZVOUS POINT!
  secondSem->Signal();
  std::cout << "Task One has left! "<<std::endl;
}

  /*! 
  \fn void taskTwo(std::shared_ptr<Semaphore> firstSem, std::shared_ptr<Semaphore> secondSem, int delay)
  \brief This runs divided into 2, the first statement will print and then will give control to the next function.
  \param firstSem puts the thread in the queue waiting for its turn
  \param secondSem puts the second part of the thread in the waiting queue, waiting for its turn 
  \param delay indicates the time the thread will sleep
  displays a message that is split in to 2 sections to show how a rendezvous works*/
void taskTwo(std::shared_ptr<Semaphore> firstSem, std::shared_ptr<Semaphore> secondSem, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  firstSem->Wait();
  std::cout << "Task Two has arrived! "<<std::endl;
  //THIS IS THE RENDEZVOUS POINT!
  secondSem->Wait();
  std::cout << "Task Two has left! "<<std::endl;
}

/*!
  \fn main(void)
  \brief This is the main method of the code and starts the threads  
  \return The main method returns 0, for the normal exit of a program
*/
int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem1( new Semaphore);
  std::shared_ptr<Semaphore> sem2( new Semaphore);
  int taskOneDelay=5;
  int taskTwoDelay=1;
  /**< Launch the threads  */
  threadOne=std::thread(taskTwo,sem1,sem2,taskTwoDelay);
  threadTwo=std::thread(taskOne,sem1,sem2,taskOneDelay);
  std::cout << "Launched from the main\n";
  threadOne.join();
  threadTwo.join();
  return 0;
}
