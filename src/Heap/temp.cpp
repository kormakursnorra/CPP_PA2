// heap.cpp
#include "heap.h"
#include <cassert>

// Default constructor - create empty heap with initial capacity
// Time: O(1)
Heap::Heap() {
    capacity = 4;              // Start small, will grow as needed
    heap_size = 0;             // No elements yet
    data = new int[capacity];  // Allocate initial array
}

// Copy constructor - deep copy from another heap
// Time: O(n)
Heap::Heap(const Heap& other) {
    capacity = other.capacity;
    heap_size = other.heap_size;
    data = new int[capacity];  // Allocate NEW memory
    
    // Copy all elements
    for (int i = 0; i < heap_size; i++) {
        data[i] = other.data[i];
    }
}

// Assignment operator - deep copy via assignment
// Time: O(n)
Heap& Heap::operator=(const Heap& other) {
    // Check for self-assignment
    if (this == &other) {
        return *this;
    }
    
    // Delete old data
    delete[] data;
    
    // Copy from other
    capacity = other.capacity;
    heap_size = other.heap_size;
    data = new int[capacity];
    
    for (int i = 0; i < heap_size; i++) {
        data[i] = other.data[i];
    }
    
    return *this;
}

// Destructor - free allocated memory
// Time: O(1)
Heap::~Heap() {
    delete[] data;
}

// Double the capacity when array is full
// Time: O(n) - but amortized O(1) per push
void Heap::resize() {
    capacity *= 2;  // Growth factor of 2
    int* new_data = new int[capacity];
    
    // Copy all elements to new array
    for (int i = 0; i < heap_size; i++) {
        new_data[i] = data[i];
    }
    
    // Free old memory and update pointer
    delete[] data;
    data = new_data;
}

// Move element UP the tree if it's smaller than parent
// Time: O(log n) - height of tree
void Heap::bubbleUp(int index) {
    // While not at root and smaller than parent
    while (index > 0) {
        int parent_index = (index - 1) / 2;
        
        // If heap property satisfied, we're done
        if (data[index] >= data[parent_index]) {
            break;
        }
        
        // Swap with parent
        int temp = data[index];
        data[index] = data[parent_index];
        data[parent_index] = temp;
        
        // Move up to parent's position
        index = parent_index;
    }
}

// Move element DOWN the tree if it's larger than children
// Time: O(log n) - height of tree
void Heap::bubbleDown(int index) {
    while (true) {
        int left_child = 2 * index + 1;
        int right_child = 2 * index + 2;
        int smallest = index;
        
        // Find smallest among parent and children
        if (left_child < heap_size && data[left_child] < data[smallest]) {
            smallest = left_child;
        }
        if (right_child < heap_size && data[right_child] < data[smallest]) {
            smallest = right_child;
        }
        
        // If parent is smallest, heap property satisfied
        if (smallest == index) {
            break;
        }
        
        // Swap with smallest child
        int temp = data[index];
        data[index] = data[smallest];
        data[smallest] = temp;
        
        // Move down to child's position
        index = smallest;
    }
}

// Insert element into heap
// Time: O(log n)
void Heap::push(int value) {
    // Resize if full
    if (heap_size == capacity) {
        resize();
    }
    
    // Add element at end
    data[heap_size] = value;
    
    // Bubble up to maintain heap property
    bubbleUp(heap_size);
    
    heap_size++;
}

// Remove minimum element (root)
// Time: O(log n)
void Heap::pop() {
    assert(heap_size > 0);  // Can't pop empty heap
    
    heap_size--;
    
    // If heap becomes empty, we're done
    if (heap_size == 0) {
        return;
    }
    
    // Move last element to root
    data[0] = data[heap_size];
    
    // Bubble down to maintain heap property
    bubbleDown(0);
}

// Access minimum element (root)
// Time: O(1)
int Heap::peek() const {
    assert(heap_size > 0);  // Can't peek empty heap
    return data[0];
}

// Get number of elements
// Time: O(1)
int Heap::size() const {
    return heap_size;
}

// heap.h

struct Heap {
    // Member variables (public by default in struct)
    int* data;
    int capacity;
    int heapSize;
    
    // Helper functions
    void bubbleUp(int index);
    void bubbleDown(int index);
    void resize();
    
    // Public interface
    Heap();                           // Constructor
    Heap(const Heap& other);          // Copy constructor
    Heap& operator=(const Heap& other); // Assignment
    ~Heap();                          // Destructor
    
    void push(int value);
    void pop();
    int peek() const;
    int size() const;
};


// main.cpp
#include "heap.h"
#include <cstdio>

int main() {
    int q;
    scanf("%d", &q);  // Number of operations
    
    // Array to hold up to 1000 heap instances
    // Initialize all to nullptr (no heap created yet)
    Heap* heaps[1001];  // Index 0 unused, instances are 1-1000
    for (int i = 0; i <= 1000; i++) {
        heaps[i] = nullptr;
    }
    
    // Process each operation
    for (int i = 0; i < q; i++) {
        int id;
        char op;
        scanf("%d %c", &id, &op);
        
        // If this heap doesn't exist yet, create it
        if (heaps[id] == nullptr) {
            heaps[id] = new Heap();
        }
        
        if (op == '+') {
            // Push operation
            int value;
            scanf("%d", &value);
            heaps[id]->push(value);
            
        } else if (op == '-') {
            // Pop operation
            heaps[id]->pop();
            
        } else if (op == 'p') {
            // Peek operation - output minimum
            printf("%d\n", heaps[id]->peek());
            
        } else if (op == 's') {
            // Size operation - output size
            printf("%d\n", heaps[id]->size());
            
        } else if (op == 'a') {
            // Copy operation
            int source_id;
            scanf("%d", &source_id);
            
            // If target heap already exists, delete it first
            if (heaps[id] != nullptr) {
                delete heaps[id];
            }
            
            // Copy from source heap
            heaps[id] = new Heap(*heaps[source_id]);
        }
    }
    
    // Clean up all created heaps
    for (int i = 1; i <= 1000; i++) {
        if (heaps[i] != nullptr) {
            delete heaps[i];
        }
    }
    
    return 0;
}


g++ -Wall -Wextra -g heap.cpp main.cpp -o heap_test
echo "7
1 + 1
1 p
1 + 2
1 p
1 s
1 -
1 s" | ./heap_test