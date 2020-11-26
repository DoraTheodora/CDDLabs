#include <iostream>
#include "SafeBuffer.h"


bool SafeBuffer::isEmpty()
{
    if(head == 0 && tail ==0)
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
    if(tail >= size)
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
    }
}

int SafeBuffer::dequeue()
{
    if(!isEmpty())
    {
        int x = arr[tail-1];
        tail--;
        return x;
    }
    return -1;
}

void SafeBuffer::printQueue()
{
    for(int i = 0; i < tail; i++)
    {
        std::cout << arr[i] << std::endl;
    }
}

int SafeBuffer::frontQueue()
{
    return arr[tail-1];
}