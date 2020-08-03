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
	Game(bool excelMode, int numBots, int boardWidth, int boardHeight, double messChance, double mutationChance);

private:	
	void initializeGame(int numBots, int numGenerations, int boardWidth, int boardHeight, double messChance);
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