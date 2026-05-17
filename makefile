CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = tictactoe
OBJS = Board.o HumanPlayer.o RandomBot.o MinimaxBot.o GameManager.o main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)