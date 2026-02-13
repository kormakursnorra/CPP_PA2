#include <cassert>
#include <iostream>
#include "array.h"

using std::cout;
using std::cin;
using std::ws;

dynamicArray<int> vecs[1000];

int main() {
    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        int instance;
        cin >> instance;
        instance--; // change to 0-based index
        // consume whitespace before reading character, otherwise we get a space
        cin >> ws;
        char op;
        cin >> op; // read operation character

        if (op == 'a') {
            int other;
            cin >> other;
            other--; // change to 0-based index
            // assignment
            vecs[instance] = vecs[other];
        }
        else if (op == '+') {
            int value;
            cin >> value;
            vecs[instance].push(value);
        }
        else if (op == '-') {
            vecs[instance].pop();
        }
        else if (op == 'i') {
            int index, value;
            cin >> index >> value;
            vecs[instance].insert(index, value);
        }
        else if (op == 'e') {
            int index;
            cin >> index;
            vecs[instance].erase(index);
        }
        else if (op == 'g') {
            int index;
            cin >> index;
            cout << vecs[instance].element_get(index) << "\n";
        }
        else if (op == 's') {
            int index, value;
            cin >> index >> value;
            vecs[instance].element_set(index, value);
        }
        else if (op == 'r') {
            int sz;
            cin >> sz;
            vecs[instance].resize(sz);
        }
        else if (op == 'p') {
            // print
            cout << vecs[instance].arr_size << "\n";
            for (int j = 0; j < vecs[instance].arr_size; j++) {
                if (j>0) cout << " ";
                cout << vecs[instance].arr[j];
            }
            if (vecs[instance].arr_size > 0) {
                cout << "\n";
            }
        }
        else {
            assert(false);
        }
    }
    return 0;
}