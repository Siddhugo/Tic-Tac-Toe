#include "Board.h"

Board::Board() { reset(); }

void Board::reset() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            grid[i][j] = ' ';
}

bool Board::isCellEmpty(int row, int col) const {
    return grid[row][col] == ' ';
}

bool Board::placeMark(int row, int col, char player) {
    if (row < 0 || row > 2 || col < 0 || col > 2 || !isCellEmpty(row, col))
        return false;
    grid[row][col] = player;
    return true;
}

char Board::getCell(int row, int col) const {
    return grid[row][col];
}

bool Board::isFull() const {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (grid[i][j] == ' ') return false;
    return true;
}

bool Board::checkWin(char player) const {
    for (int i = 0; i < 3; ++i) {
        if ((grid[i][0] == player && grid[i][1] == player && grid[i][2] == player) ||
            (grid[0][i] == player && grid[1][i] == player && grid[2][i] == player))
            return true;
    }
    if ((grid[0][0] == player && grid[1][1] == player && grid[2][2] == player) ||
        (grid[0][2] == player && grid[1][1] == player && grid[2][0] == player))
        return true;
    return false;
}

std::vector<int> Board::getEmptyIndices() const {
    std::vector<int> empty;
    for (int i = 0; i < 9; ++i) {
        int r = i / 3, c = i % 3;
        if (grid[r][c] == ' ') empty.push_back(i);
    }
    return empty;
}

void Board::display() const {
    std::cout << "\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << "  ";
        for (int j = 0; j < 3; ++j) {
            if (grid[i][j] == ' ')
                std::cout << (i*3 + j + 1);   // show position number
            else
                std::cout << grid[i][j];
            if (j < 2) std::cout << " | ";
        }
        std::cout << "\n";
        if (i < 2) std::cout << "  --+---+--\n";
    }
    std::cout << "\n";
}