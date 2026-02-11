#ifndef HASHMAP_H
#define HASHMAP_H


struct Node{
    int key;
    int value;
    Node* next;
};

struct HashMap{
    private:
    Node** nodes;
    int capacity;
    int count;
    int hash(int key);

    public:
    HashMap();
    HashMap(const HashMap& other);
    HashMap& operator=(const HashMap& other);
    ~HashMap();
    void insert(int key, int value);
    void erase(int key);
    Node* find(int key);
    int& operator[](int key);
    int hashSize() const;

};

#endif