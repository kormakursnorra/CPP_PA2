#include "heap.h"
#include <cstdio>

int main() {
    int q;
    scanf("%d", &q);

    Heap* heaps[1001];
    for (int i = 0; i <= 1000; i++) {
        heaps[i] = NULL;
    }

    for (int i = 0; i < q; i++) {
        int id;
        char op;
        scanf("%d %c", &id, &op);
        
        if (heaps[id] == NULL) {
            heaps[id] = new Heap();
        }

        if (op == '+') {
            int value;
            scanf("%d", &value);
            heaps[id]->push(value);
        } else if (op == '-') {
            heaps[id]->pop();
        } else if (op == 'p') {
            printf("%d\n", heaps[id]->peek());
        } else if (op == 's') {
            printf("%d\n", heaps[id]->size());
        } else if (op == 'a') {
            int sourceID;
            scanf("%d", &sourceID);

            if (heaps[id] != NULL) {
                delete heaps[id];
            }

            heaps[id] = new Heap(*heaps[sourceID]);
        }
    }

    // Clean up all created heaps
    for (int i = 1; i <= 1000; i++) {
        if (heaps[i] != NULL) {
            delete heaps[i];
        }
    }
    return 0;
}