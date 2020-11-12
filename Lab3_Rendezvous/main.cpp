/*!   \mainpage Lab 3 -  Semaphores and Mutual Exclusion - RENDEZVOUS
      \author Theodora Tataru, Student No: C00231174\n  
      \date 30 October 2020 
      \copyright  License: GNU Affero General Public License v3.0 
      \section Abstract
      \subsection An Implementation of a Rendezvous using Semaphores 
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
  \fn void taskOne(std::shared_ptr<Semaphore> taskOneArrived,std::shared_ptr<Semaphore>  taskTwoArrived, int delay)
  \brief This method has a 'randezvous' point with the method called 'taskTwo'. First part of the method will execute, 
  followed by the first part of taskTwo. Then, taskTwo will signal and resume the rest of the method, again when finishing giving the 
  control back to TaskTwo to resume it's execution.
  \param taskOneArrived signals that first part of the function had been executed
  \param taskTwoArrived puts the thread into the queue, waiting for it's turn
  \param delay indicates the time the function will sleep, before starting the execution
  displays a message that is split in to 2 sections to show how a rendezvous works*/
void taskOne(std::shared_ptr<Semaphore> taskOneArrived,std::shared_ptr<Semaphore>  taskTwoArrived, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  std::cout << "Task One has arrived! "<< std::endl;
  taskOneArrived->Signal();
  //THIS IS THE RENDEZVOUS POINT!
  taskTwoArrived->Wait();
  std::cout << "Task One has left! "<<std::endl;
}

  /*! 
  \fn void taskTwo(std::shared_ptr<Semaphore> firstSem, std::shared_ptr<Semaphore> secondSem, int delay)
  \brief This runs divided into 2, the first statement will print and then will give control to the next function.
  \param taskOneArrived puts the thread in the queue waiting for its turn
  \param taskTwoArrived signals that the thread had finished it's execution until this particular line
  \param delay indicates the time the function will sleep, before starting the execution
  displays a message that is split in to 2 sections to show how a rendezvous works*/
void taskTwo(std::shared_ptr<Semaphore> taskOneArrived, std::shared_ptr<Semaphore> taskTwoArrived, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  std::cout << "Task Two has arrived! "<<std::endl;
  taskTwoArrived->Signal();
  //THIS IS THE RENDEZVOUS POINT!
  taskOneArrived->Wait();
  std::cout << "Task Two has left! "<<std::endl;
}

/*!
  \fn main(void)
  \brief This is the main method of the code that creates 2 threads
  \return The main method returns 0, for the normal exit of a program
*/
int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem1( new Semaphore);
  std::shared_ptr<Semaphore> sem2( new Semaphore);
  int taskOneDelay=1;
  int taskTwoDelay=1;
  /**< Launch the threads  */
  threadOne=std::thread(taskTwo,sem1,sem2,taskTwoDelay);
  threadTwo=std::thread(taskOne,sem1,sem2,taskOneDelay);
  std::cout << "Launched from the main\n";
  threadOne.join();
  threadTwo.join();
  return 0;
}
