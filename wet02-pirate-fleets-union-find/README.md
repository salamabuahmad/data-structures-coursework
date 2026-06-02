# Pirate Fleets Management System

## Overview

This project implements a C++ system for managing pirate fleets.

The system supports creating fleets, adding pirates, merging fleets, paying pirates, querying fleet size, and resolving pirate arguments based on rank.

It combines several custom data structures, including a hash table, AVL trees, dynamic arrays, and Union-Find.

## Features

- Add new fleets
- Add pirates to fleets
- Pay pirates
- Query pirate money
- Query number of ships in a fleet
- Merge fleets
- Resolve pirate arguments based on rank difference

## Data Structures Used

- Custom hash table
- AVL tree buckets inside the hash table
- Dynamic array
- Union-Find / Disjoint Set
- Smart pointers and weak pointers for object relationships

## Technologies Used

- C++
- Hash Tables
- AVL Trees
- Union-Find
- Dynamic Arrays
- Smart Pointers
- Object-Oriented Programming

## Project Files

- `DynamicArray.h` - custom dynamic array implementation
- `AVLTree.h` - generic AVL tree implementation
- `HashTable.h` - hash table implementation using AVL tree buckets
- `UnionFind.h` - disjoint-set structure for fleet merging
- `Fleet.h` / `Fleet.cpp` - fleet entity
- `Pirate.h` / `Pirate.cpp` - pirate entity
- `pirates24b2.h` / `pirates24b2.cpp` - main system API
- `wet2util.h` - status and output utility types

## What I Learned

- Implementing and combining multiple data structures
- Using Union-Find for efficient group merging
- Designing a custom hash table with tree-based buckets
- Managing relationships between objects using smart pointers
- Supporting efficient system operations under data-structure constraints
