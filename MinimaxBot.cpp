#include "MinimaxBot.h"
#include "Board.h"
#include <algorithm>
#include <climits>

MinimaxBot::MinimaxBot(char sym, char opp) : botSymbol(sym), opponentSymbol(opp) {}

int MinimaxBot::evaluate(const Board& board) const {
    if (board.checkWin(botSymbol)) return 10;
    if (board.checkWin(opponentSymbol)) return -10;
    return 0;
}

int MinimaxBot::minimax(Board board, bool isMaximizing) const {
    int score = evaluate(board);
    if (score == 10 || score == -10) return score;
    if (board.isFull()) return 0;

    if (isMaximizing) {
        int best = INT_MIN;
        for (int idx : board.getEmptyIndices()) {
            int r = idx / 3, c = idx % 3;
            Board newBoard = board;          // copy
            newBoard.placeMark(r, c, botSymbol);
            best = std::max(best, minimax(newBoard, false));
        }
        return best;
    } else {
        int best = INT_MAX;
        for (int idx : board.getEmptyIndices()) {
            int r = idx / 3, c = idx % 3;
            Board newBoard = board;          // copy
            newBoard.placeMark(r, c, opponentSymbol);
            best = std::min(best, minimax(newBoard, true));
        }
        return best;
    }
}

std::pair<int,int> MinimaxBot::getMove(Board& board) {
    int bestScore = INT_MIN;
    std::pair<int,int> bestMove = {-1, -1};
    for (int idx : board.getEmptyIndices()) {
        int r = idx / 3, c = idx % 3;
        Board testBoard = board;             // copy current state
        testBoard.placeMark(r, c, botSymbol);
        int moveScore = minimax(testBoard, false);
        if (moveScore > bestScore) {
            bestScore = moveScore;
            bestMove = {r, c};
        }
    }
    return bestMove;
}

std::pair<int,int> MinimaxBot::getMove(const Board&) {
    return {-1, -1};
}