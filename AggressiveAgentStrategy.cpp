#include"AggressiveAgentStrategy.h"
#include"Game.h";

namespace Gaming {
	const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * 0.75;

	AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy) {
		__agentEnergy = agentEnergy;
	}

	AggressiveAgentStrategy::~AggressiveAgentStrategy() {

	}

	ActionType AggressiveAgentStrategy::operator()(const Surroundings& s) const {
		bool pieces[4] = { false, false, false, false };
		std::vector<int> ways;
		PositionRandomizer random;
		Position p, middle(1,1);

		//this loop saves time by knoocking out loops and ifs
		for (int i = 0; i < 8; ++i) {
			if ((s.array[i] == SIMPLE || s.array[i] == STRATEGIC) && 
				__agentEnergy >= DEFAULT_AGGRESSION_THRESHOLD)//checks for agents 
				pieces[0] = true;
			else if (s.array[i] == ADVANTAGE)//checks for advantage
				pieces[0] = true;
			else if (s.array[i] == FOOD)//checks for food
				pieces[0] = true;
			else if (s.array[i] == EMPTY)//checks for empty
				pieces[0] = true;
		}

		if (pieces[0]) {//moves towards agent if true
			for (int i = 0; i < 8; ++i)
				if (s.array[i] == SIMPLE || s.array[i] == STRATEGIC)
					ways.push_back(i);

			p = random(ways);
			return Game::reachSurroundings(middle, p);
		}
		else if (pieces[1]) {//moves to advantage if true
			for (int i = 0; i < 8; ++i)
				if (s.array[i] == ADVANTAGE)
					ways.push_back(i);

			p = random(ways);
			return Game::reachSurroundings(middle, p);
		}
		else if (pieces[2]) { //moves to food if true
			for (int i = 0; i < 8; ++i)
				if (s.array[i] == FOOD)
					ways.push_back(i);

			p = random(ways);
			return Game::reachSurroundings(middle, p);
		}
		else if (pieces[3]) {//moves to empty space if true
			for (int i = 0; i < 8; ++i)
				if (s.array[i] == EMPTY)
					ways.push_back(i);

			p = random(ways);
			return Game::reachSurroundings(middle, p);
		}

		//didn't meet any requirements to move so it's staying in place
		return STAY;
	}
}