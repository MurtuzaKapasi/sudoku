# Sudoku Solver

## Description

This C++ console application provides a Sudoku solver and interactive game for two types of Sudoku puzzles:

1. **4x4 Grid**: Uses a 2x2 subgrid.
2. **9x9 Grid**: Uses a 3x3 subgrid.

The program reads Sudoku puzzles from CSV files, allows users to make changes interactively, and verifies the solution upon request.

## Features

- Supports 4x4 and 9x9 Sudoku puzzles.
- Reads initial puzzle data from CSV files.
- Allows interactive number entry.
- Solves the puzzle and checks the correctness of the solution.
- Displays the Sudoku grid in a user-friendly format.

## Files

- **`matrix2*2.csv`**: Contains the initial puzzle data for 4x4 Sudoku.
- **`matrix3*3.csv`**: Contains the initial puzzle data for 9x9 Sudoku.

## Compilation and Execution

1. **Compile the Code**:
   Use a C++ compiler like `g++` to compile the code.
   ```bash
   g++ -o sudoku_solver sudoku_solver.cpp
