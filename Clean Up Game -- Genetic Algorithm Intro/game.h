#ifndef GAME_H_
#define GAME_H_

#include "board.h"
#include "bot.h"

#include <iostream>
#include <list>
#include <random>
#include <string>
#include <time.h>
#include <vector>

class Game {
public:
	Game(int numBots = 200, int numGenerations = 50, int boardWidth = 8, int boardHeight = 8, float messChance = 0.2f);

private:	
	void initializeGame(int numBots, int numGenerations, int boardWidth = 8, int boardHeight = 8, float messChance = 0.2f);
	void gameLoop();

	//0 if empty
	//1 if contains mess
	Board board_;
	int numMesses_;

	std::vector<std::pair<Bot, int> > population_;
	//botCoords = x*y
};

#endif 