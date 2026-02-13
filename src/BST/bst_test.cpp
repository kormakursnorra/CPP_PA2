#include "bst.h"
#include <cassert>
#include <cstdio>

#define SIZE 100

static Tree<int, int> trees[SIZE];
static treeNode<int, int>* cursors[SIZE];

int main() {
    int num_lines;
    scanf("%d", &num_lines);

    for (int i = 0; i < SIZE; i++) {
        cursors[i] = NULL; // or other sentinel value
    }

    for (int i = 0; i < num_lines; i++) {
        int instance;
        char op;
        scanf("%d %c", &instance, &op);

        if (op == 'a') {
            int other;
            scanf("%d", &other);
            trees[instance] = trees[other];
            cursors[instance] = NULL; // or other sentinel value
        }
        else if (op == '?') {
            int key;
            scanf("%d", &key);
            cursors[instance] = trees[instance].findNode(key);
        }
        else if (op == 'l') {
            int key;
            scanf("%d", &key);
            cursors[instance] = trees[instance].getLowerBound(key);
        }
        else if (op == 'u') {
            int key;
            scanf("%d", &key);
            cursors[instance] = trees[instance].getUpperBound(key);
        }
        else if (op == 'i') {
            int key, value;
            scanf("%d %d", &key, &value);
            cursors[instance] = trees[instance].insertNode(key, value);
        }
        else if (op == 'e') {
            trees[instance].eraseNode(cursors[instance]);
            cursors[instance] = NULL; // or other sentinel value
        }
        else if (op == 'f') {
            cursors[instance] = trees[instance].getMinimumKey();
        }
        else if (op == 'b') {
            cursors[instance] = trees[instance].getMaximumKey();
        }
        else if (op == '>') {
            cursors[instance] = trees[instance].getSuccessor(cursors[instance]);
        }
        else if (op == '<') {
            cursors[instance] = trees[instance].getPredecessor(cursors[instance]);
        }
        else if (op == 'r') {
            // or other sentinel value
            if (cursors[instance] == NULL) {
                printf("%s", "-\n");
            }
            else {
                printf("%d\n", trees[instance].getRank(cursors[instance]));
            }
        }
        else if (op == 'k') {
            int k;
            scanf("%d", &k);
            cursors[instance] = trees[instance].getKthElement(k);
        }
        else if (op == 'g') {
            // or other sentinel value
            if (cursors[instance] == NULL) {
                printf("%s", "-\n");
            }
            else {
                printf("%d\n", cursors[instance]->val);
            }
        }
        else if (op == 's') {
            int value;
            scanf("%d", &value);
            // or other sentinel value
            if (cursors[instance] != NULL) {
                cursors[instance]->val = value;
            }
        }
        else if (op == 'z') {
            printf("%d\n", trees[instance].getSize());
        }
        else {
            assert(false);
        }
    }
}