#include "heap.h"
#include <cassert>

// Create empty Heap
Heap::Heap() {
    capacity = 4; // Start small
    heapSize = 0;
    data = new int[capacity]; // start array
}

Heap::Heap(const Heap& other) {
    capacity = other.capacity;
    heapSize = other.heapSize;
    data = new int[capacity]; // allocate new memory
    
    for (int i = 0; i < heapSize; i++) {
        data[i] = other.data[i];
    }
}

// Assignment op
Heap& Heap::operator=(const Heap& other) {
    if (this == &other) {
        return *this;
    }

    delete[] data;

    capacity = other.capacity;
    heapSize = other.heapSize;
    data = new int[capacity];

    for (int i = 0; i < heapSize; i++) {
        data[i] = other.data[i];
    }

    return *this;
}

// Destuct
Heap::~Heap() {
    delete[] data; 
}

// Double capacity when arr is full
void Heap::resize() {
    capacity *=2;
    int* newData = new int[capacity];

    for (int i = 0; i < heapSize; i++) {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
}

// Move elements upp da tree
void Heap::bubbleUp(int index) {
    // while not at root and smaller then parent
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
    
        if (data[index] >= data[parentIndex]) {
            break;
        }

        int temp = data[index];
        data[index] = data[parentIndex];
        data[parentIndex] = temp;

        index = parentIndex;
    }
}

void Heap::bubbleDown(int index) {
    while (true) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < heapSize && data[leftChild] < data[smallest]) {
            smallest = leftChild;
        }
        if (rightChild < heapSize && data[rightChild] < data[smallest]) {
            smallest = rightChild;
        }

        // If parent is smallest heap is satisfied
        if (smallest == index) {
            break;
        }

        int temp = data[index];
        data[index] = data[smallest];
        data[smallest] = temp;

        // move to child position
        index = smallest;
    }
}

void Heap::push(int value) {
    if (heapSize >= capacity) {
        resize();
    }

    data[heapSize] = value;
    bubbleUp(heapSize);
    heapSize++;
}

void Heap::pop() {
    // Cant pop from empty heap
    assert(heapSize > 0);
    heapSize--;

    if (heapSize == 0) {
        return;
    }
    data[0] = data[heapSize];
    bubbleDown(0);
}

int Heap::peek() const {
    assert(heapSize > 0);
    return data[0];
}

int Heap::size() const {
    return heapSize;
}