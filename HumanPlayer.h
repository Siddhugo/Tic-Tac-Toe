#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"

class HumanPlayer : public Player {
private:
    char symbol;
public:
    HumanPlayer(char sym);
    std::pair<int,int> getMove(const Board& board) override;
};

#endif