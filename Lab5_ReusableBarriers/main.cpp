/*!   \mainpage Lab - Mutual Exclusion (mutex)
      \author Theodora Tataru, Student No: C00231174\n  
      \date 20 November 2020 
      \copyright  License: GNU Affero General Public License v3.0 
      \section Abstract
      \subsection Implementing a barrier class, using semaphores and mutex
*/

#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>
#include "Barrier.h"

/*!
  \param num_threads denotes the number of threads that will be created
*/
static const int num_threads = 5;


/*! \fn void updateTask(std::shared_ptr<Barrier> barrier, int numLoops)
    \param barrier is a reusable barrier object to organise the flow of control between n threads
    \param numLoops denotes the number of iterations
    \brief An example of using a reusable barrier
*/
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void updateTask(std::shared_ptr<Barrier> barrier, int numLoops)
{
  for(int i = 0; i < numLoops; i++)
  {
    std::cout << "A";
    barrier->phaseOne();
    std::cout<< "B";
    barrier->phaseTwo();
  }
}


int main(void){

   /*! \remark std::vector<std::thread> vt(num_threads) created the N threads */
  std::vector<std::thread> vt(num_threads);
  //std::shared_ptr<Semaphore> mutexSem( new Semaphore(1));
  //std::shared_ptr<Semaphore> semaphore2( new Semaphore());
  //std::shared_ptr<Semaphore> semaphore3( new Semaphore(1));
  // instaciatiating the barrier class
  /*! \remark std::shared_ptr<Barrier> barrier(new Barrier(num_threads)) instanciates the barrier object*/
  std::shared_ptr<Barrier> barrier(new Barrier(num_threads)); 

  int i=0;
   /*! \remark t=std::thread(updateTask,barrier,10)) launches the threads*/
   /*! \note happens in a for each loop */
  for(std::thread& t: vt)
  {
    t=std::thread(updateTask,barrier,10);
  }
  
  /*! \remark fv.join() joins the threads in the main thread*/
  /*! \note happens in a for each loop */
  for (auto& v :vt){
      v.join();
  }
  return 0;
}
