#ifndef HEAP_H
#define HEAP_H

struct Heap{
    int* data;
    int capacity;
    int heapSize;

    void bubbleUp(int index);
    void bubbleDown(int index);
    void resize();

    Heap(); // Construct
    Heap(const Heap& other); // Copy
    Heap& operator=(const Heap& other); // Assignment
    ~Heap(); // Destruct
    void push(int val);
    void pop();
    int peek() const;
    int size() const;
};

#endif