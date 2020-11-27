

class SafeBuffer
{
    int head;
    int tail;
    int size;
    int arr[];

    public: SafeBuffer(int sizeOfArray)
    {
        head = 0;
        tail = 0;
        arr[sizeOfArray];
        size = sizeOfArray;
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

};