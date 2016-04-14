#include"DefaultAgentStrategy.h"
#include"Game.h"

namespace Gaming {

	DefaultAgentStrategy::DefaultAgentStrategy() {

	}

	DefaultAgentStrategy::~DefaultAgentStrategy() {

	}

	ActionType DefaultAgentStrategy::operator()(const Surroundings& s) const {
		bool pieces[4] = { false, false, false, false };
		std::vector<int> ways;
		PositionRandomizer random;
		Position p;
		
		//this loop is to check if there's that piece to save some time 
		//because if you are surrounded by simples you will have to go
		//through 4 fours loops before finding out this way you have 2 loops at most
		for (int i = 0; i < 8; ++i) {
			if (s.array[i] == ADVANTAGE)//checks for advantage 
				pieces[0] = true;
			else if (s.array[i] == FOOD)//checks for food
				pieces[0] = true;
			else if (s.array[i] == EMPTY)//checks for empty
				pieces[0] = true;
			else if (s.array[i] == SIMPLE)//checks for simples
				pieces[0] = true;

		}

		if (pieces[0]) {

			for (int i = 0; i < 8; ++i)//check for advantage
				if (s.array[i] == ADVANTAGE)
					ways.push_back(i);

			if (ways.size() != 0) {//goes  to advantage
				p = random(ways);
				return Game::reachSurroundings(p, p);
			}
		}
		else if (pieces[1]) {
			for (int i = 0; i < 8; ++i)//no advantage check for food
				if (s.array[i] == FOOD)
					ways.push_back(i);

			if (ways.size() != 0) {//goes to food
				p = random(ways);
				return Game::reachSurroundings(p, p);
			}
		}
		else if (pieces[2]) {
			for (int i = 0; i < 8; ++i)//no food check for empty
				if (s.array[i] == EMPTY)
					ways.push_back(i);

			if (ways.size() != 0) {//goes to empty
				p = random(ways);
				return Game::reachSurroundings(p, p);
			}
		}
		else if (pieces[3]) {
			for (int i = 0; i < 8; ++i)//no empty check for simple
				if (s.array[i] == SIMPLE)
					ways.push_back(i);

			if (ways.size() != 0) {//goes to simple
				p = random(ways);
				return Game::reachSurroundings(p, p);
			}
		}

		//array pieces is full of false so the piece stays put
		return STAY;
	}
}