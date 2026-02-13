# CPP_PA2 - Data Structures

## Implemented Data Structures

### 1. Dynamically Sized Array — `src//`

### 2. Linked List — `src/DLL/`

A templated doubly linked list with sentinel node implementation. The list maintains bidirectional links between nodes, allowing efficient insertion and deletion at any position.

**Implementation details:**
- Uses a circular doubly linked list structure with a sentinel node
- Sentinel node acts as both the head and tail marker:
  * `sentinel->next` points to the first real node
  * `sentinel->prev` points to the last real node
  * When empty: `sentinel->next == sentinel->prev == sentinel`
- Each node contains:
  * `data`: the stored value (templated type T)
  * `prev`: pointer to previous node
  * `next`: pointer to next node
- Circular structure simplifies edge cases (no NULL pointers to check)
- Supports insertion before any node, including the sentinel (which inserts at end)

**Operations and time complexities:**
| Operation | Method | Time Complexity | Notes |
|-----------|--------|-----------------|-------|
| Constructor | `DLL()` | O(1) | Creates empty list with sentinel node |
| Copy constructor | `DLL(const DLL&)` | O(n) | Deep copies all nodes in order |
| Assignment | `operator=` | O(n) | Uses copy-and-swap idiom for exception safety | 
| Destructor | `~DLL()` | O(n) | Deletes all nodes including sentinel |
| First | `getFirst()` | O(1) | Returns pointer to first node `(sentinel->next)` | 
| Back | `getLast()` | O(1) | Returns pointer to sentinel (insertion point for append) |
| Insert | `insertNode(node*, data)` | O(1) | Inserts new node before given node |
| Erase | `eraseNode(node*)` | O(1) | Removes given node, returns next node | 
| Predecessor | `getPredecessor(node*)` | O(1) | Returns previous node in list
| Successor | `getSuccessor(node*)` | O(1) | Returns next node in list | 
| Size | `getSize()` | O(1) | Returns number of nodes (excluding sentinel) |

---

### 3. Double Ended Queue (Deque) — `src/Deque/`

A double-ended queue implemented using the doubly linked list (DLL) from `src/DLL/`. The deque is a thin wrapper around the DLL, delegating all operations to it.

**Implementation details:**
- Backed by a templated doubly linked list with a sentinel node.
- All push/pop operations work by inserting or erasing nodes at the head or tail of the DLL, which are O(1) thanks to the sentinel.
- Copy construction and assignment delegate to the DLL's copy constructor and assignment operator, which perform deep copies.

**Operations and time complexities:**
| Operation | Method | Time Complexity | Notes |
|-----------|--------|-----------------|-------|
| Constructor | `Deque()` | O(1) | Creates an empty DLL with sentinel |
| Copy constructor | `Deque(const Deque&)` | O(n) | Deep copies via DLL copy constructor |
| Assignment | `operator=` | O(n) | Frees old data, deep copies via DLL |
| Destructor | `~Deque()` | O(n) | DLL destructor frees all nodes |
| Push front | `push_front(T)` | O(1) | Inserts node after sentinel |
| Push back | `push_back(T)` | O(1) | Inserts node before sentinel |
| Pop front | `pop_front()` | O(1) | Erases first node |
| Pop back | `pop_back()` | O(1) | Erases last node |
| Front | `front()` | O(1) | Returns data of first node |
| Back | `back()` | O(1) | Returns data of last node |
| Size | `size()` | O(1) | Returns stored size counter |

**Exceptional cases:**
- `pop_front()` / `pop_back()` on an empty deque: no-op (DLL `eraseNode` returns early if size is 0).
- `front()` / `back()` on an empty deque returns the sentinel's uninitialized data (undefined behavior — callers should check size first).

---

### 4. Heap (Min-Heap) — `src/Heap/`

A min-heap implemented using a dynamically sized array. The smallest element is always at the top.

