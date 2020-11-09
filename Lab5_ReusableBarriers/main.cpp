#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>


static const int num_threads = 5;
int sharedVariable=0;
int threadTurn = 0;


/*! \fn barrierTask
    \brief An example of using a reusable barrier
*/
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void updateTask(std::shared_ptr<Semaphore> mutexSem,std::shared_ptr<Semaphore> semTwo, std::shared_ptr<Semaphore> semThree, int numLoops)
{
  for(int i = 0; i < 3; i++)
  {
    mutexSem->Wait();
    //Do first bit of task
    std::cout << "A";
    threadTurn++;
    if(threadTurn == num_threads)
    {
      std::cout << std::endl;
      semThree->Wait();
      semTwo->Signal();
    }
    mutexSem->Signal();

    semTwo->Wait();
    //------ everybody stops here
    semTwo->Signal(); // signal the next thread that it can come

    mutexSem->Wait();
    threadTurn--;
    if(threadTurn == 0)
    {
      semTwo->Wait();
      semThree->Signal();
    }
    mutexSem->Signal();
    //Do second half of task
 
    std::cout<< "B";
    if(threadTurn == 0)
    {
      std::cout << std::endl;
    }
    semThree->Wait(); // second time, everyone waits here so no threads start the next iteration
    semThree->Signal();
    // all threads finish the loop in the same time
  }
}


int main(void){
  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<Semaphore> mutexSem( new Semaphore(1));
  std::shared_ptr<Semaphore> semaphore2( new Semaphore());
  std::shared_ptr<Semaphore> semaphore3( new Semaphore(1));
  /**< Launch the threads  */
  int i=0;
  for(std::thread& t: vt)
  {
    t=std::thread(updateTask,mutexSem,semaphore2, semaphore3,10);
  }
  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  std::cout << sharedVariable << std::endl;
  return 0;
}
