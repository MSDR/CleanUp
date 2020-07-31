#include "game.h"

Game::Game(int numBots, int numGenerations, int boardWidth, int boardHeight, float messChance) {
	initializeGame(numBots, numGenerations, boardWidth, boardHeight, messChance);
	gameLoop();
}

void Game::initializeGame(int numBots, int numGenerations, int boardWidth, int boardHeight, float messChance) {
	board_ = Board(boardWidth, boardHeight, messChance);
	board_.printBoard();

	std::srand(std::time(0)); //seed rng for chromosome generation
	for (int b = 0; b < numBots; ++b) {
		Bot* bot = new Bot();
		bot->id_ = b;
		int fitness = bot->getFitness(board_);
		population_.push_back(std::make_pair(*bot, fitness));
	}

	for (int p = 0; p < population_.size(); ++p) {
		std::cout << "Bot: " << population_[p].first.id_ << " Fitness: " << population_[p].second << std::endl;
	}
	//population_[0].printChromosome();
	//population_[0].getFitness(board_, true);
	std::string str;
	std::cin >> str;
	if (str == "c")
		population_[0].first.getFitness(board_, true);
}

void Game::gameLoop() {
	//while (bool exitCondition = false) {

	//}
}


