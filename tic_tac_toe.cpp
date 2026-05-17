// tic_tac_toe.cpp
// Professional Tic-Tac-Toe with AI (Minimax) and Score Tracking
// Compile: g++ -std=c++17 tic_tac_toe.cpp -o tictactoe

#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <algorithm>
#include <memory>
#include <cstdlib>   // for system("clear") or "cls"

using namespace std;

// -------------------------------------------------------------
// Utility: clear terminal (cross-platform)
// -------------------------------------------------------------
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// -------------------------------------------------------------
// Board class: manages the 3x3 grid
// -------------------------------------------------------------
class Board {
private:
    char grid[3][3];

public:
    Board() {
        reset();
    }

    void reset() {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                grid[i][j] = ' ';
    }

    bool isCellEmpty(int row, int col) const {
        return grid[row][col] == ' ';
    }

    bool placeMark(int row, int col, char player) {
        if (row < 0 || row > 2 || col < 0 || col > 2 || !isCellEmpty(row, col))
            return false;
        grid[row][col] = player;
        return true;
    }

    char getCell(int row, int col) const {
        return grid[row][col];
    }

    bool isFull() const {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (grid[i][j] == ' ') return false;
        return true;
    }

    bool checkWin(char player) const {
        // rows & columns
        for (int i = 0; i < 3; ++i) {
            if ((grid[i][0] == player && grid[i][1] == player && grid[i][2] == player) ||
                (grid[0][i] == player && grid[1][i] == player && grid[2][i] == player))
                return true;
        }
        // diagonals
        if ((grid[0][0] == player && grid[1][1] == player && grid[2][2] == player) ||
            (grid[0][2] == player && grid[1][1] == player && grid[2][0] == player))
            return true;
        return false;
    }

    // Get all empty cell indices (0..8)
    vector<int> getEmptyIndices() const {
        vector<int> empty;
        for (int i = 0; i < 9; ++i) {
            int r = i / 3, c = i % 3;
            if (grid[r][c] == ' ') empty.push_back(i);
        }
        return empty;
    }

    void display() const {
        cout << "\n";
        for (int i = 0; i < 3; ++i) {
            cout << "  ";
            for (int j = 0; j < 3; ++j) {
                cout << grid[i][j];
                if (j < 2) cout << " | ";
            }
            cout << "\n";
            if (i < 2) cout << "  ---+---+---\n";
        }
        cout << "\n";
    }
};

// -------------------------------------------------------------
// Abstract Player class
// -------------------------------------------------------------
class Player {
public:
    virtual ~Player() = default;
    virtual pair<int,int> getMove(const Board& board) = 0;
};

// -------------------------------------------------------------
// HumanPlayer: reads input from console
// -------------------------------------------------------------
class HumanPlayer : public Player {
private:
    char symbol; // 'X' or 'O'
public:
    HumanPlayer(char sym) : symbol(sym) {}

    pair<int,int> getMove(const Board& board) override {
        int pos;
        while (true) {
            cout << "Player " << symbol << ", enter position (1-9): ";
            cin >> pos;
            if (cin.fail() || pos < 1 || pos > 9) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Use numbers 1-9.\n";
                continue;
            }
            int row = (pos - 1) / 3;
            int col = (pos - 1) % 3;
            if (!board.isCellEmpty(row, col)) {
                cout << "Cell occupied. Choose another.\n";
                continue;
            }
            return {row, col};
        }
    }
};

// -------------------------------------------------------------
// RandomBot: picks a random empty cell (easy difficulty)
// -------------------------------------------------------------
class RandomBot : public Player {
private:
    char symbol;
    mt19937 rng;
public:
    RandomBot(char sym) : symbol(sym), rng(random_device{}()) {}

    pair<int,int> getMove(const Board& board) override {
        vector<int> empty = board.getEmptyIndices();
        uniform_int_distribution<int> dist(0, empty.size() - 1);
        int idx = empty[dist(rng)];
        return {idx / 3, idx % 3};
    }
};

// -------------------------------------------------------------
// MinimaxBot: unbeatable AI using minimax algorithm
// -------------------------------------------------------------
class MinimaxBot : public Player {
private:
    char botSymbol;    // 'O' typically
    char opponentSymbol;

    // Evaluate score from bot's perspective
    int evaluate(const Board& board) const {
        if (board.checkWin(botSymbol)) return 10;
        if (board.checkWin(opponentSymbol)) return -10;
        return 0;
    }

    // Minimax recursion
    int minimax(Board& board, bool isMaximizing) const {
        int score = evaluate(board);
        if (score == 10 || score == -10) return score;
        if (board.isFull()) return 0;

        if (isMaximizing) {
            int best = -1000;
            for (int idx : board.getEmptyIndices()) {
                int r = idx / 3, c = idx % 3;
                board.placeMark(r, c, botSymbol);
                best = max(best, minimax(board, false));
                board.placeMark(r, c, ' '); // undo
            }
            return best;
        } else {
            int best = 1000;
            for (int idx : board.getEmptyIndices()) {
                int r = idx / 3, c = idx % 3;
                board.placeMark(r, c, opponentSymbol);
                best = min(best, minimax(board, true));
                board.placeMark(r, c, ' ');
            }
            return best;
        }
    }

public:
    MinimaxBot(char sym, char opp) : botSymbol(sym), opponentSymbol(opp) {}

