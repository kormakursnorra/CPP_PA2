#include "hashmap.h"
#include <cstdio>

HashMap::HashMap() {
    capacity = 4;
    count = 0;
    nodes = new Node*[capacity];
    for (int i = 0; i < capacity; i++) {
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

void HashMap::resize() {
    if (count >= capacity) {
        int old_capacity = capacity;
        Node** old_nodes = nodes;
        capacity = capacity * 2;
        nodes = new Node*[capacity];
        for (int i = 0; i < capacity; i++) {
            nodes[i] = NULL;
        }
        for (int i = 0; i < old_capacity; i++) {
            Node* current = old_nodes[i];
            while (current != NULL) {
                Node* temp = current->next;
                int new_hash_key = hash(current->key);
                current->next = nodes[new_hash_key];
                nodes[new_hash_key] = current;
                current = temp;
            }
        }
        delete[] old_nodes;
        return;
    } else {
        return;
    }
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
    resize();
}

void HashMap::erase(int key) {
    if (!find(key)) {
        return;
    }
    int hashed_key = hash(key);
    Node* prev = NULL;
    Node* current = nodes[hashed_key];
    while (current) {
        if (current->key == key) {
            if (prev == NULL) {
                count--;
                nodes[hashed_key] = current->next;
                delete(current);
                return;
            }
            prev->next = current->next;
            delete(current);
            count--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

int& HashMap::operator[](int key) {
    Node* node = find(key);
    return node->value;
}

HashMap::~HashMap() {
    Node* temp = NULL;
    for (int i = 0; i < capacity; i++) {
        Node* current = nodes[i];
        while (current != NULL) {
            temp = current->next;
            delete(current);
            current = temp;
        }
    }
    delete[] nodes;
}

HashMap::HashMap(const HashMap& other) {
    capacity = other.capacity;
    count = other.count;

    nodes = new Node*[capacity];
    for (int i = 0; i < capacity; i++) {
        nodes[i] = NULL;
    }
    for (int i = 0; i < other.capacity; i++) {
        Node* current = other.nodes[i];
        while (current != NULL) {
            Node* new_node = new Node;
            new_node->key = current->key;
            new_node->value = current->value;
            new_node->next = nodes[i];
            nodes[i] = new_node;
            current = current->next;
        }
    }
}

HashMap& HashMap::operator=(const HashMap& other) {
    if (this == &other) {
        return *this;
    }
    Node* temp = NULL;
    for (int i = 0; i < capacity; i++) {
        Node* current = nodes[i];
        while (current != NULL) {
            temp = current->next;
            delete(current);
            current = temp;
        }
    }
    delete[] nodes;

    capacity = other.capacity;
    count = other.count;

    nodes = new Node*[capacity];
    for (int i = 0; i < capacity; i++) {
        nodes[i] = NULL;
    }
    for (int i = 0; i < other.capacity; i++) {
        Node* current = other.nodes[i];
        while (current != NULL) {
            Node* new_node = new Node;
            new_node->key = current->key;
            new_node->value = current->value;
            new_node->next = nodes[i];
            nodes[i] = new_node;
            current = current->next;
        }
    }
    return *this;
}

int HashMap::hashSize() const {
    return count;
}