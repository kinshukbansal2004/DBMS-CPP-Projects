# B+ Trees

## Overview

This project provides a simple B+ Tree implementation in C++, supporting dynamic insertion, deletion, and traversal operations. B+ Trees are commonly used in databases and file systems because they provide efficient disk read/write operations and maintain sorted data for search optimization.

## Features

1. **Insert**: Add keys to the B+ tree while maintaining sorted order and balancing the tree when nodes overflow.
2. **Delete**: Remove keys from the B+ tree while ensuring proper rebalancing through redistribution or merging of nodes.
3. **Display**: Print the current structure of the tree in a user-friendly format to visualize keys at each level.
4. **Dynamic Split and Merge**: When the number of keys in a node exceeds its order, it is split into two nodes. When underfilled, nodes can merge or redistribute keys from sibling nodes.

## Usage

Upon running the program, you will be prompted to provide:

- **Order of an internal node**: The maximum number of keys an internal node can hold.
- **Order of a leaf node**: The maximum number of keys a leaf node can hold.

Once these parameters are provided, the program enters an interactive mode where you can insert or delete keys and display the current tree structure.

### Commands

- `+<key>`: Insert a key into the B+ Tree.
- `-<key>`: Delete a key from the B+ Tree.
- `*`: Display the current structure of the B+ Tree.
- Any other input terminates the program.

### Output Format

The tree is displayed as follows:
- **Keys in a node** are separated by `-`.
- **Nodes on the same level** are separated by `|`.
- **Different levels** are displayed on separate lines.

## Build Instructions

You can build the program using any C++ compiler. The code is written in standard C++ and relies on the `iostream`, `vector`, `algorithm`, and `queue` libraries.

## Notes

- This implementation supports inserting unique integer keys. Insertion of a duplicate key is ignored.
- Deletion redistributes keys between siblings or merges nodes when necessary, keeping the tree balanced.
- The tree dynamically adjusts its structure by promoting keys to the parent node upon node splits.
