#ifndef PLAYER_H
#define PLAYER_H

#include <utility>

class Board;

class Player {
public:
    virtual ~Player() = default;
    virtual std::pair<int,int> getMove(const Board& board) = 0;
};

#endif