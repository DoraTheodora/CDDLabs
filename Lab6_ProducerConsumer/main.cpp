#include "SafeBuffer.h"
#include "Semaphore.h"
#include "Event.h"
#include <iostream>
#include <thread>
#include <vector>


static const int num_threads = 10;
const int size=20;
int number = 0;

void producer(std::shared_ptr<SafeBuffer> queue, std::shared_ptr<Semaphore> mutex, 
std::shared_ptr<Semaphore> consumer, int numLoops)
{
    mutex->Wait();
    number = number + 10;
    queue->enqueue(number);
    std::cout << "Enqueue : " << queue->frontQueue() << std::endl;
    consumer->Signal();
    mutex->Signal();
}

void consumer(std::shared_ptr<SafeBuffer> queue, std::shared_ptr<Semaphore> mutex, 
std::shared_ptr<Semaphore> consumer, int numLoops)
{
  consumer->Wait();
  mutex->Wait();
  int x = queue->dequeue();
  std::cout << "Dequed : " << x << std::endl;
  mutex->Signal();
} 

  void testingQueue(SafeBuffer queue)
  {
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    queue.enqueue(5);
    queue.enqueue(6);
    queue.enqueue(7);
    queue.enqueue(8);
    queue.enqueue(9);
    queue.enqueue(10);
    queue.enqueue(11);
    queue.enqueue(12);

    queue.printQueue();
    queue.dequeue();
    std::cout << std::endl;
    queue.printQueue();
    std::cout << queue.isEmpty() << std::endl;
  }

int main(void){
  
  std::vector<std::thread> vp(num_threads);
  std::vector<std::thread> vc(num_threads);
  std::shared_ptr<SafeBuffer> queue (new SafeBuffer());
  std::shared_ptr<Semaphore> mutex (new Semaphore(1));
  std::shared_ptr<Semaphore> consumers (new Semaphore(0));

  int i=0;
  for(std::thread& t: vp)
  {
    t=std::thread(producer,queue,mutex,consumers,10);
  }
    for(std::thread& t: vc)
  {
    t=std::thread(consumer,queue,mutex,consumers,10);
  }
  for (auto& v :vp){
      v.join();
  }
    for (auto& v :vc){
      v.join();
  }
  std::cout << "Queue: " << std::endl;

  //queue->printQueue();

  
  //testingQueue(queue);
  return 0;
}
