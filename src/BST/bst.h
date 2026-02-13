#ifndef BST_H
#define BST_H
#include <algorithm>
#include <cstddef>

template <typename T1, typename T2>
struct treeNode {
    treeNode<T1, T2> *parent;
    treeNode<T1, T2> *right;
    treeNode<T1, T2> *left;
    int color; // 0 = black, 1 = red
    T1 key;
    T2 val;

    treeNode(T1 new_key, T2 new_val) // Tree Node Constructor
    {
        parent = NULL;
        right = NULL;
        left = NULL;
        key = new_key;
        val = new_val;
        color = 1;
    }
    
    treeNode(const treeNode<T1, T2> &other) // Tree Node Copy 
    {
        color = other.color;
        key = other.key;
        val = other.val;
        parent = NULL;
        
        if (other.right != NULL) {
            right = new treeNode<T1, T2>(*other.right);
            right->parent = this;
        } else {
            right = NULL;
        }

        if (other.left != NULL) {
            left = new treeNode<T1, T2>(*other.left);
            left->parent = this;
        } else {
            left = NULL;
        }
    }

    treeNode<T1, T2> &operator=(treeNode<T1, T2> other) // Tree Node Assignment
    {
        std::swap(parent, other.parent);
        std::swap(right, other.right);
        std::swap(left, other.left);
        std::swap(color, other.color);
        std::swap(key, other.key);
        std::swap(val, other.val);
        return *this;
    }

    ~treeNode() // Tree Node Destructor
    {   
        delete right;
        delete left;
    }
};

template <typename T1, typename T2>
struct Tree {
    treeNode<T1, T2> *root;
    int size;

    Tree() // Constructor
    {
        root = NULL;
        size = 0;
    }
    
    treeNode<T1, T2> *copyTree(treeNode<T1, T2> *node) 
    {
        if (node == NULL) { return NULL; }
        
        T1 key = node->key;
        T2 val = node->val; 

        treeNode<T1, T2> *new_node = new treeNode<T1, T2>(key, val);
        new_node->color = node->color;
        
        new_node->right = copyTree(node->right);
        if (new_node->right != NULL) {
            new_node->right->parent = new_node;
        }        
        new_node->left = copyTree(node->left);
        if (new_node->left != NULL) {
            new_node->left->parent = new_node;
        }        

        return new_node;
    }

    Tree(const Tree<T1, T2> &other) // Copy 
    {
        size = other.size; 
        root = copyTree(other.root);
    }

    Tree<T1, T2> &operator=(Tree<T1, T2> other) // Assignment 
    {
        std::swap(size, other.size);
        std::swap(root, other.root);
        return *this;
    }

    ~Tree() // Destructor
    {
        delete root;
    }

    treeNode<T1, T2>* findNodeHelper(T1 key, treeNode<T1, T2> *node) 
    {
        if (node == NULL) { return NULL; }
        
        if (node->key > key) { return findNodeHelper(key, node->left); }  
        if (node->key < key) { return findNodeHelper(key, node->right); }

        return node;
    }

    treeNode<T1, T2>* findNode(T1 key) { return findNodeHelper(key, root); }

    treeNode<T1, T2>* getTreeCeil(T1 key, treeNode<T1, T2> *node) 
    {
        if (node == NULL) { return NULL; }
        
        if (node->key == key) { return node; }  
    
        if (node->key < key) { return getTreeCeil(key, node->right); }
        
        treeNode<T1, T2> *left_ceil = getTreeCeil(key, node->left);
        return (left_ceil != NULL) ? left_ceil : node;
    }

    treeNode<T1, T2>* getLowerBound(T1 key) { return getTreeCeil(key, root); }

    treeNode<T1, T2>* getUpperBound(T1 key) 
    {
        treeNode<T1, T2> *smallest = getTreeCeil(key, root);
        if (smallest != NULL && smallest->key == key) { 
            return getSuccessor(smallest); 
        }
        return smallest;
    } 

    void rotateLeft(treeNode<T1, T2> *node) 
    {
        treeNode<T1, T2> *child = node->right;
        node->right = child->left;
        
        if (node->right != NULL) {
            node->right->parent = node;
        }
        
        child->parent = node->parent;
        
        if (node->parent == NULL) {
            root = child;
        } else if (node == node->parent->left) {
            node->parent->left = child;
        } else {
            node->parent->right = child;
        }
        
        child->left = node;
        node->parent = child;
    }

