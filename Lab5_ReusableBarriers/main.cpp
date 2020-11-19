/*!   \mainpage Lab - Mutual Exclusion (mutex)
      \author Theodora Tataru, Student No: C00231174\n  
      \date 03 November 2020 
      \copyright  License: GNU Affero General Public License v3.0 
      \section Abstract
      \subsection Implementing a barrier - 2 semaphores working in pairs - 
*/

#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>
#include "Barrier.h"

static const int num_threads = 5;
int sharedVariable=0;
int threadTurn = 0;


/*! \fn barrierTask
    \brief An example of using a reusable barrier
*/
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void updateTask(std::shared_ptr<Barrier> barrier, int numLoops)
{
  for(int i = 0; i < numLoops; i++)
  {
    std::cout << "A";
    barrier->wait();
    std::cout<< "B";
    barrier->wait();
  }
}


int main(void){
  std::vector<std::thread> vt(num_threads);
  //std::shared_ptr<Semaphore> mutexSem( new Semaphore(1));
  //std::shared_ptr<Semaphore> semaphore2( new Semaphore());
  //std::shared_ptr<Semaphore> semaphore3( new Semaphore(1));
  std::shared_ptr<Barrier> barrier(new Barrier(num_threads));
  /**< Launch the threads  */
  int i=0;
  for(std::thread& t: vt)
  {
    t=std::thread(updateTask,barrier,10);
  }
  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  std::cout << sharedVariable << std::endl;
  return 0;
}
