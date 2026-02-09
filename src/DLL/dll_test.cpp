#include "dll.h"
#include <cassert>
#include <cstdio>


static DLL<int> lists[1001];

static Node<int> *cursors[1001];

int main() {

    int num_lines;
    scanf("%d", &num_lines);

    for (int i = 0; i < 1000; i++) {
        cursors[i] = lists[i].getLast();
    }

    for (int i = 0; i < num_lines; i++) {
        int instance;
        char op;
        scanf("%d %c", &instance, &op);

        if (op == 'a') {
            int other;
            scanf("%d", &other);
            lists[instance] = lists[other];
            cursors[instance] = lists[instance].getLast();
        }
        else if (op == 'f') {
            cursors[instance] = lists[instance].getFirst();
        }
        else if (op == 'b') {
            cursors[instance] = lists[instance].getLast();
        }
        else if (op == 'i') {
            int value;
            scanf("%d", &value);
            cursors[instance] = lists[instance].insertNode(cursors[instance], value);
        }
        else if (op == 'e') {
            cursors[instance] = lists[instance].eraseNode(cursors[instance]);
        }
        else if (op == '>') {
            cursors[instance] = lists[instance].getSuccessor(cursors[instance]);
        }
        else if (op == '<') {
            cursors[instance] = lists[instance].getPredecessor(cursors[instance]);
        }
        else if (op == 'g') {
            printf("%d, %c", cursors[instance]->data, '\n');
        }
        else if (op == 's') {
            int value;
            scanf("%d", &value);
            cursors[instance]->data = value;
        }
        else if (op == 'z') {
            printf("%d %c", lists[instance].getSize(), '\n');
        }
        else {
            assert(false);
        }
    }
    return 0;
}