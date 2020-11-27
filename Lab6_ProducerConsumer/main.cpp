#include "SafeBuffer.h"
#include "Semaphore.h"
#include "Event.h"
#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>


static const int num_threads = 12;
const int size=20;
int number = 0;

void producer(std::shared_ptr<SafeBuffer> queue, std::shared_ptr<Semaphore> mutex, 
std::shared_ptr<Semaphore> consumer, std::shared_ptr<Semaphore> space)
{
  //space->Wait();
  mutex->Wait();
  number = number + 10;
  std::cout << "Enqueue: ";
  queue->enqueue(number);
  mutex->Signal();
  consumer->Signal();
  //space->Signal();
}

void consumer(std::shared_ptr<SafeBuffer> queue, std::shared_ptr<Semaphore> mutex, 
std::shared_ptr<Semaphore> consumer, std::shared_ptr<Semaphore> space)
{
  //space->Wait();
  consumer->Wait();
  mutex->Wait();
  std::cout << "Dequed: ";
  queue->dequeue();
  mutex->Signal();
  //space->Signal();
} 

  void testingQueue(SafeBuffer queue)
  {
    queue.printQueue();
    queue.details();
    queue.enqueue(1);
    queue.details();
    queue.enqueue(2);
    queue.details();
    queue.enqueue(3);
    queue.details(); 
    queue.enqueue(4);
    queue.details();
    queue.enqueue(4);
    queue.details();
    queue.enqueue(4);
    queue.details();
    queue.enqueue(4);
    queue.details();
    queue.enqueue(4);
    queue.details();
    queue.enqueue(4);
    queue.details();

    /*
    for(int i = 0 ; i <= 110; i=i+10)
    {
      queue.enqueue(i);
    }
    for(int i = 0 ; i <= 11; i++)
    {
      queue.dequeue();
    }
    */
    //std::cout << std::endl;
    //queue.printQueue();
    //std::cout << queue.isFull() << std::endl;
  }
int main(void)
{
  
  std::vector<std::thread> vp(num_threads);
  std::vector<std::thread> vc(num_threads);
  std::shared_ptr<SafeBuffer> queue (new SafeBuffer());
  std::shared_ptr<Semaphore> mutex (new Semaphore(1));
  std::shared_ptr<Semaphore> consumers (new Semaphore(0));
  std::shared_ptr<Semaphore> space (new Semaphore(1));

  int i=0;
  for(std::thread& t: vp)
  {
    t=std::thread(producer,queue,mutex,consumers,space);
  }

  for(std::thread& t: vc)
  {
    t=std::thread(consumer,queue,mutex,consumers,space);
  }

  for (auto& v :vp){
    v.join();
  }
  
  for (auto& v :vc){
    v.join();
  } 

  //free(&queue);
  //queue.reset();

  //SafeBuffer q = SafeBuffer();
  //testingQueue(q);

  //queue->printQueue();
  return 0;
}
