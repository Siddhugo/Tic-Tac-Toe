#include "RandomBot.h"
#include "Board.h"

RandomBot::RandomBot(char sym) : symbol(sym), rng(std::random_device{}()) {}

std::pair<int,int> RandomBot::getMove(const Board& board) {
    std::vector<int> empty = board.getEmptyIndices();
    std::uniform_int_distribution<int> dist(0, empty.size() - 1);
    int idx = empty[dist(rng)];
    return {idx / 3, idx % 3};
}