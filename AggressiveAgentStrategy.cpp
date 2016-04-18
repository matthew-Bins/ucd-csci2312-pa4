#include"AggressiveAgentStrategy.h"
#include"Game.h";
#include<ctime>

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
		std::default_random_engine gen(time(0));
		Position p, middle(1,1);
		int place;

		//this loop saves time by knoocking out loops and ifs
		for (int i = 0; i < 8; ++i) {
			if ((s.array[i] == SIMPLE || s.array[i] == STRATEGIC) && 
				__agentEnergy >= DEFAULT_AGGRESSION_THRESHOLD)//checks for agents 
				pieces[0] = true;
			else if (s.array[i] == ADVANTAGE)//checks for advantage
				pieces[1] = true;
			else if (s.array[i] == FOOD)//checks for food
				pieces[2] = true;
			else if (s.array[i] == EMPTY)//checks for empty
				pieces[3] = true;
		}

		if (pieces[0]) {//moves towards agent if true
			for (int i = 0; i < 8; ++i) {
				if (s.array[i] == SIMPLE || s.array[i] == STRATEGIC)
					ways.push_back(i);
			}

			place = ways[gen() % ways.size()];
		}
		else if (pieces[1]) {//moves to advantage if true
			for (int i = 0; i < 8; ++i) {
				if (s.array[i] == ADVANTAGE)
					ways.push_back(i);
			}

			place = ways[gen() % ways.size()];
		}
		else if (pieces[2]) { //moves to food if true
			for (int i = 0; i < 8; ++i) {
				if (s.array[i] == FOOD)
					ways.push_back(i);
			}

			place = ways[gen() % ways.size()];
		}
		else if (pieces[3]) {//moves to empty space if true
			for (int i = 0; i < 8; ++i) {
				if (s.array[i] == EMPTY)
					ways.push_back(i);
			}

			place = ways[gen() % ways.size()];
		}
		else
			return STAY;

		switch (place) {
		case 0:
			p.x = middle.x - 1;
			p.y = middle.y - 1;
			break;
		case 1:
			p.x = middle.x - 1;
			p.y = middle.y;
			break;
		case 2:
			p.x = middle.x - 1;
			p.y = middle.y + 1;
			break;
		case 3:
			p.x = middle.x;
			p.y = middle.y - 1;
			break;
		case 4:
			p.x = middle.x;
			p.y = middle.y;
			break;
		case 5:
			p.x = middle.x;
			p.y = middle.y + 1;
			break;
		case 6:
			p.x = middle.x + 1;
			p.y = middle.y - 1;
			break;
		case 7:
			p.x = middle.x + 1;
			p.y = middle.y;
			break;
		case 8:
			p.x = middle.x + 1;
			p.y = middle.y + 1;
			break;
		}

		return Game::reachSurroundings(middle, p);
	}
}