# Sudoku-Solver

Project Overview
This project is a console-based Sudoku puzzle solver implemented in C++. It allows users to input their own 9x9 Sudoku grid (using 0 for empty cells), solves the puzzle using constraint propagation and backtracking, and displays the final solution in a formatted grid layout.

Features
Users can enter their own custom Sudoku puzzle via console input.
Displays both the original and solved Sudoku grid in a clear visual format.
Uses a combination of constraint propagation and backtracking algorithm to efficiently solve puzzles.
Automatically selects the cell with the fewest possibilities to optimize solving time (Minimum Remaining Value heuristic).

Concepts Used
2D Vectors and Sets
vector<vector<int>> is used to store the Sudoku grid.
vector<vector<set<int>>> holds the set of possible values for each empty cell.

Constraint Propagation
When a value is filled into a cell, the possible values for all related row, column, and box cells are updated to exclude that value.

Backtracking
The solver tries a possible value, moves forward recursively, and backtracks if it hits a dead end.

Heuristic Optimization (MRV - Minimum Remaining Value)
Always picks the cell with the least number of valid options to increase the chance of early success and reduce recursive depth.

User Input Handling
Prompts the user to input the Sudoku board row-by-row with validation for puzzle entry
