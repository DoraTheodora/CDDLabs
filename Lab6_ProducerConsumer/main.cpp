#include "SafeBuffer.h"
#include "Semaphore.h"
#include "Event.h"
#include <iostream>
#include <thread>
#include <vector>


static const int num_threads = 12;
const int size=20;
int number = 0;

void producer(std::shared_ptr<SafeBuffer> queue, std::shared_ptr<Semaphore> mutex, 
std::shared_ptr<Semaphore> consumer)
{
    mutex->Wait();
    number = number + 10;
    std::cout << "Enqueue: ";
    queue->enqueue(number);
    mutex->Signal();
    consumer->Signal();
}

void consumer(std::shared_ptr<SafeBuffer> queue, std::shared_ptr<Semaphore> mutex, 
std::shared_ptr<Semaphore> consumer)
{
  consumer->Wait();
  mutex->Wait();
  std::cout << "Dequed: ";
  queue->dequeue();
  mutex->Signal();
} 

  void testingQueue(SafeBuffer queue)
  {
    for(int i = 0 ; i <= 110; i=i+10)
    {
      queue.enqueue(i);
    }
    for(int i = 0 ; i <= 11; i++)
    {
      queue.dequeue();
    }

    //std::cout << std::endl;
    //queue.printQueue();
    //std::cout << queue.isFull() << std::endl;
  }
int main(void)
{

  std::vector<std::thread> vp(num_threads);
  std::vector<std::thread> vc(num_threads);
  std::shared_ptr<SafeBuffer> queue (new SafeBuffer(1000));
  std::shared_ptr<Semaphore> mutex (new Semaphore(1));
  std::shared_ptr<Semaphore> consumers (new Semaphore(0));

  int i=0;
  for(std::thread& t: vp)
  {
    t=std::thread(producer,queue,mutex,consumers);
  }

  for(std::thread& t: vc)
  {
    t=std::thread(consumer,queue,mutex,consumers);
  }

  for (auto& v :vp){
    v.join();
  }
  
  for (auto& v :vc){
    v.join();
  } 

  //free(&queue);
  //queue.reset();

  //SafeBuffer  q (100);
  //testingQueue(q);
  //queue->printQueue();
  return 0;
}
