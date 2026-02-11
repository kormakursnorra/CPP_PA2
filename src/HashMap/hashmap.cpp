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

Node* HashMap::find(int key) {
    if (capacity == 0) {
        return NULL;  
    }

    int hashed_key = hash(key);
    Node* current = nodes[hashed_key];
    while (current) {
        if (current->key == key) {
            return current;
        }
        current = current->next;
        
    }
    return NULL;
}

void HashMap::insert(int key, int value) {
    if (find(key)) {
        return;
    } else {
        int hashed_key = hash(key);
        Node* new_node = new Node;
        new_node->key = key;
        new_node->value = value;
        new_node->next = nodes[hashed_key];
        nodes[hashed_key] = new_node;
        count++;
    }
}

void HashMap::erase(int key) {
    if (find(key)) {
        return;
    }
    int hashed_key = hash(key);
    Node* prev = NULL;
    Node* current = nodes[hashed_key];
    while (current) {
        if (current->key == key) {
            if (prev == NULL) {
                count--;
                delete(nodes[hashed_key]);
                return;
            } else if (prev->next == current->next) {
                delete(current);
                count--;
                return;
            }
        }
        prev = current;
        current = current->next;
    }
}

int HashMap::hashSize() const {
    return count;
}