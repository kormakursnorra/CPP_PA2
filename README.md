# CPP_PA2 - Data Structures

## Implemented Data Structures

### 1. Dynamically Sized Array — `src//`

### 2. Linked List — `src/DLL/`

### 3. Queue/Stack/Double Ended Queue — `src//`

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
make run-heap       # Build and run the Heap test program
make run-hashmap    # Build and run the HashMap test program
```

### Run tests with sample input

```bash
# Dynamically sized array tests:

# Linked list tests:

# Queue/Stack/Double ended queue tests:

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
