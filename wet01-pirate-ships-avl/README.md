# Pirate Ships Management System

## Overview

This project implements a C++ data management system for ships and pirates.

The system uses AVL trees to efficiently store and query ships, pirates, and ship-specific pirate data.

## Features

- Add and remove ships
- Add and remove pirates
- Move the oldest pirate from one ship to another using a treason operation
- Update pirate treasure
- Query a pirate's treasure
- Query a ship's cannon count
- Find the richest pirate on a ship
- Simulate battles between ships

## Data Structures Used

- AVL Tree for global ship storage
- AVL Tree for global pirate storage
- AVL Tree per ship for pirates by ID
- AVL Tree per ship for pirates by insertion order
- AVL Tree per ship for pirates by treasure value

## Technologies Used

- C++
- Templates
- AVL Trees
- Smart Pointers
- Object-Oriented Programming

## Project Files

- `AVLTree.h` - generic AVL tree implementation
- `Ship.h` / `Ship.cpp` - ship entity and ship-level pirate management
- `pirates.h` / `pirates.cpp` - pirate entity
- `pirates24b1.h` / `pirates24b1.cpp` - main Ocean system API
- `wet1util.h` - status and output utility types
- `main24b1.cpp` - command-based test runner

## What I Learned

- Implementing a generic self-balancing tree
- Managing multiple indexes over the same objects
- Designing efficient query/update operations
- Using smart pointers in a data-structure-heavy C++ project
- Organizing a larger C++ assignment into multiple classes
