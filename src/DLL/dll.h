#ifndef DLL_H
#define DLL_H

template <typename T>
struct listNode {
    listNode<T> *prev;
    listNode<T> *next;
    T data;
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
        
        listNode<T> *curr = sentinel;
        size = other.size;
        
        listNode<T> *listother_node = other.sentinel->next;

        while (listother_node != other.sentinel) {
            listNode<T> *listnew_node = new listNode<T>();
            
            listnew_node->prev = curr;
            listnew_node->next = curr->next;
            curr->next->prev = listnew_node;
            curr->next = listnew_node;

            listnew_node->data = listother_node->data;
            curr = listnew_node;
            listother_node = listother_node->next;
        }

        curr = sentinel;
    }

    DLL<T> &operator=(const DLL<T> &other)  // Assign
    {
        if (this == &other) {
            return *this; 
        }
        
        listNode<T> *listnode = sentinel->next;
        while (listnode != sentinel) {
            listnode = listnode->next;
            delete listnode->prev;
        }

        delete sentinel;

        sentinel = new listNode<T>();
        sentinel->prev = sentinel;
        sentinel->next = sentinel;
        
        listNode<T> *curr = sentinel;
        size = other.size;

        listNode<T> *listother_node = other.sentinel->next;

        while (listother_node != other.sentinel) {
            listNode<T> *listnew_node = new listNode<T>();
            
            listnew_node->prev = curr;
            listnew_node->next = curr->next;
            curr->next->prev = listnew_node;
            curr->next = listnew_node;

            listnew_node->data = listother_node->data;
            curr = listnew_node;
            listother_node = listother_node->next;
        }

        curr = sentinel;
        return *this;
    }

    ~DLL()  // Deconstructor
    {
        listNode<T> *listnode = sentinel->next;
        while (listnode != sentinel) {
            listnode = listnode->next;
            delete listnode->prev;
        }
    
        delete sentinel;
    }
    
    listNode<T>* getFirst() 
    {
        if (size == 0) { 
            return sentinel;
        } 
        return sentinel->next;
    }
    
    listNode<T>* getLast()
    {
        if (size == 0) { 
            return sentinel; 
        }
        return sentinel->prev; 
    }

    listNode<T>* insertNode(listNode<T> *curr, T data)
    {
        listNode<T> *listnew_node = new listNode<T>();
        listnew_node->data = data;
    
        listnew_node->prev = curr->prev;
        listnew_node->next = curr;
        curr->prev->next = listnew_node;
        curr->prev = listnew_node;
    
        curr = listnew_node;
        size++;
        return listnew_node;
    }

    listNode<T>* eraseNode(listNode<T> *curr)
    {
        if (size == 0) { return curr; }
        listNode<T> *listnode = curr->next;
        listnode->prev = curr->prev;
        curr->prev->next = listnode;
        
        delete curr; 
        curr = listnode;
        size--;
        return listnode;
    }

    listNode<T>* getPredecessor(listNode<T> *curr)
    {
        return curr->prev;
    }

    listNode<T>* getSuccessor(listNode<T> *curr)
    {
        return curr->next;
    }

    int getSize()
    {
        return size;
    }
};

#endif