    void rotateRight(treeNode<T1, T2> *node)
    {
        treeNode<T1, T2> *child = node->left;
        node->left = child->right;
        
        if (node->left != NULL) {
            node->left->parent = node;
        }

        child->parent = node->parent;
        
        if (node->parent == NULL) {
            root = child;
        } else if (node == node->parent->left) {
            node->parent->left = child;
        } else {
            node->parent->right = child;
        }
        
        child->right = node;
        node->parent = child;
    }

    void transplant(treeNode<T1, T2> *node1, treeNode<T1, T2> *node2) 
    {
        if (node1->parent == NULL) {
            root = node2;
        } else if (node1 == node1->parent->left) {
            node1->parent->left = node2;
        } else {
            node1->parent->right = node2; 
        }
        if (node2 != NULL) {
            node2->parent = node1->parent;
        }
    }

    void fixInsertNode(treeNode<T1, T2> *new_node) 
    {
        treeNode<T1, T2> *parent = NULL;
        treeNode<T1, T2> *grandparent = NULL;
        while (new_node != root && new_node->color == 1 
                && new_node->parent->color == 1) {
            parent = new_node->parent;
            grandparent = parent->parent;
            
            if (parent == grandparent->left) {
                treeNode<T1, T2> *uncle = grandparent->right;
                
                if (uncle != NULL && uncle->color == 1) {
                    grandparent->color = 1;
                    parent->color = 0;
                    uncle->color = 0;
                    new_node = grandparent;
                } else {
                    if (new_node == parent->right) {
                        rotateLeft(parent);
                        new_node = parent;
                        parent = new_node->parent;
                    }
                    
                    rotateRight(grandparent);
                    std::swap(parent->color, grandparent->color);
                    new_node = parent;
                } 
            } else {
                treeNode<T1, T2> *uncle = grandparent->left;
                
                if (uncle != NULL && uncle->color == 1) {
                    grandparent->color = 1;
                    parent->color = 0;
                    uncle->color = 0;
                    new_node = grandparent;
                } else {
                    if (new_node == parent->left) {
                        rotateRight(parent);
                        new_node = parent;
                        parent = new_node->parent;
                    }

                    rotateLeft(grandparent);
                    std::swap(parent->color, grandparent->color);
                    new_node = parent;
                }
            }
        }
        root->color = 0;
    }

    treeNode<T1, T2>* insertNode(T1 key, T2 value) 
    {
        treeNode<T1, T2> *exists = findNode(key);
        if (exists != NULL) { return exists; }

        treeNode<T1, T2> *new_node = new treeNode<T1, T2>(key, value);
        treeNode<T1, T2> *parent = NULL;
        treeNode<T1, T2> *curr = this->root;

        while (curr != NULL) {
            parent = curr;
            if (new_node->key < curr->key) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        
        new_node->parent = parent;
        if (parent == NULL) {
            root = new_node;
        } else if (new_node->key < parent->key) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }

        fixInsertNode(new_node);
        size++;
        return new_node;
    }

    void fixEraseNode(treeNode<T1, T2> *node) 
    {
        if (node == NULL) { return; }

        treeNode<T1, T2> *other_node;
        while (node != root && node->color == 0) {
            if (node == node->parent->left) {
                other_node = node->parent->right;
                
                if (other_node == NULL) { break; }
                
                if (other_node->color == 1) {
                    other_node->color = 0;
                    node->parent->color = 1;
                    rotateLeft(node->parent);
                    other_node = node->parent->right;
                }

                if (other_node == NULL) { break; }

                if (other_node->left->color == 0 
                    && other_node->right->color == 0) {
                    
                    other_node->color = 1;
                    node = node->parent;
                } else {
                    if (other_node->right->color == 0) {
                        if (other_node->left != NULL) {
                            other_node->left->color = 0;
                        }
                        other_node->color = 1;
                        rotateRight(other_node);
                        other_node = node->parent->right;
                    }
                    
                    if (other_node == NULL) { break; }

                    other_node->color = node->parent->color;
                    node->parent->color = 0;
                    if (other_node->right != NULL) {
                        other_node->right->color = 0;
                    }
                    rotateLeft(node->parent);
                    node = root;
                }
            } else {
                other_node = node->parent->left;

                if (other_node == NULL) { break; }

                if (other_node->color == 1) {
                    other_node->color = 0;
                    node->parent->color = 1;
                    rotateRight(node->parent);
                    other_node = node->parent->left;
                }

                if (other_node->right->color == 0 
                    && other_node->right->color == 0) {
                    
                    other_node->color = 1;
                    node = node->parent;
                } else {
                    if (other_node->left->color == 0) {
                        if (other_node->right != NULL) {
                            other_node->right->color = 0;
                        }
                        other_node->color = 1;
                        rotateLeft(other_node);
                        other_node = node->parent->left;
                    }

                    if (other_node == NULL) { break; }

                    other_node->color = node->parent->color;
                    node->parent->color = 0;
                    if (other_node->left != NULL) {
                        other_node->left->color = 0;
                    }
                    rotateRight(node->parent);
                    node = root;
                }
            }
        }
        if (node != NULL) {
            node->color = 0;
        }
    }

