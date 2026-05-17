#include "HumanPlayer.h"
#include "Board.h"
#include <iostream>
#include <limits>

HumanPlayer::HumanPlayer(char sym) : symbol(sym) {}

std::pair<int,int> HumanPlayer::getMove(const Board& board) {
    int pos;
    while (true) {
        std::cout << "Player " << symbol << ", enter position (1-9): ";
        std::cin >> pos;
        if (std::cin.fail() || pos < 1 || pos > 9) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Use numbers 1-9.\n";
            continue;
        }
        int row = (pos - 1) / 3;
        int col = (pos - 1) % 3;
        if (!board.isCellEmpty(row, col)) {
            std::cout << "Cell occupied. Choose another.\n";
            continue;
        }
        return {row, col};
    }
}