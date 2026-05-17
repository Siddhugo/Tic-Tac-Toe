#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>

class Board {
private:
    char grid[3][3];
public:
    Board();
    void reset();
    bool isCellEmpty(int row, int col) const;
    bool placeMark(int row, int col, char player);
    char getCell(int row, int col) const;
    bool isFull() const;
    bool checkWin(char player) const;
    std::vector<int> getEmptyIndices() const;
    void display() const;   // now shows numbers 1-9 on empty cells
};

#endif