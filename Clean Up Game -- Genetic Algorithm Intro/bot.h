#ifndef BOT_H_
#define BOT_H_

#include "board.h"

#include <array>
#include <ctime>
#include <iostream>
#include <map>
#include <random>
#include <set>
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

	Bot(int id = -1);
	Bot(const Bot& clone);
	Bot(const Bot &mom, const Bot &dad, double mutationChance, int id = -1);

	void generateChromosome();
	void printChromosome() const;

	std::pair<int, bool> calculateFitness(Board board, bool playVisually = false); //board is by non-const copy intentionally

	int id_;
	int fitness_;
	int movesToComplete_;
	int messesCleaned_;
private:
	std::map<std::array<Tile, 5>, Action> chromosome_;
};

#endif