    void eraseNode(treeNode<T1, T2> *curr) 
    {
        if (curr == NULL) { return; }

        treeNode<T1, T2> *tmp1 = curr;
        treeNode<T1, T2> *tmp2 = tmp1;
        treeNode<T1, T2> *tmp3 = NULL;
        
        int tmp2_original_color = tmp2->color;

        if (tmp1->left == NULL) {
            tmp3 = tmp1->right;
            transplant(tmp1, tmp1->right);
        } else if (tmp1->right == NULL) {
            tmp3 = tmp1->left;
            transplant(tmp1, tmp1->left);
        } else {
            tmp2 = getMinimumKey(tmp1->right); 
            tmp2_original_color = tmp2->color;
            tmp3 = tmp2->right;
            
            if (tmp2->parent == tmp1) {
                if (tmp3 != NULL) {
                    tmp3->parent = tmp2;
                }
            } else {
                transplant(tmp2, tmp2->right);
                tmp2->right = tmp1->right;
                tmp2->right->parent = tmp2;
            }

            transplant(tmp1, tmp2);
            tmp2->left = tmp1->left;
            tmp2->left->parent = tmp2;
            tmp2->color = tmp1->color;
        }
        
        tmp1->parent = NULL;
        tmp1->right = NULL;
        tmp1->left = NULL;
        delete tmp1;

        if (tmp2_original_color == 0) {
            fixEraseNode(tmp3);
        }
        size--;
    }

    treeNode<T1, T2>* getMinimumKey(treeNode<T1, T2> *node)
    { 
        if (node == NULL) { return NULL; }

        treeNode<T1, T2> *curr = node;
        while (curr->left != NULL) {
            curr = curr->left;
        }
        return curr; 
    }


    treeNode<T1, T2>* getMinimumKey() { return getMinimumKey(root); }

    treeNode<T1, T2>* getMaximumKey(treeNode<T1, T2> *node) 
    { 
        if (node == NULL) { return NULL; }

        treeNode<T1, T2> *curr = node;
        while (curr->right != NULL) {
            curr = curr->right;
        }
        return curr; 
    }

    treeNode<T1, T2>* getMaximumKey() { return getMaximumKey(root); }

    treeNode<T1, T2>* getPredecessor(treeNode<T1, T2> *curr) 
    { 
        if (curr->left != NULL) {
            return getMaximumKey(curr->left);
        }

        treeNode<T1, T2> *parent = curr->parent;
        while (parent != NULL && curr == parent->left) {
            curr = parent;
            parent = parent->parent;
        }
        return parent;
    }  
    
    treeNode<T1, T2>* getSuccessor(treeNode<T1, T2> *curr) 
    {
        if (curr->right != NULL) {
            return getMinimumKey(curr->right);
        }
        treeNode<T1, T2> *parent = curr->parent;
        while (parent != NULL && curr == parent->right) {
            curr = parent;
            parent = parent->parent;
        }
        return parent;
    }
    
    int countNodes(treeNode<T1, T2> *curr) 
    {
        if (curr == NULL) { return 0; }
        return 1 + countNodes(curr->left) + countNodes(curr->right);
    }
    
    int getRank(treeNode<T1, T2> *target) 
    { 
        if (target == NULL) { return -1; }

        int rank = 0;
        treeNode<T1, T2> *curr = root;

        while (curr != NULL) {
            if (target->key < curr->key) {
                curr = curr->left;
            } 
            else if (target->key > curr->key) {
                rank += 1 + countNodes(curr->left);
                curr = curr->right;
            } 
            else {
                rank += countNodes(curr->left);
                return rank;
            }
        }
        return -1; 
    }
    

    treeNode<T1, T2>* getKthElement(int &index, treeNode<T1, T2> *curr) 
    { 
        if (curr == NULL) { return NULL; }
        
        treeNode<T1, T2> *tmp = getKthElement(index, curr->left);
        
        if (tmp != NULL) { return tmp; }

        if (index-- == 0) { return curr; }
        
        return getKthElement(index, curr->right);
    }

    treeNode<T1, T2>* getKthElement(int index) { return getKthElement(index, root); }

    int getSize() { return size; }

};

#endif