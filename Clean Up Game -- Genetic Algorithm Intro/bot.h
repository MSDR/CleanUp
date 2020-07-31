#ifndef BOT_H_
#define BOT_H_

#include "board.h"

#include <array>
#include <ctime>
#include <iostream>
#include <map>
#include <random>
#include <string>

enum Action {
	clean,
	moveNorth,
	moveSouth,
	moveEast,
	moveWest
};

enum Tile {
	none,
	mess, 
	wall
};

class Bot {
public:
	//Tiles are held in CNESW [current, north, east, south, west] order
	typedef std::pair<std::array<Tile, 5>, Action> Gene;

	Bot();
	Bot(Bot &mom, Bot &dad, double mutationChance);

	void generateChromosome();
	void printChromosome();

	int getFitness(Board board, bool playVisually = true);

private:
	std::map<std::array<Tile, 5>, Action> chromosome_;
	int id_;
};

#endif