#include "dll.h"
#include <cassert>
#include <cstring>
#include <cstdio>


template <typename T> 
DLL<T>::DLL() 
{
    sentinel = new Node<T>();
    sentinel->prev = sentinel;
    sentinel->next = sentinel;
    curr = sentinel;
    size = 0;
};

template <typename T> 
DLL<T>::DLL(const DLL &other) 
{
    sentinel = new Node<T>();
    sentinel->prev = sentinel;
    sentinel->next = sentinel;
    
    curr = sentinel;
    size = other.size;
    
    Node<T> *other_node = other.sentinel->next;

    while (other_node != other.sentinel) {
        Node<T> *new_node = new Node<T>();
        
        new_node->prev = curr;
        new_node->next = curr->next;
        curr->next->prev = new_node;
        curr->next = new_node;

        new_node->data = other_node->data;
        curr = new_node;
        other_node = other_node->next;
    }

    curr = sentinel;
};  

template <typename T> 
DLL<T> &DLL<T>::operator=(const DLL<T> &other) 
{
    if (this == &other) {
        return *this; 
    }
    
    Node<T> *node = sentinel->next;
    while (node != sentinel) {
        node = node->next;
        delete node->prev;
    }

    delete sentinel;

    sentinel = new Node<T>();
    sentinel->prev = sentinel;
    sentinel->next = sentinel;
    
    curr = sentinel;
    size = other.size;

    Node<T> *other_node = other.sentinel->next;

    while (other_node != other.sentinel) {
        Node<T> *new_node = new Node<T>();
        
        new_node->prev = curr;
        new_node->next = curr->next;
        curr->next->prev = new_node;
        curr->next = new_node;

        new_node->data = other_node->data;
        curr = new_node;
        other_node = other_node->next;
    }

    curr = sentinel;
};

template <typename T> 
DLL<T>::~DLL() {
    Node<T> *node = sentinel->next;
    while (node != sentinel) {
        node = node->next;
        delete node->prev;
    }
    
    delete sentinel;
}