#include"Food.h"
#include<sstream>

namespace Gaming {

	const char Food::FOOD_ID = 'F';

	Food::Food(const Game& g, const Position& p, double capacity) : 
		Resource(g, p, capacity) {}

	Food::~Food() {}

	void Food::print(std::ostream& os) const {
		std::stringstream ss;
		ss << FOOD_ID << Food::__id;
		os << ss.str();
	}

}