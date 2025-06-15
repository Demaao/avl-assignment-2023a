# Extended AVL Tree in C
 
The assignment supports insertion, deletion, search, duplicate-free merging of two AVL trees,  
range-sum queries, lowest common ancestor (LCA), and complete tree cleanup—all while
automatically maintaining each node’s height, subtree size, and subtree sum.

## Features & Complexities

| Operation          | Time Complexity | Notes                                              |
|--------------------|-----------------|----------------------------------------------------|
| `Insert(x)`        | **O(log n)**    | No duplicate keys are inserted                     |
| `Delete(x)`        | **O(log n)**    | Frees node memory                                  |
| `Search(x)`        | **O(log n)**    | Returns a pointer to the node or `NULL`            |
| `LCA(x, y)`        | **O(log n)**    | Lowest common ancestor                             |
| `Sum(x, y)`        | **O(log n)**    | Range-sum over keys in `[x, y]`                    |
| `Merge(T₁, T₂)`    | **O(n)**        | Builds a balanced, duplicate-free tree             |
| `DeleteAll()`      | **O(n)**        | Post-order traversal frees entire tree             |

## File Overview

| File            | Purpose                                  |
|-----------------|------------------------------------------|
| `avl.c` / `avl.h` | Core AVL implementation                 |
| `main.c`        | Simple unit-test driver                  |
| `HW AVL 2023A.pdf` | Original assignment description (PDF)  |

