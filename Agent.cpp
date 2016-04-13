#include"Agent.h"
#include"Resource.h"

namespace Gaming {
	const double Agent::AGENT_FATIGUE_RATE = 0.3;

	Agent::Agent(const Game &g, const Position &p, double energy) : Piece(g, p) {
		__energy = energy;
	}

	Agent::~Agent() {

	}

	void Agent::age() {
		__energy -= AGENT_FATIGUE_RATE;
	}

	Piece& Agent::operator*(Piece& other) {
		return other.interact(this);
	}
	Piece& Agent::interact(Agent* other) {

		if (__energy == other->getEnergy()) { // energies equal each other
			this->finish();
			other->finish();
		}
		else if (__energy > other->getEnergy()) {//greater than agent it's fighting
			__energy -= other->getEnergy();
			other->finish();
		}
		else { //the other agent is greater
			other->addEnergy(__energy * -1);
			this->finish();
		}
		return *this;
	}
	Piece& Agent::interact(Resource* other) {
		addEnergy(other->consume());
		return *this;
	}

}