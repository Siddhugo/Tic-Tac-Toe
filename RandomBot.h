#ifndef RANDOMBOT_H
#define RANDOMBOT_H

#include "Player.h"
#include <random>

class RandomBot : public Player {
private:
    char symbol;
    std::mt19937 rng;
public:
    RandomBot(char sym);
    std::pair<int,int> getMove(const Board& board) override;
};

#endif