// Clean Up Game -- Genetic Algorithm Intro.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "game.h"


int main(int argc, char* argv[]) {
	std::cout << std::left;

	int numBots = 200;
	int numGenerations = 50;
	int boardWidth = 8;
	int boardHeight = 8;
	double messChance = 0.2;
	double mutationChance = 0.01;
	bool excelMode = false;

	for (int i = 1; i < argc; ++i) {
		if (argv[i] == std::string("--numBots") || argv[i] == std::string("--b")) {
			i++;
			numBots = std::stoi(argv[i]);
		} else if (argv[i] == std::string("--numGenerations") || argv[i] == std::string("--g")) {
			i++;
			numGenerations = std::stoi(argv[i]);
		} else if (argv[i] == std::string("--boardWidth") || argv[i] == std::string("--w")) {
			i++;
			boardWidth = std::stoi(argv[i]);
		} else if (argv[i] == std::string("--boardHeight") || argv[i] == std::string("--h")) {
			i++;
			boardHeight = std::stoi(argv[i]);
		} else if (argv[i] == std::string("--messChance") || argv[i] == std::string("--c")) {
			i++;
			messChance = std::stof(argv[i]);
		} else if (argv[i] == std::string("--mutationChance") || argv[i] == std::string("--m")) {
			i++;
			mutationChance = std::stof(argv[i]);
		} else if (argv[i] == std::string("--excel") || argv[i] == std::string("--e")) {
			i++;
			excelMode = true;
		} else {
			std::cerr << "Flag " << argv[i] << " not recognized.\n";
		}
	}
	Game game(excelMode, numBots, numGenerations, boardWidth, boardHeight, messChance);
	std::cout << std::endl << std::endl;
}

/*
Notes guide:
Main Thing (idea, function, class, etc.)
	- Part of main thing
		+ More detail, additions
			//personal comment on thing
	1. First item in list
	2. Second item in list
	\/
	n. nth item in list. shocker.

Program structure:

Done?	| Functionality/Structure
______|__________________________________________________________________________________|
yes	  Game Board
 yes			- 8x8 grid, a number of messes spawn randomly (adjustable)
______|__________________________________________________________________________________|
yes	  Bot Class
 yes			- The Chromosome
					+ A ledger with all possible states and corresponding actions
					+ For each position in the ordered ledger, the assigned action has a 
					  number. String these together and that's the chromosome.
 yes			- Fitness 
					+ Run the bot through the board:
					  +15 for successful clean up
					  -10 for slippery floors (cleaning an already clean floor)
					  -3  for property damage (bumping into a wall)
					  -1  for each move
______|__________________________________________________________________________________|
yes		  Genetic Algorithm -- in Game::gameLoop()
 yes			1. Spawn a set number of Bots with random traits
 yes			2. Calculate the fitness of each Bot (run the game)
 yes			3. Take 2/4/whatever of the top Bots and combine their genes into new Bots
	yes			- reproduce function, taking 2 bots and creating n new ones with a percent
						chance mutation on each gene
 yes			4. Repeat from 2 until satisfied
______|__________________________________________________________________________________|
wip		UI
 yes			- The ability to run a set number of generations at a time 
 no				+ Include other break conditions 
 no 				+ if a bot reaches a certain fitness, stop the algorithm 
 yes			- Watch the best bot of a current generation play the game in 'real time'
 _____|__________________________________________________________________________________|
					

Ideas for future: 
	- More robust sensors
		+ Use raycasts to determine how far away the next object is
			// may require more complex Bot than a simple ledger
	- Memory
		+ Some internal representation of the board
			// this might require a whole neural net 
	- More complex game!
		+ Add more bots with different functions that can communicate with each other
			// hard
		+ Add obstacles to avoid
			+ tables, people walking around
*/