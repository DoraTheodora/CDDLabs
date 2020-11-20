
/*!   \mainpage Lab - Mutual Exclusion (mutex)
      \author Theodora Tataru, Student No: C00231174\n  
      \date 20 November 2020 
      \copyright  License: GNU Affero General Public License v3.0 
      \section Abstract
      \subsection Implementing a barrier class, using semaphores
*/

/*!
    \class Barrier 
    \brief This class implements a barrier, using 3 semaphores
    \param mutex{1}; This semphore is initiated to value 1 as it will act as mutex 
    \param turnstileOne{0}; This semphore is initiated to value 0 and is the pair of turnstileTwo. It will alayws have the opposite value of turnstileTwo 
    \param turnstileTwo{1}; This semphore is initiated to value 1 and is the pair of turnstileOne. It will alayws have the opposite value of turnstileOne 
*/
#include "Semaphore.h"
#include "Barrier.h"
#include <iostream>
/*! 
    \fn Barrier::~Barrier()
    \brief The destrucor is invoked automatically when the object goes out of scope or is explicitly destroyed by a call to delete
*/

Barrier::~Barrier()
{ 

}
/*!
    \fn void Barrier::phaseOne()
    \brief This function will handle the phase one of rendezvou between N threads
    With the help of the mutex, and the pair of sempahores, the threads are controlled on how they execute within the function
*/
void Barrier::phaseOne()
{
    mutex.Wait();           /*! \remark mutex.Wait() allows only one thread at the time to enter */
    threadCount++;
    /*! \remark if(threadCount==threadTotal) this conditional statement is executed only by the last thread */
    if(threadCount == threadTotal) 
    {
        std::cout << std::endl;
        turnstileTwo.Wait();    /*! \remark  turnstileTwo.Wait() closes second door */
        turnstileOne.Signal();  /*! \remark turnstileOne.Signal() opens first door */
    }
    mutex.Signal();         /*! \remark mutex.Signal() Signals the next thread that can proceed */
    turnstileOne.Wait();    /*! \remark turnstileOne.Wait() closes first door */
    turnstileOne.Signal();  /*! \remark turnstileOne.Signal() opens first door */
    
}

/*!
    \fn void Barrier::phaseTwo()
    \brief This function will handle the phase one of rendezvou between N threads
    With the help of the mutex, and the pair of sempahores, the threads are controlled on how they execute within the function
*/
void Barrier::phaseTwo()
{
    mutex.Wait();           /*! \remark mutex.Wait() allows only one thread at the time to enter */
    threadCount--;
    if(threadCount == 0)    /*! \remark if(threadCount==0) this conditional statement is executed only by the last thread */
    {
        std::cout << std::endl;
        turnstileOne.Wait();    /*! \remark turnstileOne.Wait() closes first door */
        turnstileTwo.Signal();  /*! \remark turnstileTwo.Signal() opens second door */
    }
    mutex.Signal();          /*! \remark mutex.Signal() Signals the next thread that can proceed */
    turnstileTwo.Wait();     /*! \remark turnstileTwo.Wait() closes second door */
    turnstileTwo.Signal();   /*! \remark turnstileTwo.Signal() opens second door */
} 
// Barrier.cpp ends here
