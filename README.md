# Tic‑Tac‑Toe – Professional C++ Implementation

A feature‑rich, object‑oriented Tic‑Tac‑Toe game with **two modes** (two‑player and vs AI) and an **unbeatable Minimax bot**. The game runs in the terminal, shows board positions (1‑9), supports score tracking, and is fully compiled with C++17.

## ✨ Features

| Feature | Description |
|---------|-------------|
| **Two game modes** | Play with a friend locally or challenge the AI. |
| **AI difficulty** | Easy (random moves) – Hard (Minimax, unbeatable). |
| **Clear board display** | Empty cells show numbers 1‑9 for intuitive move selection. |
| **Score tracking** | Wins and draws are counted across rounds. |
| **Multi‑file architecture** | Separated into headers and sources – clean, maintainable. |
| **Cross‑platform** | Works on Windows, Linux, macOS (tested with GCC / MinGW). |
| **No terminal clearing** | Game history stays visible – you see every move. |

## 🚀 How to Compile & Run

### Prerequisites
- A C++ compiler supporting **C++17** (g++, clang++, or MSVC)

### Compilation (Windows / Linux / macOS)
```bash
# Clone or download the repository
git clone https://github.com/yourusername/tictactoe.git
cd tictactoe

# Compile all .cpp files
g++ -std=c++17 *.cpp -o tictactoe

# Run the executable
./tictactoe      # Linux/macOS
tictactoe.exe    # Windows