You can NOT use any STL data structure, e.g. `std::vector, std::set, std::list`, etc.
You can include `<cassert>`, `<cstring>`, `<cstdio>` and use `strlen, strcat, strcpy, atoi, atof, memcpy, assert`. Perhaps there are some more you can use but you don't really need any specific helper functions that you can't just write yourselves for this project. You may ask if you want to include something else, but the answer is decently likely to be no.

Students are meant to practice using pointers and arrays directly. You are expected to use the material from the lectures to do this assignment.

**Handing in**

* Hand in a single ZIP, including:
    * All code files (.cpp and .h)
            * Header files declaring the data structures and if templated also defining them
            * Code files for each data structure if they are not templated
            * Code files for simple programs that test your data structures, one for each data structure. You are allowed to make more than one per data structure.
    * Additional files and/or scripts needed to run your code that tests each of your implemented data structures. Use a Makefile!
    * README.md (or README.txt) in which is
            * What abstract data structures you implemented and a general summary of how they are implemented. For example, specify the growth factor of your dynamically sized array, specify what kind of self-balancing binary search tree you used, mention any data structures you used to implement other data structures. Imagine that you are documenting your library enough that other programmers can use it.
            * What needs to be written in the terminal to compile and run the program. If you provide additional files for the tests, then clarify that and say how to run and verify the tests ran correctly.
            * Anything else a student wishes to say. Put it here and not in the Canvas comments!

**This assignment will focus on manual memory management.**

In C++, this mostly comes up in the implementations of data structures which we can then use to avoid manual memory management. Your task is to implement data structures generally found within standard libraries of programming languages. There are many to choose from and you are not required to implement all of them for a full grade.
Your implementations should either be specialisations for integers or for an added bonus you can template them to support all types.

You are not allowed to use built in data structures, you must manage the memory yourselves. 

You are allowed to use your previously implemented data structures for some of the other data structures. 

You should test your data structures properly and use the compiler flags, gdb and valgrind to assist you in debugging. 

You will be able to submit your data structures for testing on Kattis, which will inform you whether you get incorrect results or whether you have memory leaks.

If a program using your data structure gets incorrect results, then you should expect major deductions. 

If your data structures have worse than expected time complexities, then you should expect major deductions. 

If a program using your data structure has memory issues (leaks, accessing unowned memory, etc.) that DO result in the program crashing, you should expect major deductions.

If a program using your data structure has memory issues (leaks, accessing unowned memory, etc.) that DO NOT result in the program crashing, you should expect minor deductions.

If your data structures have correct time complexities, but do an excessive amount of unnecessary work, then you should expect minor deductions.

You should document time complexities and exceptional cases for each operation of each data structure. You can either do this in the README or by adding a comment above the function declaration!

There are 120 base points available and scoring 100 gives you a 10.

There are additionally 10 points available for templating your data structures.

1. Implement a dynamically sized array. This is the built-in list data structure in python or the vector data structure in C++. (20 points)
    * Here you can template the data type stored in the dynamically sized array.
    * You must implement the default constructor, copy constructor, push_back, pop_back, insert, erase, operator[], operator=, resize, and reserve methods.

2. Implement a linked list data structure. This is the built-in list data structure in C++. (20 points)
    * If you implement a singly linked list you get max 10 points, it is intended to be doubly linked so it can support all the operations efficiently.
    * Here you can template the data type stored in the linked list nodes.
    * You must implement the default constructor, copy constructor, assignment (operator=), front, back, insert, erase, size, successor, predecessor.

3. Implement a queue, stack, OR double-ended queue data structure. This are the built in stack, queue, deque data structures in C++. (15 points)
    * Here you can template the data type stored in data structures. 
    * If you implement either a queue, stack or both, you get max 10 points.
    * For queue and stack you must implement the default constructor, copy constructor, assignment (operator=), push, pop, size and access to the front/top element.
    * If you implement a double ended queue, you can get the full 15 points.
    * For deque you must implement the default constructor, copy constructor, assignment (operator=), push_front, push_back, pop_front, pop_back, element access at the front, element access at the back, and size.

4. Implement a heap data structure. This is the built-in priority_queue data structure in C++. (15 points)
    * Here you can template the data type stored in heap.
    * You can also use templates to support a custom comparator function that determines the * ordering of items.
    * You must implement the default constructor, copy constructor, assignment (operator=), push, pop, size, and element access to the top element. Pop should return the minimum element.

5. Implement a hash table structure with key-value pairs. This is the built-in dict in python or unordered_map data structure in C++. (20 points)
    * If your hash table does not support hash collisions in some way, or if you implement a bloom filter, then you can get a maximum of 10 points.
    * If your hash table only supports keys, but not values, then you will be deducted a few points.
    * Here you can template the key type used in the hash table.
    * You can also template the value type used in the hash table.
    * You can even template the hash function provided to allow the user of the library to specify their own hash for their key type of choice.
    * You must implement the default constructor, copy constructor, assignment (operator=), insert, find, erase, operator[], size.

6. Implement a self-balancing binary search tree structure with key-value pairs. This is the built-in map data structure in C++. (30 points)
    * If you implement a data structure that represents a binary tree, but not a binary search tree you get a maximum of 5 points.
    * If you implement a data structure that represents a binary search tree which does not self-balance then you get a maximum of 15 points.
    * If your binary search tree only supports keys, but not values, then you will be deducted a few points. 
    * Here you can template the key type used in the hash table.
    * You can also template the value type used in the hash table.
    * You can even template the comparator function provided to allow the user of the library to specify their own ordering of keys.
    * You must implement the default constructor, copy constructor, assignment (operator=), insert, find, erase, operator[], size, successor, predecessor, rank, kth_element, lower_bound, upper_bound.

**Examples:**

* **If you implement a dynamically sized array (20), linked list (20), stack (10), heap (15) and hash table (20), you get 85 points. If you further template at least one of them (5), you get 90 points. If you template all of them (10), you get 95 points.**
* **Suppose instead that you implement the dynamically sized array (20), linked list (20), deque (15) and a (non-self-balancing) binary search tree (15) then you will get 70 points total.**

**Both examples assume you do not have any errors and that you implement all functions. You will always receive some partial score if you implement some of the required functionality, but it can range from 1 point to the maximum, depending on how much is missing.**