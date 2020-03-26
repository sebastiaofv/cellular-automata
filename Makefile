all: src/main.cpp
	g++ src/gameOfLife.cpp src/main.cpp -o bin/cellular-automata -Wall -Werror -ggdb -funroll-loops -lncurses

