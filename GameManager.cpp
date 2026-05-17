#include "GameManager.h"
#include "Board.h"
#include "HumanPlayer.h"
#include "RandomBot.h"
#include "MinimaxBot.h"
#include "Player.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <thread>
#include <chrono>

void waitForEnter() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Press Enter to continue...";
    std::cin.get();
}

GameManager::GameManager() : scoreX(0), scoreO(0), scoreDraw(0) {}

GameManager::~GameManager() = default;

void GameManager::showMainMenu() {
    int choice;
    do {
        std::cout << "========== TIC-TAC-TOE (Professional Edition) ==========\n";
        std::cout << "1. Play with Friend\n";
        std::cout << "2. Play with Bot\n";
        std::cout << "3. Show Scores\n";
        std::cout << "4. Reset Scores\n";
        std::cout << "5. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input.\n";
            waitForEnter();
            continue;
        }

        switch(choice) {
            case 1: 
                startFriendGame(); 
                break;   // game already waits for Enter internally
            case 2: 
                setupBotGame(); 
                break;   // game already waits for Enter internally
            case 3: 
                showScores(); 
                waitForEnter();   // wait so user can read scores
                break;
            case 4: 
                resetScores(); 
                waitForEnter();   // wait so user sees confirmation
                break;
            case 5: 
                std::cout << "Goodbye!\n"; 
                break;
            default: 
                std::cout << "Invalid choice.\n";
                waitForEnter();
        }
    } while(choice != 5);
}

void GameManager::setupBotGame() {
    int diff;
    std::cout << "Bot Difficulty:\n1. Easy (Random)\n2. Hard (Unbeatable)\n";
    std::cin >> diff;
    botDifficulty = (diff == 2) ? 1 : 0;

    int first;
    std::cout << "Who starts first?\n1. You (X)\n2. Bot (O)\n";
    std::cin >> first;
    bool botFirst = (first == 2);

    vsBot = true;
    startGame(botFirst);
}

void GameManager::startGame(bool botStarts) {
    board.reset();
    char turn = botStarts ? 'O' : 'X';

    if (vsBot) {
        playerX = std::make_unique<HumanPlayer>('X');
        if (botDifficulty == 0)
            playerO = std::make_unique<RandomBot>('O');
        else
            playerO = std::make_unique<MinimaxBot>('O', 'X');
    } else {
        playerX = std::make_unique<HumanPlayer>('X');
        playerO = std::make_unique<HumanPlayer>('O');
    }

    board.display();

    while (true) {
        std::pair<int,int> move;

        if (turn == 'X') {
            move = playerX->getMove(board);
            board.placeMark(move.first, move.second, 'X');
            board.display();
            if (board.checkWin('X')) {
                std::cout << "Player X wins!\n";
                scoreX++;
                break;
            }
            turn = 'O';
        } else {
            if (vsBot) {
                if (dynamic_cast<MinimaxBot*>(playerO.get())) {
                    auto& bot = dynamic_cast<MinimaxBot&>(*playerO);
                    move = bot.getMove(board);
                } else {
                    move = playerO->getMove(board);
                }
                std::cout << "Bot chooses: " << (move.first*3 + move.second + 1) << "\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            } else {
                move = playerO->getMove(board);
            }
            board.placeMark(move.first, move.second, 'O');
            board.display();
            if (board.checkWin('O')) {
                if (vsBot) std::cout << "Bot wins!\n";
                else std::cout << "Player O wins!\n";
                scoreO++;
                break;
            }
            turn = 'X';
        }

        if (board.isFull()) {
            board.display();
            std::cout << "It's a draw!\n";
            scoreDraw++;
            break;
        }
    }

    std::cout << "\nScores: X: " << scoreX << " | O: " << scoreO << " | Draws: " << scoreDraw << "\n";
    waitForEnter();   // only ONE wait after game ends
}

void GameManager::startFriendGame() {
    vsBot = false;
    startGame(false);
}

void GameManager::showScores() {
    std::cout << "===== SCORES =====\n";
    std::cout << "Player X wins: " << scoreX << "\n";
    std::cout << "Player O wins: " << scoreO << "\n";
    std::cout << "Draws: " << scoreDraw << "\n";
}

void GameManager::resetScores() {
    scoreX = scoreO = scoreDraw = 0;
    std::cout << "Scores reset.\n";
}