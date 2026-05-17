#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Board.h"
#include <memory>

class Player; // forward declaration

class GameManager {
private:
    Board board;
    std::unique_ptr<Player> playerX;
    std::unique_ptr<Player> playerO;
    int scoreX, scoreO, scoreDraw;
    bool vsBot;
    int botDifficulty;

public:
    GameManager();
    ~GameManager();    // destructor declared
    void showMainMenu();
private:
    void setupBotGame();
    void startGame(bool botStarts = false);
    void startFriendGame();
    void showScores();
    void resetScores();
};

#endif