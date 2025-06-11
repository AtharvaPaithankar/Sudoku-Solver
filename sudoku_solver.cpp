#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class SudokuSolver {
private:
    vector<vector<int>> board;
    vector<vector<set<int>>> possibleValues;

public:
    SudokuSolver(vector<vector<int>> inputBoard) : board(inputBoard) {
        possibleValues.resize(9, vector<set<int>>(9));
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == 0) {
                    for (int num = 1; num <= 9; ++num) {
                        possibleValues[i][j].insert(num);
                    }
                }
            }
        }
        initializePossibleValues();
    }

    void initializePossibleValues() {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] != 0) {
                    propagateConstraints(i, j, board[i][j]);
                }
            }
        }
    }

    void propagateConstraints(int row, int col, int num) {
        for (int x = 0; x < 9; ++x) {
            if (board[row][x] == 0) {
                possibleValues[row][x].erase(num);
            }
            if (board[x][col] == 0) {
                possibleValues[x][col].erase(num);
            }
        }

        int boxRow = (row / 3) * 3;
        int boxCol = (col / 3) * 3;
        for (int i = boxRow; i < boxRow + 3; ++i) {
            for (int j = boxCol; j < boxCol + 3; ++j) {
                if (board[i][j] == 0) {
                    possibleValues[i][j].erase(num);
                }
            }
        }
    }

    pair<int, int> findNextCell() {
        int minOptions = 10;
        pair<int, int> target = {-1, -1};
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == 0 && possibleValues[i][j].size() > 0) {
                    if (possibleValues[i][j].size() < minOptions) {
                        minOptions = possibleValues[i][j].size();
                        target = {i, j};
                        if (minOptions == 1) {
                            return target;
                        }
                    }
                }
            }
        }
        return target;
    }

    bool solve() {
        auto [row, col] = findNextCell();
        if (row == -1) {
            return true;
        }

        auto originalPossible = possibleValues;
        auto originalBoard = board;

        for (int num : possibleValues[row][col]) {
            board[row][col] = num;
            possibleValues[row][col].clear();
            propagateConstraints(row, col, num);

            if (solve()) {
                return true;
            }

            board = originalBoard;
            possibleValues = originalPossible;
        }

        return false;
    }

    void printBoard() {
        cout << "Sudoku Solution:" << endl;
        for (int i = 0; i < 9; ++i) {
            if (i % 3 == 0 && i != 0) {
                cout << "------+-------+------" << endl;
            }
            for (int j = 0; j < 9; ++j) {
                if (j % 3 == 0 && j != 0) {
                    cout << "| ";
                }
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    vector<vector<int>> puzzle(9, vector<int>(9));
    
    cout << "Enter your Sudoku puzzle (use 0 for empty cells):" << endl;
    for (int i = 0; i < 9; ++i) {
        cout << "Enter 9 numbers for row " << i + 1 << ": ";
        for (int j = 0; j < 9; ++j) {
            cin >> puzzle[i][j];
        }
    }

    SudokuSolver solver(puzzle);

    cout << "\nOriginal Puzzle:" << endl;
    solver.printBoard();

    if (solver.solve()) {
        cout << "\nSolved successfully!" << endl;
        solver.printBoard();
    } else {
        cout << "\nNo solution exists for this puzzle." << endl;
    }

    return 0;
}

