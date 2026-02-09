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
    size = 0;
}

template <typename T> 
DLL<T>::DLL(const DLL &other) 
{
    sentinel = new Node<T>();
    sentinel->prev = sentinel;
    sentinel->next = sentinel;
    
    Node<T> *curr = sentinel;
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
}  

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
    
    Node<T> *curr = sentinel;
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
}

template <typename T> 
DLL<T>::~DLL() 
{
    Node<T> *node = sentinel->next;
    while (node != sentinel) {
        node = node->next;
        delete node->prev;
    }
    
    delete sentinel;
}

template <typename T>
Node<T>* DLL<T>::getFirst() 
{
    if (size == 0) { return sentinel; }
    return sentinel->next;
}

template <typename T>
Node<T>* DLL<T>::getLast() 
{
    if (size == 0) { return sentinel; }
    return sentinel; 
}

template <typename T>
Node<T>* DLL<T>::insertNode(Node<T> *curr, T data) 
{
    Node<T> *new_node = new Node<T>();
    new_node->data = data;
    
    new_node->prev = curr->prev;
    new_node->next = curr;
    curr->prev->next = new_node;
    curr->prev = new_node;
    
    curr = new_node;
    return new_node;
}

template <typename T>
Node<T>* DLL<T>::eraseNode(Node<T> *curr) 
{
    if (size == 0) { return curr; }
    Node<T> *node = curr->next;
    node->prev = curr->prev;
    curr->prev->next = node;
    
    delete curr; 
    curr = node;
    return node;
}

template <typename T>
Node<T>* DLL<T>::getPredecessor(Node<T> *curr) 
{
    return curr->prev;
}

template <typename T>
Node<T>* DLL<T>::getSuccessor(Node<T> *curr) 
{
    return curr->next;
}

template <typename T>
int DLL<T>::getSize() 
{
    return size;
}