**Implementation details:**
- Backed by a dynamically allocated integer array, starting with capacity 4.
- Growth factor of 2x — when the array is full, capacity is doubled.
- Uses `bubbleUp` and `bubbleDown` to maintain the heap property after insertions and removals.
- Parent of index `i` is at `(i - 1) / 2`. Children of index `i` are at `2*i + 1` (left) and `2*i + 2` (right).

**Operations and time complexities:**
| Operation | Method | Time Complexity | Notes |
|-----------|--------|-----------------|-------|
| Constructor | `Heap()` | O(1) | Allocates initial array of capacity 4 |
| Copy constructor | `Heap(const Heap&)` | O(n) | Deep copies the backing array |
| Assignment | `operator=` | O(n) | Frees old data, deep copies |
| Destructor | `~Heap()` | O(1) | Frees the backing array |
| Push | `push(int)` | O(log n) amortized | Inserts element and bubbles up. O(n) on resize |
| Pop | `pop()` | O(log n) | Removes minimum element, bubbles down |
| Peek | `peek()` | O(1) | Returns minimum element |
| Size | `size()` | O(1) | Returns number of elements |

**Exceptional cases:**
- `pop()` on an empty heap triggers an assertion failure.
- `peek()` on an empty heap triggers an assertion failure.

---

### 5. HashMap (Hash Table) — `src/HashMap/`

A hash table mapping integer keys to integer values, using separate chaining (linked lists) for collision resolution.

**Implementation details:**
- Backed by a dynamically allocated array of `Node*` pointers (bucket array), starting with capacity 4.
- Growth factor of 2x — when the number of entries reaches the capacity (load factor >= 1.0), the table is resized and all entries are rehashed.
- Hash function: `key mod capacity` (with correct handling of negative keys).
- Collisions are handled via chaining — each bucket is a singly linked list of `Node` structs containing `key`, `value`, and `next` pointer.

**Operations and time complexities:**
| Operation | Method | Time Complexity | Notes |
|-----------|--------|-----------------|-------|
| Constructor | `HashMap()` | O(1) | Allocates initial bucket array of capacity 4 |
| Copy constructor | `HashMap(const HashMap&)` | O(n + m) | Deep copies all nodes across all buckets (n = entries, m = capacity) |
| Assignment | `operator=` | O(n + m) | Frees old data, deep copies |
| Destructor | `~HashMap()` | O(n + m) | Frees all nodes and bucket array |
| Insert | `insert(int, int)` | O(1) amortized | Inserts key-value pair. Does nothing if key already exists. O(n) on resize |
| Find | `find(int)` | O(1) average | Returns pointer to node with matching key, or NULL if not found |
| Erase | `erase(int)` | O(1) average | Removes node with matching key. Does nothing if key not found |
| operator[] | `operator[](int)` | O(1) average | Returns reference to value for given key. Key must exist |
| Size | `hashSize()` | O(1) | Returns number of key-value pairs |

**Exceptional cases:**
- `operator[]` assumes the key exists. Calling it with a non-existent key is undefined behavior.
- `insert()` does not update the value if the key already exists. Use `operator[]` to update values.
- 
### 4. Self Balancing BST — `src/BST/`

A self-balancing binary search tree implemented as a Red-Black tree that stores integer key-value pairs. The tree maintains balanced height through rotations and color properties, ensuring logarithmic time complexity for all operations.

**Implementation details:**
- Each node contains a key, value, parent pointer, left and right child pointers, and a color (red=1, black=0).
- Red-Black tree properties maintained:
1. Every node is either red or black
2. Root is always black
3. All NULL leaves are considered black
4. Red nodes cannot have red children (no two consecutive red nodes on any path)
5. Every path from root to NULL has the same number of black nodes
- Uses `rotateLeft` and rotateRight for structural rebalancing
- Uses `fixInsertNode` and fixEraseNode to restore Red-Black properties after modifications
- Parent pointers enable efficient predecessor/successor operations without recursion
- Supports cursor-based iteration (cursor is maintained externally, not as tree member)

