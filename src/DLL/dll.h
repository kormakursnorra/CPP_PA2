#ifndef DLL_H
#define DLL_H
#include <cstdio>

template <typename T>
struct listNode {
    listNode<T> *prev;
    listNode<T> *next;
    T data;

    // listNode(T data) // List Node Constructor 
    // {
    //     data = data;
    //     prev = NULL;
    //     next = NULL;
    // }

    // listNode(const listNode<T> &other) // List Node Copy 
    // {
    //     data = other.data;
        
    //     if (other.prev != NULL) {
    //         prev = new listNode<T>(*other.prev);
    //     } else {
    //         prev = next;
    //     }

    //     if (other.next != NULL) {
    //         next = new listNode<T>(*other.next);
    //     } else {
    //         next = prev;
    //     }
    // }

    // listNode<T> &operator=(listNode<T> other) 
    // {
    //     std::swap(data, other.data);
    //     std::swap(prev, other.prev);
    //     std::swap(next, other.next);
    //     return *this
    // }

    // ~listNode() 
    // {
    //     delete prev;
    //     delete next;
    // }
};

template <typename T> 
struct DLL {
    listNode<T> *sentinel;
    int size; 

    DLL() // Constructor
    {
        sentinel = new listNode<T>();
        sentinel->prev = sentinel;
        sentinel->next = sentinel;
        size = 0;
    }                                   
    
    DLL(const DLL<T> &other)  // Copy 
    {
        sentinel = new listNode<T>();
        sentinel->prev = sentinel;
        sentinel->next = sentinel;
        size = other.size;
        
        listNode<T> *curr = sentinel;
        
        listNode<T> *other_node = other.sentinel->next;

        while (other_node != other.sentinel) {
            listNode<T> *new_node = new listNode<T>();
            new_node->data = other_node->data;
            
            new_node->prev = curr;
            new_node->next = curr->next;
            curr->next->prev = new_node;
            curr->next = new_node;

            curr = new_node;
            other_node = other_node->next;
        }

        curr = sentinel;
    }

    DLL<T> &operator=(const DLL<T> &other)  // Assign
    {
        if (this != &other) {
            DLL<T> temp(other);
            
            listNode<T> *temp_sentinel = sentinel;
            int temp_size = size;
            
            sentinel = temp.sentinel;
            size = temp.size;
            
            temp.sentinel = temp_sentinel;
            temp.size = temp_size;
        }

        return *this;
    }

    ~DLL()  // Destructor
    {
        listNode<T> *listnode = sentinel->next;
        while (listnode != sentinel) {
            listnode = listnode->next;
            delete listnode->prev;
        }
    
        delete sentinel;
    }
    
    listNode<T>* getFirst() { return sentinel->next; }
    
    listNode<T>* getLast() { return sentinel; }

    listNode<T>* insertNode(listNode<T> *curr, T data)
    {
        listNode<T> *new_node = new listNode<T>();
        new_node->data = data;
    
        new_node->prev = curr->prev;
        new_node->next = curr;
        curr->prev->next = new_node;
        curr->prev = new_node;
    
        size++;
        return new_node;
    }

    listNode<T>* eraseNode(listNode<T> *curr)
    {
        if (size == 0) { return curr; }
        listNode<T> *listnode = curr->next;
        listnode->prev = curr->prev;
        curr->prev->next = listnode;
        size--;
        
        delete curr;
        return listnode;
    }

    listNode<T>* getPredecessor(listNode<T> *curr) { return curr->prev; }

    listNode<T>* getSuccessor(listNode<T> *curr) { return curr->next; }

    int getSize() { return size; }
};

#endif