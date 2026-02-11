#include "heap.h"
#include <cstdio>

int main() {
    int q;
    scanf("%d", &q);

    Heap heaps[1001];

    for (int i = 0; i < q; i++) {
        int id;
        char op;
        scanf("%d %c", &id, &op);

        if (op == '+') {
            int value;
            scanf("%d", &value);
            heaps[id].push(value);
        } else if (op == '-') {
            heaps[id].pop();
        } else if (op == 'p') {
            printf("%d\n", heaps[id].peek());
        } else if (op == 's') {
            printf("%d\n", heaps[id].size());
        } else if (op == 'a') {
            int sourceID;
            scanf("%d", &sourceID);
            heaps[id] = heaps[sourceID];
        }
    }

    return 0;
}