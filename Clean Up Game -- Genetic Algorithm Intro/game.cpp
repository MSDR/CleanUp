#include "game.h"

struct {
	bool operator()(const std::pair<Bot*, int> &l, const std::pair<Bot*, int> &r) const {
		return l.first->fitness_ > r.first->fitness_;
	}
} populationSortByFitness;

Game::Game(bool excelMode, int numBots, int numGenerations, int boardWidth, int boardHeight, double messChance, double mutationChance) :
	numBots_(numBots),
	mutationChance_(mutationChance),
	excelMode_(excelMode)
{
	initializeGame(numBots, numGenerations, boardWidth, boardHeight, messChance);
	gameLoop();
}

void Game::initializeGame(int numBots, int numGenerations, int boardWidth, int boardHeight, double messChance) {
	board_ = Board(boardWidth, boardHeight, messChance);
	numMesses_ = board_.messes_;
	if(!excelMode_) board_.printBoard();

	std::srand(std::time(NULL)); //seed rng for chromosome generation
	for (int b = 0; b < numBots; ++b) {
		Bot* bot = new Bot(b);
		int fitness = bot->calculateFitness(board_).first;
		population_.push_back(std::make_pair(bot, fitness)); //use population_.clear() or .erase() to delete bots -- it clears memory too
	}
	std::sort(population_.begin(), population_.end(), populationSortByFitness);
	//population_[0].first->printChromosome(); 
	//printPopulation();
}

void Game::gameLoop() {
	int generation = 0;
	bool overrideGameCompletion = false;

	while(true) {
		int genToRunTo = generation;

		std::cout << (excelMode_ ? "How many generations?\n" : "Run generation, print generation, or watch top bot?\n");
		std::string str;
		std::cin >> str;
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);

		if (excelMode_) {
			//std::cout << std::setw(4) << population_[0].second << " " << std::setw(3) << population_[0].first->movesToComplete_ << " " << avgFitness << std::endl;
			if (str == "max" || str == "inf") { 
				genToRunTo = INT_MAX;
				std::cout << "Enter o to stop at first completion, any key for true infinite:\n";
				std::cin >> str;
				if (str == "o") overrideGameCompletion = true;
			} else {
				genToRunTo += std::stoi(str);
			}
			std::cout << "\ngeneration  topFitness  topMoves  avgFitness\n";
		} else {
			if (str == "r" || str == "run" || str == "run generation") {
				std::cout << "\nHow many?\n";
				std::cin >> str;
				if (str == "max" || str == "inf") genToRunTo = INT_MAX;
				else genToRunTo += std::stoi(str);
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
			std::cout << std::endl;
		}

		while (generation < genToRunTo) {
			Bot* mom = new Bot(*population_[0].first);
			Bot* dad = new Bot(*population_[1].first);
		//	mom.printChromosome();
		//	dad.printChromosome();

			for (int i = 0; i < population_.size(); ++i) {
				delete population_[i].first;
			}
			population_.clear();
			population_.push_back(std::make_pair(mom, mom->fitness_));
			population_.push_back(std::make_pair(dad, dad->fitness_));

			int avgFitness = 0;
			bool botCompletedGame = false;
			for (int b = 2; b < numBots_; ++b) {
				Bot* bot = new Bot(*mom, *dad, mutationChance_, b);
				int fitness = bot->calculateFitness(board_).first;
				botCompletedGame = bot->calculateFitness(board_).second;
				avgFitness += fitness;
				population_.push_back(std::make_pair(bot, fitness)); //use population_.clear() or .erase() to delete bots -- it clears memory too
			}
		//	population_[0].first.printChromosome(); 
			std::sort(population_.begin(), population_.end(), populationSortByFitness);

			if (botCompletedGame && !overrideGameCompletion) {
				overrideGameCompletion = true;

				avgFitness /= numBots_;
				std::cout << "Generation " << generation << " avg fitness: " << std::setw(4) << avgFitness << std::endl;
				std::cout << "Bot 0 | Fitness: " << std::setw(4) << population_[0].second << " | Moves: " << std::setw(3) << population_[0].first->movesToComplete_ << std::endl;
				std::cout << "Bot 1 | Fitness: " << std::setw(4) << population_[1].second << " | Moves: " << std::setw(3) << population_[1].first->movesToComplete_ << std::endl << std::endl;

				std::cout << "A bot completed the game! Enter h to halt or any key to continue: ";
				std::string s;
				std::cin >> s;
				if (s == "h") break;
			}

			avgFitness /= numBots_;

			if(!excelMode_ && (generation%50 == 0 || generation == genToRunTo-1)) {
				std::cout << "Generation " << generation << " avg fitness: " << std::setw(4) << avgFitness << std::endl;
				std::cout << "Bot 0 | Fitness: " << std::setw(4) << population_[0].second << " | Moves: " << std::setw(3) << population_[0].first->movesToComplete_ << std::endl;
				std::cout << "Bot 1 | Fitness: " << std::setw(4) << population_[1].second << " | Moves: " << std::setw(3) << population_[1].first->movesToComplete_ << std::endl << std::endl;
			} else if (excelMode_) {
				std::cout << std::setw(12) << generation << std::setw(11) << population_[0].second << std::setw(10) << population_[0].first->movesToComplete_ << avgFitness << std::endl;
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


