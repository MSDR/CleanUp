#include "bot.h"

Bot::Bot() {
	generateChromosome();
	//printChromosome();
}

Bot::Bot(Bot &mom, Bot &dad, double mutationChance) {
	//combine parent's chromosomes with mutations
}

void Bot::generateChromosome() {
	int c=0, n=0, e=0, s=0, w=0;
	while (c < 3) {
		Action action = static_cast<Action>(std::rand() % 5);
		std::array<Tile, 5> radar{ static_cast<Tile>(c), static_cast<Tile>(n), static_cast<Tile>(e), static_cast<Tile>(s), static_cast<Tile>(w)};
		chromosome_.insert(std::make_pair(radar, action));

		w++;
		if (w >= 3) { s++; w = 0; }
		if (s >= 3) { e++; s = 0; }
		if (e >= 3) { n++; e = 0; }
		if (n >= 3) { c++; n = 0; }
	}
}

void Bot::printChromosome() {
	std::cout << "\nBot " << id_ << " Chromosome: \n";

	int geneCount = 0;
	for (std::map<std::array<Tile, 5>, Action>::iterator ribosome = chromosome_.begin(); ribosome != chromosome_.end(); ++ribosome) {
		std::cout << "Gene " << (geneCount < 10 ? " " : (geneCount < 100 ? " " : (geneCount < 1000 ? " " : ""))) << geneCount  << ": ";

		for (std::array<Tile, 5>::const_iterator itr = (*ribosome).first.begin(); itr != (*ribosome).first.end(); ++itr) {
			std::string tile;
			if (*itr == 0) tile = "none";
			else if (*itr == 1) tile = "mess";
			else if (*itr == 2) tile = "wall";

			std::cout << tile << "  ";
		}

		int a = (*ribosome).second;
		std::string action;
		if (a == 0) action = "clean";
		else if (a == 1) action = "moveNorth";
		else if (a == 2) action = "moveSouth";
		else if (a == 3) action = "moveEast";
		else if (a == 4) action = "moveWest";

		std::cout << "| " << action << std::endl;

		geneCount++;
	}
}

int Bot::getFitness(Board board, bool playVisually) {
	int maxMoves = board.w_*board.h_*4;
	int botX = 1, botY = 1;
	int moveCount = 0;
	int messesCleaned = 0;

	int fitness = 0;
	/*	+1 for successful clean up
		-1 for slippery floors (cleaning an already clean floor)
		-1 for property damage (bumping into a wall) */
	while (moveCount < maxMoves && messesCleaned < board.messes_) {
		if (playVisually) {
			std::cout << "\nFitness: " << fitness << std::endl;
			board.printBoard(botX, botY);
		}

		std::array<Tile, 5> radar;
		radar[0] = static_cast<Tile>(board.board_[botY][botX]);													//Current
		radar[1] = botY-1 > -1 ? static_cast<Tile>(board.board_[botY-1][botX]) : Tile::wall;			//North
		radar[2] = botX+1 < board.w_ ? static_cast<Tile>(board.board_[botY][botX+1]) : Tile::wall;	//East
		radar[3] = botY+1 < board.h_ ? static_cast<Tile>(board.board_[botY+1][botX]) : Tile::wall;	//South
		radar[4] = botX-1 > -1 ? static_cast<Tile>(board.board_[botY][botX-1]) : Tile::wall;			//West

		Action action = chromosome_[radar];
		switch (action) {
			case clean:
				if (board.board_[botY][botX] == 1) { //Successful clean
					fitness++;
					board.board_[botY][botX] = 0; //Slippery floors
				} else {
					fitness--;
				}
				break;
			case moveNorth:
				if (botY - 1 < 0)
					fitness--;
				else
					botY--;
				break;
			case moveSouth:
				if (botY + 1 >= board.h_)
					fitness--;
				else
					botY++;
				break;
			case moveEast:
				if (botX + 1 >= board.w_)
					fitness--;
				else
					botX++;
				break;
			case moveWest:
				if (botX - 1 < 0)
					fitness--;
				else
					botX--;
				break;
		}

		moveCount++;
	}

	return fitness;
}
