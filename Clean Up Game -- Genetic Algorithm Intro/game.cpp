#include "game.h"

Game::Game(int numBots, int numGenerations, int boardWidth, int boardHeight, float messChance) {
	initializeGame(numBots, numGenerations, boardWidth, boardHeight, messChance);
	gameLoop();
}

void Game::initializeGame(int numBots, int numGenerations, int boardWidth, int boardHeight, float messChance) {
	board_ = Board(boardWidth, boardHeight, messChance);
	board_.printBoard();

	for (int b = 0; b < numBots; ++b) {
		Bot bot = Bot();
		population_.push_back(bot);
	}
}

void Game::gameLoop() {
	//while (bool exitCondition = false) {

	//}
}


