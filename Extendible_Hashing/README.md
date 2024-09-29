# Extendible Hashing

## Overview

This C++ project implements extendible hashing, a dynamic hashing technique designed to handle growing datasets efficiently. Extendible hashing is suitable for scenarios requiring frequent insertions and deletions, as it dynamically adjusts its directory and bucket sizes.

## Features

1. **Insert:** Add keys to the hash table, with automatic bucket splitting when a bucket overflows.
2. **Delete:** Remove keys from the hash table, with automatic bucket merging when necessary.
3. **Search:** Find and retrieve keys from the hash table efficiently.
4. **Dynamic Resizing:** Adjusts the global directory and local bucket sizes based on the number of entries.
5. **Display:** Print the current state of the hash table to visualize the contents and bucket distribution.

## Usage

Upon running the program, you will be prompted to provide:

- **Maximum size of bucket:** The maximum number of keys a bucket can hold.

Once the bucket size is specified, the program enters an interactive mode where you can insert, delete, search for keys, and display the hash table structure.

## Commands

- **I:** Insert a key into the hash table. You will be prompted to enter the key.
- **D:** Delete a key from the hash table. You will be prompted to enter the key.
- **S:** Search for a key in the hash table. You will be prompted to enter the key.
- **P:** Display the current structure of the hash table.
- **E:** Exit the program.

## Output Format

- The directory and bucket contents are printed, showing the bucket index and its keys.
- The structure includes the depth of each bucket and its contents.

## Notes

- The implementation supports inserting unique integer keys. Duplicate keys are ignored.
- When deleting keys, the hash table dynamically adjusts by merging or redistributing keys between buckets.
- The hash table grows and shrinks its directory based on the global and local depths.

