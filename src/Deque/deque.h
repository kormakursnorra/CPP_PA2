// Using DLL implementation this group made

#ifndef DEQUE_H
#define DEQUE_H

#include "../DLL/dll.h"

template <typename T>
struct Deque {
    DLL<T> list;

    Deque() {}

    Deque(const Deque<T> &other) : list(other.list) {}

    Deque<T> &operator=(const Deque<T> &other) {
        if (this != &other) {
            list = other.list;
        }
        return *this;
    }

    ~Deque() {}


    void push_front(T data) {
        list.insertNode(list.sentinel->next, data);
    }

    void push_back(T data) {
        list.insertNode(list.sentinel, data);
    }

    void pop_front() {
        list.eraseNode(list.getFirst());
    }

    void pop_back() {
        list.eraseNode(list.getLast());
    }

    T front() {
        return list.getFirst()->data;
    }

    T back() {
        return list.getLast()->data;
    }

    int size() {
        return list.getSize();
    }
};

#endif
