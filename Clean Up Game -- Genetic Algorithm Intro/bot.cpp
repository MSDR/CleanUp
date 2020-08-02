#include "bot.h"

Bot::Bot(int id) : 
	id_(id),
	fitness_(INT_MAX+1)
{
	generateChromosome();
	//printChromosome();
}

Bot::Bot(const Bot & clone) :
	id_(clone.id_),
	fitness_(clone.fitness_) 
{
	for (std::map<std::array<Tile, 5>, Action>::const_iterator ribosome = clone.chromosome_.begin(); ribosome != clone.chromosome_.end(); ++ribosome) {
		chromosome_.insert(std::make_pair(ribosome->first, ribosome->second));
	}
}

Bot::Bot(const Bot &mom, const Bot &dad, double mutationChance, int id) :
	id_(id)
{
	//Generate set of genes (by number) to mutate
	int mutations = 0;
	std::set<int> mutatedGenes;
	for (int i = 0; i < mom.chromosome_.size()*mutationChance; ++i) {
		int rand = std::rand() % mom.chromosome_.size();
		while (mutatedGenes.find(rand) != mutatedGenes.end()) {
			rand = std::rand() % mom.chromosome_.size();
		}
		mutatedGenes.insert(rand);
	}

	//Combine parent's chromosomes into chromosome_, with mutations
	int gene = 0;
	std::map<std::array<Tile, 5>, Action>::const_iterator itr = mom.chromosome_.begin();
	while (itr != dad.chromosome_.end()) {
		Action action = itr->second;

		if (mutatedGenes.find(gene) != mutatedGenes.end()) {
			int mutation = std::rand() % 5;
			if (mutation == action) {
				mutation = mutation + std::rand() % 4;
				mutation = mutation > 4 ? 0 + (mutation - 4) : mutation;
			}
			action = static_cast<Action>(mutation);
			mutations++;
		}

		chromosome_.insert(std::make_pair(itr->first, action));

		gene++;
		if (gene > mom.chromosome_.size() / 2) { //switch from mom to dad
			itr = dad.chromosome_.begin();
			for (int i = 0; i < gene-1; ++i) {
				++itr;
			}
		}

		++itr;
	}
}

void Bot::generateChromosome() {
	if (!chromosome_.empty()) return;

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

void Bot::printChromosome() const {
	std::cout << "\nBot " << id_ << " Chromosome: \n";

	int geneCount = 0;
	for (std::map<std::array<Tile, 5>, Action>::const_iterator ribosome = chromosome_.begin(); ribosome != chromosome_.end(); ++ribosome) {
		std::cout << "Gene " << std::setw(3) << geneCount  << ": "; //increase setw if geneCount goes above 999

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

int Bot::calculateFitness(Board board, bool playVisually) {
	int maxMoves = board.w_*board.h_*4;
	int botX = 0, botY = 0;
	int moveCount = 0;
	int messesCleaned = 0;

	/*	+1 for successful clean up
		-1 for slippery floors (cleaning an already clean floor)
		-1 for property damage (bumping into a wall) */
	int fitness = 0;
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

		Action action = chromosome_.at(radar);
		switch (action) {
			case clean:
				if (board.board_[botY][botX] == 1) { //Successful clean
					fitness++;
					board.board_[botY][botX] = 0; 
					messesCleaned++;
				} else { //Slippery floors
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

	if (playVisually) {
		std::cout << "\nFitness: " << fitness << std::endl;
		board.printBoard(botX, botY);
	}

	fitness_ = fitness;
	return fitness;
}