    pair<int,int> getMove(Board& board) { // non-const because minimax modifies temporarily
        int bestScore = -1000;
        pair<int,int> bestMove = {-1, -1};
        for (int idx : board.getEmptyIndices()) {
            int r = idx / 3, c = idx % 3;
            board.placeMark(r, c, botSymbol);
            int moveScore = minimax(board, false);
            board.placeMark(r, c, ' ');
            if (moveScore > bestScore) {
                bestScore = moveScore;
                bestMove = {r, c};
            }
        }
        return bestMove;
    }

    // Override getMove with const Board&? Need to work around const.
    // We'll keep this version; we'll call it separately.
    pair<int,int> getMove(const Board&) override {
        // Not used; we call the non-const version.
        return {-1,-1};
    }
};

// -------------------------------------------------------------
// GameManager: orchestrates the match, tracks scores
// -------------------------------------------------------------
class GameManager {
private:
    Board board;
    unique_ptr<Player> playerX;
    unique_ptr<Player> playerO;
    int scoreX, scoreO, scoreDraw;
    bool vsBot;
    int botDifficulty; // 0 = random, 1 = minimax

public:
    GameManager() : scoreX(0), scoreO(0), scoreDraw(0) {}

    void showMainMenu() {
        int choice;
        do {
            clearScreen();
            cout << "========== TIC-TAC-TOE (Professional Edition) ==========\n";
            cout << "1. Play with Friend\n";
            cout << "2. Play with Bot\n";
            cout << "3. Show Scores\n";
            cout << "4. Reset Scores\n";
            cout << "5. Exit\n";
            cout << "Choice: ";
            cin >> choice;

            switch(choice) {
                case 1: startFriendGame(); break;
                case 2: setupBotGame(); break;
                case 3: showScores(); break;
                case 4: resetScores(); break;
                case 5: cout << "Goodbye!\n"; break;
                default: cout << "Invalid choice.\n";
            }
            if (choice != 5) {
                cout << "\nPress Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
            }
        } while(choice != 5);
    }

private:
    void setupBotGame() {
        int diff;
        cout << "Bot Difficulty:\n1. Easy (Random)\n2. Hard (Unbeatable)\n";
        cin >> diff;
        botDifficulty = (diff == 2) ? 1 : 0;

        int first;
        cout << "Who starts first?\n1. You (X)\n2. Bot (O)\n";
        cin >> first;
        bool botFirst = (first == 2);

        vsBot = true;
        startGame(botFirst);
    }

    void startGame(bool botStarts = false) {
        board.reset();
        char turn = botStarts ? 'O' : 'X';

        // Assign players based on mode
        if (vsBot) {
            playerX = make_unique<HumanPlayer>('X');
            if (botDifficulty == 0)
                playerO = make_unique<RandomBot>('O');
            else
                playerO = make_unique<MinimaxBot>('O', 'X');
        } else {
            playerX = make_unique<HumanPlayer>('X');
            playerO = make_unique<HumanPlayer>('O');
        }

        // Game loop
        while (true) {
            clearScreen();
            board.display();

            pair<int,int> move;
            if (turn == 'X') {
                move = playerX->getMove(board);
                board.placeMark(move.first, move.second, 'X');
                if (board.checkWin('X')) {
                    clearScreen();
                    board.display();
                    cout << "Player X wins!\n";
                    scoreX++;
                    break;
                }
                turn = 'O';
            } else {
                if (vsBot && dynamic_cast<MinimaxBot*>(playerO.get())) {
                    // Call minimax version with non-const board
                    auto& bot = dynamic_cast<MinimaxBot&>(*playerO);
                    move = bot.getMove(board);
                    cout << "Bot chooses: " << (move.first*3 + move.second + 1) << "\n";
                } else {
                    move = playerO->getMove(board);
                }
                board.placeMark(move.first, move.second, 'O');
                if (board.checkWin('O')) {
                    clearScreen();
                    board.display();
                    if (vsBot) cout << "Bot wins!\n";
                    else cout << "Player O wins!\n";
                    scoreO++;
                    break;
                }
                turn = 'X';
            }

            if (board.isFull()) {
                clearScreen();
                board.display();
                cout << "It's a draw!\n";
                scoreDraw++;
                break;
            }
        }
        cout << "\nScores: X: " << scoreX << " | O: " << scoreO << " | Draws: " << scoreDraw << "\n";
    }

    void startFriendGame() {
        vsBot = false;
        startGame(false);
    }

    void showScores() {
        clearScreen();
        cout << "===== SCORES =====\n";
        cout << "Player X wins: " << scoreX << "\n";
        cout << "Player O wins: " << scoreO << "\n";
        cout << "Draws: " << scoreDraw << "\n";
    }

    void resetScores() {
        scoreX = scoreO = scoreDraw = 0;
        cout << "Scores reset.\n";
    }
};

// -------------------------------------------------------------
// Entry point
// -------------------------------------------------------------
int main() {
    GameManager game;
    game.showMainMenu();
    return 0;
}