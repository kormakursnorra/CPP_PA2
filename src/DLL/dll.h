#ifndef DLL_H
#define DLL_H

template <typename T>
struct Node {
    Node *prev;
    Node *next;
    T data;
};

template <typename T> 
struct DLL {
    Node *sentinel;
    Node *curr;
    int size; 

    DLL();                                   // Constructor
    DLL(const DLL<T> &other);                // Copy 
    DLL<T> &operator=(const DLL<T> &other);  // Assign
    ~DLL();                                  // Deconstructor
    
    Node* getFirst();
    Node* getLast();
    Node* insertNode(T data);
    Node* eraseNode(T data);
    Node* getPredecessor();
    Node* getSuccessor();
    int getSize();
};

#endif