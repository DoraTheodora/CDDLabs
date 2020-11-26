

class SafeBuffer
{
    int head;
    int tail;
    int arr[10];
    int size = 10;

    public: SafeBuffer()
    {
        head = 0;
        tail = 0;
    }
    
    bool isEmpty();
    bool isFull();
    void enqueue(int value);
    int dequeue();
    void printQueue();
    int frontQueue();
};