**Operations and time complexities:**
| Operation | Method | Time Complexity | Notes |
|-----------|--------|-----------------|-------|
| Constructor | `Tree()` | O(1) | Initializes empty tree with root = NULL |
| Copy constructor | `Tree(const Tree&)` | O(n) | Deep copies entire tree structure with parent pointers |
| Assignment | `operator=` | O(n) | Uses copy-and-swap idiom |
| Destructor | `~Tree()` | O(n) | Recursively deletes all nodes (children only, not parents) |
| Find | `findNdde(key)` | O(log n) | Returns pointer to node with given key, or NULL |
| Insert | `insertNode(key, value)` | O(log n) | Inserts new node, rebalances tree. Returns existing node if key exists |
| Erase | `eraseNode(node*)` | O(log n) | Removes given node, rebalances tree |
| Lower Bound | `getLowerBound(key)` | O(log n) | Returns node with smallest key >= given key |
| Upper Bound | `getUpperBound(key)` | O(log n) | Returns node with smallest key > given key |
| Front | `getMinimumKey()` | O(log n) | Returns node with smallest key in tree |
| Back | `getMaximumKey()` | O(log n) | Returns node with largest key in tree |
| Successor | `getSuccessor(node*)` | O(log n) | Returns next node in sorted order |
| Predessor | `getPredecessor(node*)` | O(log n) | Returns previous node in sorted order |
| Rank | `getRank(node*)` | O(n) | Returns number of nodes with smaller keys than given node |
| Kth | `getKthElement(k)` | O(n) |Returns node with kth smallest key (0-indexed) |
| Size | `getSize()` | O(1) | Returns number of nodes in tree |

**Node operations:**

Access value: `node->val` (read/write)
Access key: `node->key` (read-only in practice)

**Exceptional cases:**
`insertNode(key, value)` does not update the value if the key already exists; it returns the existing node instead
`eraseNode(NULL)` does nothing (safe to call)
`getSuccessor(NULL)` returns NULL (safe to call)
`getPredecessor(NULL)` returns NULL (safe to call)
`getRank(NULL)` returns -1
Operations on empty tree: `getMinimumKey()` and `getMaximumKey()` return NULL

---

## Compiling and Running

### Prerequisites
- `g++` compiler with C++98 support
- `make`

### Build all targets
```bash
make all
```

### Build individual targets
```bash
make run-deque      # Build and run the Deque test program
make run-heap       # Build and run the Heap test program
make run-hashmap    # Build and run the HashMap test program
```

### Run tests with sample input

```bash
# Dynamically sized array tests:

# Linked list tests:

# Deque tests:
./bin/deque_test < src/Deque/sample1.txt
./bin/deque_test < src/Deque/sample2.txt

# Heap tests:
./bin/heap_test < src/Heap/sample1.txt
./bin/heap_test < src/Heap/sample2.txt
./bin/heap_test < src/Heap/sample3.txt

# HashMap tests:
./bin/hashmap_test < src/HashMap/sample1.txt
./bin/hashmap_test < src/HashMap/sample2.txt

# BST tests:
```

To verify correctness, compare output against expected output files:
```bash
# Deque
./bin/deque_test < src/Deque/sample1.txt | diff - src/Deque/expected1.txt
./bin/deque_test < src/Deque/sample2.txt | diff - src/Deque/expected2.txt

# Heap
./bin/heap_test < src/Heap/sample1.txt | diff - src/Heap/expected1.txt
./bin/heap_test < src/Heap/sample2.txt | diff - src/Heap/expected2.txt
./bin/heap_test < src/Heap/sample3.txt | diff - src/Heap/expected3.txt

# HashMap
./bin/hashmap_test < src/HashMap/sample1.txt | diff - src/HashMap/expected1.txt
./bin/hashmap_test < src/HashMap/sample2.txt | diff - src/HashMap/expected2.txt
```

If `diff` produces no output, the tests passed.

### Clean build artifacts
```bash
make clean
```
