#include "SafeBuffer.h"
#include <iostream>

SafeBuffer::~SafeBuffer() = default;

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

void SafeBuffer::enqueue(int value)
{
    if(!isFull())
    {
        arr[tail] = value;
        tail++;
        backQueue();
    } 
}

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

void SafeBuffer::backQueue()
{
    if(!isEmpty())
    {
      std::cout << arr[tail-1] << std::endl;
    }
}

void SafeBuffer::details()
{
    std::cout << "Tail: " << tail << std::endl;
    std::cout << "Head: " << head << std::endl;
    std::cout << "Size: " << sizeof(arr) << std::endl;
}
