//Matthew Bins
#include"Simple.h"
#include<sstream>
#include<ctime>

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
		Position p, This = this->getPosition();
		int place;
		std::default_random_engine gen(time(0));

		for (int i = 0; i < 8; ++i) {
			if (s.array[i] == FOOD || s.array[i] == ADVANTAGE)
				ways.push_back(i);
		}

		if (ways.size() > 0) {
			place = ways[gen() % ways.size()];
		}
		else {
			for (int i = 0; i < 8; ++i) {
				if (s.array[i] == EMPTY)
					ways.push_back(i);
			}

			if (ways.size() > 0) {
				place = ways[gen() % ways.size()];
			}
			else
				return STAY;
		}
		switch (place) {
		case 0:
			p.x = This.x - 1;
			p.y = This.y - 1;
			break;
		case 1:
			p.x = This.x - 1;
			p.y = This.y;
			break;
		case 2:
			p.x = This.x - 1;
			p.y = This.y + 1;
			break;
		case 3:
			p.x = This.x;
			p.y = This.y - 1;
			break;
		case 4:
			p.x = This.x;
			p.y = This.y;
			break;
		case 5:
			p.x = This.x;
			p.y = This.y + 1;
			break;
		case 6:
			p.x = This.x + 1;
			p.y = This.y - 1;
			break;
		case 7:
			p.x = This.x + 1;
			p.y = This.y;
			break;
		case 8:
			p.x = This.x + 1;
			p.y = This.y + 1;
			break;
		}

		move = __game.reachSurroundings(This, p);


		return move;
	}

}