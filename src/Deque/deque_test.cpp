#include "deque.h"
#include <cstdio>

int main() {
    int q;
    scanf("%d", &q);

    Deque<int> deques[1001];

    for (int i = 0; i < q; i++) {
        int id;
        char op;
        scanf("%d %c", &id, &op);

        if (op == '+') {
            char dir;
            int value;
            scanf("%c%d", &dir, &value);
            if (dir == 'f') {
                deques[id].push_front(value);
            } else {
                deques[id].push_back(value);
            }
        } else if (op == '-') {
            char dir;
            scanf("%c", &dir);
            if (dir == 'f') {
                deques[id].pop_front();
            } else {
                deques[id].pop_back();
            }
        } else if (op == 'f') {
            printf("%d\n", deques[id].front());
        } else if (op == 'b') {
            printf("%d\n", deques[id].back());
        } else if (op == 's') {
            printf("%d\n", deques[id].size());
        } else if (op == 'a') {
            int sourceID;
            scanf("%d", &sourceID);
            deques[id] = deques[sourceID];
        }
    }
    return 0;
}
