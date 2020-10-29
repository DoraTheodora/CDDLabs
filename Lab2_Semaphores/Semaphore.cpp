/*!   \mainpage Lab 2 - Semaphores 
      \author Theodora Tataru, Student No: C00231174\n  
      \date 27 October 2020 
      \copyright  License: GNU Affero General Public License v3.0 
      \name Lab 2 - Semaphores 
      \subsection Semaphores, another important contribution by E. W. Dijkstra, can be viewed as an extension to mutex locks. \n A semaphore is an object with two methods Wait and Signal, a private integer counter and a private queue (of threads). \n The semantics of a semaphore is very simple. Suppose S is a semaphore whose private counter has been initialized to a non-negative integer. 
      \subsection Reference: https://pages.mtu.edu/~shene/NSF-3/e-Book/SEMA/basics.html
*/
#include "Semaphore.h"
/*!   \class Semaphore
      \brief A Semaphore Implementation
      \note The value of the semaphores cannot be requested, as is irrelevant because values are unpredictable!!!
      Uses C++11 features such as mutex and condition variables to implement Semaphore
*/

      /*!
      \fn Semaphore::Wait()
      \brief When Wait is executed by a thread, we have two possibilities:
            The counter of S is positive
            In this case, the counter is decreased by 1 and the thread resumes its execution.
            The counter of S is zero
            In this case, the thread is suspended and put into the private queue of S.
            \n
      \link https://pages.mtu.edu/~shene/NSF-3/e-Book/SEMA/basics.html
      */
void Semaphore::Wait()
{
      std::unique_lock< std::mutex > lock(m_mutex);
      m_condition.wait(lock,[&]()->bool{ return m_uiCount>0; });
      --m_uiCount;
}

template< typename R,typename P >
bool Semaphore::Wait(const std::chrono::duration<R,P>& crRelTime)
{
      std::unique_lock< std::mutex > lock(m_mutex);
      if (!m_condition.wait_for(lock,crRelTime,[&]()->bool{ return m_uiCount>0; })){
	  return false;
      }
      --m_uiCount;
      return true;
}

      /*!
      \fn Semaphore::Signal()
      \brief When Signal is executed by a thread, we also have two possibilities:
      The queue of S has no waiting thread
      The counter of S is increased by one and the thread resumes its execution.
      The queue of S has waiting threads
      In this case, the counter of S must be zero (see the discussion of Wait above). One of the waiting threads will be allowed to leave the queue and resume its execution. The thread that executes Signal also continues.
      \n
      \link https://pages.mtu.edu/~shene/NSF-3/e-Book/SEMA/basics.html
      */
void Semaphore::Signal()
{
      std::unique_lock< std::mutex > lock(m_mutex);
      ++m_uiCount;
      m_condition.notify_one();
}
