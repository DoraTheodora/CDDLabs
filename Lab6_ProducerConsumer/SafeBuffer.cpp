/*!   \mainpage Lab - Producer-Consumer
      \author Theodora Tataru, Student No: C00231174\n  
      \date 01 December 2020 
      \copyright  License: GNU Affero General Public License v3.0 
      \section Abstract
      \subsection Implementing a queue datastructure
*/

#include "SafeBuffer.h"
#include <iostream>

/*! \fn SafeBuffer::~SafeBuffer() = default
    \brief The destructor of the class
*/
SafeBuffer::~SafeBuffer() = default;

/*! \fn bool SafeBuffer::isEmpty()
    \brief A boolean method that returnUE if the queue has no values in it, and FALSE if there exists value in the data structure
*/
bool SafeBuffer::isEmpty()
{
    if(head == 0 && tail == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}


/*! \fn bool SafeBuffer::isFull()
    \brief A boolean bethod that returns TRUE if the data structure is full and cannot accept anymore values, and returns FALSE if there is room in the data structure for new values
*/
bool SafeBuffer::isFull()
{
    if(tail == size-1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*! \fn void SafeBuffer::enqueue(int value)
    \param value is the value that will be added in the data structure
    \brief This methid adds a new value in the datastructure, at the tail
*/
void SafeBuffer::enqueue(int value)
{
    if(!isFull())
    {
        arr[tail] = value;
        tail++;
        backQueue();
    } 
}


/*! \fn void SafeBuffer::dequeue()
    \brief This method removes an element from the datastructure, from the head of the queue (array index 0)
*/
void SafeBuffer::dequeue()
{
    if(!isEmpty())
    {
        frontQueue();
        for(int i = head; i < tail; i++)
        {
            arr[i] = arr[i+1];
        }
        tail--;
        //std::cout << "Arr base address: " <<  arr << std::endl;
    }
}

/*! \fn void SafeBuffer::printQueue()
    \brief This void method prints to the console all the elements from the data structure
*/
void SafeBuffer::printQueue()
{
    for(int i = 0; i < tail; i++)
    {
        std::cout << arr[i] << std::endl;
    }
}

void SafeBuffer::frontQueue()
{
    if(!isEmpty())
    {
      std::cout << arr[head] << std::endl;
    }
}

/*! \fn void SafeBuffer::backQueue()
    \brief This method prints the last element added into the data structure
*/
void SafeBuffer::backQueue()
{
    if(!isEmpty())
    {
      std::cout << arr[tail-1] << std::endl;
    }
}

/*! \fn void SafeBuffer::details()
    \brief This method prints details about the data structure\n
    \t Tail: the position of the last element from the data structure\n
    \t Head: the position of the first element from the data strucure\n
    \t Size: the size of the data structure\n
*/
void SafeBuffer::details()
{
    std::cout << "Tail: " << tail << std::endl;
    std::cout << "Head: " << head << std::endl;
    std::cout << "Size: " << sizeof(arr) << std::endl;
}
