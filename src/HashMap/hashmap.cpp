#include "hashmap.h"
#include <cstddef>

HashMap::HashMap() {
    capacity = 4;
    count = 0;
    nodes = new Node*[capacity];
    for (int i = 0; i < capacity; i ++) {
        nodes[i] = NULL;
    }
}

long long mod(long long k, long long n) {
    return ((k % n) + n) % n;
}

int HashMap::hash(int key) {
    return mod(key, capacity);
}

void HashMap::insert(int key, int value) {
    return; 
}




int HashMap::hashSize() const {
    return count;
}