#include <array>

class SafeBuffer
{
    int head;
    int tail;
    int size;
    int arr[1000];

    public: SafeBuffer()
    {
        head = 0;
        tail = 0;
        size = 1000;
        arr[0] = 0;
    }
    ~SafeBuffer();
    bool isEmpty();
    bool isFull();
    void enqueue(int value);
    void dequeue();
    void printQueue();
    void frontQueue();
    void backQueue();
    void details();
};