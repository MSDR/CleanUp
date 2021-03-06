#ifndef BOARD_H_
#define BOARD_H_

#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>

class Board {
public:
	Board(int boardWidth = 8, int boardHeight = 8, double messChance = 0.2f);

	std::vector<std::vector<int> > board_;

	void generateBoard(double messChance = 0.2, int width = 8, int height = 8);
	void printBoard(int botX = -1, int botY = -1) const;

	int w_;
	int h_;
	int messes_;
};

#endif