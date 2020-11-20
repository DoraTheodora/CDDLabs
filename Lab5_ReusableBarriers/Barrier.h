/**
 *\file 
 */
/*!   \mainpage Lab - Mutual Exclusion (mutex)
      \author Theodora Tataru, Student No: C00231174\n  
      \date 20 November 2020 
      \copyright  License: GNU Affero General Public License v3.0 
      \section Abstract
      \subsection Implementing a barrier class, using semaphores
*/

/*!
    \class Barrier 
    \brief This file is the abstract definition of the Barrier class
*/
#include "Semaphore.h"
#pragma once //only include the #include once

class Barrier
{
  int threadCount;
  int threadTotal;

  Semaphore mutex{1}; /*!< This semphore is initiated to value 1 as it will act as mutex */
  Semaphore turnstileOne{0}; /*!< This semphore is initiated to value 0 and is the pair of turnstileTwo. It will alayws have the opposite value of turnstileTwo */
  Semaphore turnstileTwo{1}; /*!< This semphore is initiated to value 1 and is the pair of turnstileOne. It will alayws have the opposite value of turnstileOne */

 public:
 /*!
    \fn Barrier(int totalThreads)
    \param totalThreads represents the number of threads the barrier will handle 
    \brief This is the constructor of the Barrier class
*/
  Barrier(int totalThreads)
    {
      threadCount = 0;
      threadTotal = totalThreads;
    }; //numThreads = totalThreads
  virtual ~Barrier(); /*!< Destructors are always VIRTUAL */
  void phaseOne();
  void phaseTwo();
};


/* Barrier.h ends here */
