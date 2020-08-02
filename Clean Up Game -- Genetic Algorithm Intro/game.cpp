#include "game.h"

struct {
	bool operator()(const std::pair<Bot*, int> &l, const std::pair<Bot*, int> &r) const {
		return l.first->fitness_ > r.first->fitness_;
	}
} populationSortByFitness;

Game::Game(int numBots, int numGenerations, int boardWidth, int boardHeight, double messChance, double mutationChance) :
	numBots_(numBots),
	mutationChance_(mutationChance)
{
	initializeGame(numBots, numGenerations, boardWidth, boardHeight, messChance);
	gameLoop();
}

void Game::initializeGame(int numBots, int numGenerations, int boardWidth, int boardHeight, double messChance) {
	board_ = Board(boardWidth, boardHeight, messChance);
	board_.printBoard();

	std::srand(std::time(0)); //seed rng for chromosome generation
	for (int b = 0; b < numBots; ++b) {
		Bot* bot = new Bot(b);
		int fitness = bot->calculateFitness(board_);
		population_.push_back(std::make_pair(bot, fitness)); //use population_.clear() or .erase() to delete bots -- it clears memory too
	}
	std::sort(population_.begin(), population_.end(), populationSortByFitness);
	//population_[0].first.printChromosome(); 
	//printPopulation();
}

void Game::gameLoop() {
	int generation = 0;
	while(true) {
		int genToRunTo = generation;

		std::cout << "Run generation, print generation, or watch top bot?\n";
		std::string str;
		std::cin >> str;
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);

		if (str == "r" || str == "run" || str == "run generation") {
			std::cout << "\nHow many?\n";
			std::cin >> str;
			genToRunTo += std::stoi(str);
		} else if (str == "w" || str == "watch" || str == "watch top" || str == "watch top bot") {
			population_[0].first->calculateFitness(board_, true);
			continue;
		} else if (str == "p" || str == "print" || str == "print generation") {
			printPopulation();
			continue;
		} else {
			std::cout << "Command not Recognized.\n";
			continue;
		}

		while (generation < genToRunTo) {
			Bot mom(*population_[0].first);
			Bot dad(*population_[1].first);
		//	mom.printChromosome();
		//	dad.printChromosome();

			for (int i = 2; i < population_.size(); ++i) {
				delete population_[i].first;
			}
			population_.clear();

			int avgFitness = 0;
			for (int b = 2; b < numBots_; ++b) {
				Bot* bot = new Bot(mom, dad, mutationChance_, b);
				int fitness = bot->calculateFitness(board_);
				avgFitness += fitness;
				population_.push_back(std::make_pair(bot, fitness)); //use population_.clear() or .erase() to delete bots -- it clears memory too
			}
		//	population_[0].first.printChromosome(); 
			std::sort(population_.begin(), population_.end(), populationSortByFitness);

			if(generation%50 == 0) {
				avgFitness /= numBots_;
				std::cout << "Generation " << generation << " avg fitness: " << std::setw(4) << avgFitness << std::endl;
				std::cout << "Bot 0 | Fitness: " << std::setw(4) << population_[0].second << std::endl;
				std::cout << "Bot 1 | Fitness: " << std::setw(4) << population_[1].second << std::endl << std::endl;
			}
			//if(generation%50 == 0) printPopulation();
			generation++;
		}
	}
}

void Game::printPopulation() const {
	for (int p = 0; p < population_.size(); ++p) { 
		std::cout << "Bot: " << std::setw(3) << population_[p].first->id_ << " | Fitness: " << std::setw(4) << population_[p].second << std::endl;
	}
}


