#include"Strategic.h"
#include<sstream>

namespace Gaming {

	const char Strategic::STRATEGIC_ID = 'T';

	Strategic::Strategic(const Game& g, const Position& p, double energy,Strategy* s) : 
		Agent(g, p, energy) {
		__strategy = s;
	}

	Strategic::~Strategic() {
		delete __strategy;
	}

	void Strategic::print(std::ostream& os) const {
		std::stringstream ss;
		ss << STRATEGIC_ID << Strategic::__id;
		os << ss.str();
	}

	ActionType Strategic::takeTurn(const Surroundings& s) const {





		return E;
	}
}