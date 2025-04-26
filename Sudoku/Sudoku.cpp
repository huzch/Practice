#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int SIZE = 9;

// 检查某个数字是否在行、列或宫格中
bool isInRow(const vector<vector<int>>& grid, int row, int num) {
    return find(grid[row].begin(), grid[row].end(), num) != grid[row].end();
}

bool isInCol(const vector<vector<int>>& grid, int col, int num) {
    for (int row = 0; row < SIZE; ++row) {
        if (grid[row][col] == num) return true;
    }
    return false;
}

bool isInBox(const vector<vector<int>>& grid, int startRow, int startCol, int num) {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (grid[startRow + row][startCol + col] == num) return true;
        }
    }
    return false;
}

// 检查是否可以在单元格中放置数字
bool isSafe(const vector<vector<int>>& grid, int row, int col, int num) {
    return !isInRow(grid, row, num) &&
           !isInCol(grid, col, num) &&
           !isInBox(grid, row - row % 3, col - col % 3, num);
}

// 回溯求解数独
bool solveSudoku(vector<vector<int>>& grid) {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            if (grid[row][col] == 0) { // 找到未填充的单元格
                for (int num = 1; num <= SIZE; ++num) {
                    if (isSafe(grid, row, col, num)) {
                        grid[row][col] = num; // 尝试填充数字
                        if (solveSudoku(grid)) {
                            return true; // 如果成功，返回 true
                        }
                        grid[row][col] = 0; // 回溯
                    }
                }
                return false; // 如果没有数字可以填充，返回 false
            }
        }
    }
    return true; // 如果所有单元格都已填充，返回 true
}

// 打印数独网格
void printGrid(const vector<vector<int>>& grid) {
    for (const auto& row : grid) {
        for (int num : row) {
            if (num == 0) {
                cout << ". ";
            } else {
                cout << num << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    vector<vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    cout << "Initial Grid:" << endl;
    printGrid(grid);

    if (solveSudoku(grid)) {
        cout << "\nSolved Grid:" << endl;
        printGrid(grid);
    } else {
        cout << "\nNo solution exists for the given Sudoku." << endl;
    }

    return 0;
}