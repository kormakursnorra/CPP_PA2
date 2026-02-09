#ifndef DLL_H
#define DLL_H

template <typename T>
struct Node {
    Node<T> *prev;
    Node<T> *next;
    T data;
};

template <typename T> 
struct DLL {
    Node<T> *sentinel;
    int size; 

    DLL() // Constructor
    {
        sentinel = new Node<T>();
        sentinel->prev = sentinel;
        sentinel->next = sentinel;
        size = 0;
    }                                   
    
    DLL(const DLL<T> &other)  // Copy 
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

    DLL<T> &operator=(const DLL<T> &other)  // Assign
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
        return *this;
    }

    ~DLL()  // Deconstructor
    {
        Node<T> *node = sentinel->next;
        while (node != sentinel) {
            node = node->next;
            delete node->prev;
        }
    
        delete sentinel;
    }
    
    Node<T>* getFirst() 
    {
        if (size == 0) { 
            return sentinel;
        } 
        return sentinel->next;
    }
    
    Node<T>* getLast()
    {
        if (size == 0) { 
            return sentinel; 
        }
        return sentinel->prev; 
    }

    Node<T>* insertNode(Node<T> *curr, T data)
    {
        Node<T> *new_node = new Node<T>();
        new_node->data = data;
    
        new_node->prev = curr->prev;
        new_node->next = curr;
        curr->prev->next = new_node;
        curr->prev = new_node;
    
        curr = new_node;
        size++;
        return new_node;
    }

    Node<T>* eraseNode(Node<T> *curr)
    {
        if (size == 0) { return curr; }
        Node<T> *node = curr->next;
        node->prev = curr->prev;
        curr->prev->next = node;
        
        delete curr; 
        curr = node;
        size--;
        return node;
    }

    Node<T>* getPredecessor(Node<T> *curr)
    {
        return curr->prev;
    }

    Node<T>* getSuccessor(Node<T> *curr)
    {
        return curr->next;
    }

    int getSize()
    {
        return size;
    }
};

#endif