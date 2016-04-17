//Matthew Bins
#include"Simple.h"
#include<sstream>

namespace Gaming {

	const char Simple::SIMPLE_ID = 'S';

	Simple::Simple(const Game& g, const Position& p, double energy) :
	Agent(g, p, energy){}

	Simple::~Simple() {}

	void Simple::print(std::ostream& os) const {
		std::stringstream ss;
		ss << SIMPLE_ID << Simple::__id;
		os << ss.str();
	}

	ActionType Simple::takeTurn(const Surroundings& s) const {
		ActionType move;
		std::vector<int> ways;
		PositionRandomizer random;
		Position p;

		for (int i = 0; i < 8; ++i) {
			if (s.array[i] == FOOD || s.array[i] == ADVANTAGE)
				ways.push_back(i);
		}

		if (ways.size() != 0)//checks if there's any resources near
			p = random(ways);
		else {
			ways.clear();
			for (int i = 0; i < 8; ++i) {
				if (s.array[i] == EMPTY)
					ways.push_back(i);
			}
			if (ways.size() != 0)//checks if there's any empty spaces near
				p = random(ways);
			else {//sets p to center because it's not moving
				p.x = 1;
				p.y = 1;
			}
		}

		move = __game.reachSurroundings(this->getPosition(), p);


		return move;
	}

}