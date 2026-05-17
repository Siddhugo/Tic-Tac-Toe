#ifndef MINIMAXBOT_H
#define MINIMAXBOT_H

#include "Player.h"

class MinimaxBot : public Player {
private:
    char botSymbol;
    char opponentSymbol;
    int evaluate(const Board& board) const;
    int minimax(Board board, bool isMaximizing) const;   // by value (copy)
public:
    MinimaxBot(char sym, char opp);
    std::pair<int,int> getMove(Board& board);            // non-const reference
    std::pair<int,int> getMove(const Board& board) override; // dummy
};

#endif