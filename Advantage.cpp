#include"Advantage.h"
#include<sstream>
namespace Gaming {

	const char Advantage::ADVANTAGE_ID = 'D';
	const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;

	Advantage::Advantage(const Game& g, const Position& p, double capacity) : 
		Resource(g, p, capacity * ADVANTAGE_MULT_FACTOR) {}

	Advantage::~Advantage() {}

	void Advantage::print(std::ostream& os) const {
		std::stringstream ss;
		ss << ADVANTAGE_ID << Advantage::__id;
		os << ss.str();
	}

	double Advantage::getCapacity() const { return Advantage::__capacity; }

	double Advantage::consume() {
		return __capacity;
	}

}