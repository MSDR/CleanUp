#include "board.h"

Board::Board(int boardWidth, int boardHeight, float messChance) {
	w_ = boardWidth;
	h_ = boardHeight;

	try {
		generateBoard(messChance, boardWidth, boardHeight);
	} catch (const char* err) {
		std::cerr << err << std::endl;
	}
}

void Board::generateBoard(float messChance, int width, int height) {
	if (messChance <= 0 || messChance >= 1)
		throw "messChance should be a float between 0 and 1.";
	if (width <= 0 || height <= 0)
		throw "Check that the width and height are positive.";

	std::srand(time(NULL));
	for (int h = 0; h < height; ++h) {
		board_.push_back(std::vector<int>());
		for (int w = 0; w < width; ++w) {
			bool mess = (std::rand() % 10) / 10.0 <= messChance ? true : false;
			if (mess) messes_++;
			board_[h].push_back(int(mess)); //0 if empty, 1 if messy
		}
	}
}

void Board::printBoard(int botX, int botY) {
	for (int h = 0; h < board_.size(); ++h) {
		for (int w = 0; w <= 5*board_[h].size(); ++w)
			std::cout << (w % 5 == 0 ? (h==0 ? " " : "|") : "_");

		std::cout << std::endl;
		for (int w = 0; w <= 5 * board_[h].size(); ++w)
			std::cout << (w % 5 == 0 ? "|" : " ");

		std::cout << std::endl << "| ";

		for (int w = 0; w < board_[h].size(); ++w) {
			if (botX == h && botY == w)
				std::cout << "B";
			else
				std::cout << " ";

			switch(board_[h][w]) {
			case 0:
				std::cout << " "; break;
			case 1:
				std::cout << "@"; break;
			default:
				std::cout << "?"; break;
			}
			std::cout << " | ";
		}
		std::cout << std::endl;
	}

	for (int w = 0; w <= 5*board_[0].size(); ++w)
		std::cout << (w % 5 == 0 ? "|" : "_");

	std::cout << std::endl;
}