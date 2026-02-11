#ifndef BST_H
#define BST_H

template <typename T>
struct treeNode {
    treeNode *right;
    treeNode *left;
    T key;
    T val;
} 

#endif