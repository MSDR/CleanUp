#ifndef GAME_H_
#define GAME_H_

#include "board.h"
#include "bot.h"

#include <cctype>
#include <iostream>
#include <list>
#include <random>
#include <string>
#include <time.h>

class Game {
public:
	Game(bool excelMode = false, int numBots = 200, int numGenerations = 50, int boardWidth = 8, int boardHeight = 8, double messChance = 0.2f, double mutationChance = 0.1f);

private:	
	void initializeGame(int numBots, int numGenerations, int boardWidth = 8, int boardHeight = 8, double messChance = 0.2f);
	void gameLoop();

	//0 if empty
	//1 if contains mess
	Board board_;
	int numMesses_;

	int numBots_;
	double mutationChance_;
	std::vector<std::pair<Bot*, int> > population_;
	void printPopulation() const;

	bool excelMode_;
	//botCoords = x*y
};

#endif 