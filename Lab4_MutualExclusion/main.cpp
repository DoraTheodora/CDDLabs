/*!   \mainpage Lab - Mutual Exclusion (mutex)
      \author Theodora Tataru, Student No: C00231174\n  
      \date 03 November 2020 
      \copyright  License: GNU Affero General Public License v3.0 
      \section Abstract
      \subsection Implementing a mutex, using semaphores
*/

#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>

static const int num_threads = 100;
int sharedVariable=0;

/*! \fn updateTask(std::shared_ptr<Semaphore> firstSem, int numUpdates)
    \brief An Implementation of Mutual Exclusion using Semaphores
    \param mutex used to achieve mutual exclusion. 
    \param numUpdates is the variable incremented to prove the use of mutual exclusion. This parameter can be incremented by one thread at the time
  
  Uses C++11. In the main, the semaphore is initalized to the value of 1, so that
  first thread, to able to continue its execution when the WAIT method is called. The next thread will nead to wait for the
  thread inside the loop to signal so it can proceed.

*/
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void updateTask(std::shared_ptr<Semaphore> mutex, int numUpdates)
{
  // This is a mutex, only one thread can go into the loop at a time
  mutex->Wait();
  for(int i=0;i<numUpdates;i++)
  {
    //UPDATE SHARED VARIABLE HERE!
    sharedVariable++;
  }
  mutex->Signal();
  // realeasing the lock so other threads cab access the loop

}

/*!
  \fn main(void)
  \brief This is the main method that creates a semaphore initialized with the value of 1, so that first thread to be able to pass over the first WAIT of the semaphore. 
  \return The main method returns 0, for the normal exit of a program
*/
int main(void){
  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<Semaphore> aSemaphore( new Semaphore(1));
  
  /**< Launch the threads  */
  int i=0;
  for(std::thread& t: vt){
    t=std::thread(updateTask,aSemaphore,1000);
  }
  std::cout << "Launched from the main\n";
  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  std::cout << sharedVariable << std::endl;
  return 0;
}
