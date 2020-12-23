/*!   \mainpage Lab - Producer - Consumer Problem
      \author Theodora Tataru, Student No: C00231174\n  
      \date 10 December 2020 
      \copyright  License: GNU Affero General Public License v3.0 
      \section Abstract
      \subsection Implement a SafeBuffer class using the Semaphore class
*/

/*! Using C++ Sempahores, and a collectivectors of threads, a solution was implemented
for the Producer-Consumer Problem. The safe buffer was designed as queue with the FIFO rule:
First element in is the first element out.
*/

/*! 
  \file main.cpp
  \brief In this file the threads are created and manipulated in such a way, that consumers can read and manipulate
  data from producers, only and only if data is present.
*/

#include "SafeBuffer.h"
#include "Semaphore.h"
#include "Event.h"
#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>


 /*! \remark static const int num_threads = 12; represents the number of threads*/
static const int num_threads = 100; 
int number = 0;

/*! \fn void producer(std::shared_ptr<SafeBuffer> queue, std::shared_ptr<Semaphore> mutex, std::shared_ptr<Semaphore> consumer)
    \param queue is the queue action, when data is added into the datastructure
    \param mutex is the semaphore that ensures that only one thread at the time can write data into the queue
    \param consumer is a semaphore that signals the consumer threads, that one thread canm proceed and dequeue from the data structure
    \brief This method allows one thread at the time to write data to the queue, and signals the consumer threads that one thread can read data from the queue
*/
void producer(std::shared_ptr<SafeBuffer> queue, std::shared_ptr<Semaphore> mutex, 
std::shared_ptr<Semaphore> consumer)
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

/*! \fn void consumer(std::shared_ptr<SafeBuffer> queue, std::shared_ptr<Semaphore> mutex, std::shared_ptr<Semaphore> consumer)
    \param queue is the queue action, when data is removed from the datastructure
    \param mutex is the semaphore that ensures that only one thread at the time can read data into the queue
    \param consumer is a semaphore that signals the consumer threads, that they need to wait for the producers to write data to the queue
    \brief When a tread finishes to read datas from the queue, blocks the other thread consumers to read data, until a producer thread writes data to the queue
*/
void consumer(std::shared_ptr<SafeBuffer> queue, std::shared_ptr<Semaphore> mutex, 
std::shared_ptr<Semaphore> consumer)
{
  //space->Wait();
  consumer->Wait();
  mutex->Wait();
  std::cout << "Dequed: ";
  queue->dequeue();
  mutex->Signal();
  //space->Signal();
} 



/*! \fn void testingQueue(SafeBuffer queue)
    \param queue is the queue datastructure
    \brief This method was used to exercise the queue datastructure logic
*/
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
  /*! \remark std::vector<std::thread> vp(num_threads) created the N  producer threads */
  std::vector<std::thread> vp(num_threads);
  /*! \remark std::vector<std::thread> vc(num_threads) created the N  consumer threads */
  std::vector<std::thread> vc(num_threads);

  /*! \remark std::shared_ptr<SafeBuffer> queue (new SafeBuffer()); instanciates the safe buffer (queue) object*/
  std::shared_ptr<SafeBuffer> queue (new SafeBuffer());
  /*! \remark std::shared_ptr<Semaphore> mutex (new Semaphore(1)); instanciates of a Sempahore, that acts a mutex*/
  std::shared_ptr<Semaphore> mutex (new Semaphore(1));
  /*! \remark std::shared_ptr<Semaphore> consumers (new Semaphore(0)); instanciates of a Sempahore that dictates the consumer threads flow*/
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

  //SafeBuffer q = SafeBuffer();
  //testingQueue(q);

  //queue->printQueue();
  return 0;
}
