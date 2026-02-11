#include "hashmap.h"
#include <cstdio>

int main() {
    int q;
    scanf("%d", &q);

    HashMap instances[1001];

    for (int i = 0; i < q; i++) {
        int id;
        char op;
        scanf("%d %c", &id, &op);

        if (op == 'a') {
            int source;
            scanf("%d", &source);
            instances[id] = instances[source];
        } else if (op == 'i') {
            int key, value;
            scanf("%d %d", &key, &value);
            instances[id].insert(key, value);
        } else if (op == 'e') {
            int key;
            scanf("%d", &key);
            instances[id].erase(key);
        } else if (op == 'g') {
            int key;
            scanf("%d", &key);
            Node* node = instances[id].find(key);
            if (node) {
                printf("%d\n", node->value);
            } else {
                printf("-\n");
            }
        } else if (op == 's') {
            int key, value;
            scanf("%d %d", &key, &value);
            instances[id][key] = value;
        } else if (op == 'z') {
            printf("%d\n", instances[id].hashSize());
        }
    }

    return 0;
}
