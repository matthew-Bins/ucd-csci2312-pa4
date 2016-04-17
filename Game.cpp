//Matthew Bins
#include"Game.h"
#include "Simple.h"
#include "Strategic.h"
#include "Food.h"
#include "Advantage.h"
#include "Piece.h"
#include<set>
#include<iomanip>

namespace Gaming {
	const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
	const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;
	const unsigned Game::MIN_WIDTH = 3;
	const unsigned Game::MIN_HEIGHT = 3;
	const double Game::STARTING_AGENT_ENERGY = 20;
	const double Game::STARTING_RESOURCE_CAPACITY = 10;
	PositionRandomizer Game::__posRandomizer = PositionRandomizer();

	void Game::populate() {

		__numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
		__numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
		unsigned int numStrategic = __numInitAgents / 2;
		unsigned int numSimple = __numInitAgents - numStrategic;
		unsigned int numAdvantages = __numInitResources / 4;
		unsigned int numFoods = __numInitResources - numAdvantages;
		//random number generator
		std::default_random_engine gen;
		std::uniform_int_distribution<int> d(0, __width * __height);

		while (numStrategic > 0) {
			int i = d(gen); // random index in the grid vector
			if (__grid[i] == nullptr) { // is position empty
				Position pos(i / __width, i % __width);
				__grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);
				numStrategic--;
			}
		}

		while (numSimple > 0) {
			int i = d(gen); // random index in the grid vector
			if (__grid[i] == nullptr) { // is position empty
				Position pos(i / __width, i % __width);
				__grid[i] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
				numSimple--;
			}
		}

		while (numAdvantages > 0) {
			int i = d(gen); // random index in the grid vector
			if (__grid[i] == nullptr) { // is position empty
				Position pos(i / __width, i % __width);
				__grid[i] = new Advantage(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
				numAdvantages--;
			}
		}

		while (numFoods > 0) {
			int i = d(gen); // random index in the grid vector
			if (__grid[i] == nullptr) { // is position empty
				Position pos(i / __width, i % __width);
				__grid[i] = new Food(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
				numFoods--;
			}
		}


	}

	Game::Game() {
		__width = MIN_WIDTH;
		__height = MIN_HEIGHT;
		__status = NOT_STARTED;

		int size = __width * __height;
		for (int i = 0; i < size; ++i)
			__grid.push_back(nullptr);

	}

	Game::Game(unsigned width, unsigned height, bool manual) {
		__width = width;
		__height = height;
		__status = NOT_STARTED;

		int size = __width * __height;
		for (int i = 0; i < size; ++i)
			__grid.push_back(nullptr);

		if (!manual)
			populate();
	}

	Game::~Game() {
		for (auto it = __grid.begin(); it != __grid.end(); ++it)
			if (*it != nullptr)
				delete *it;
	}

	unsigned int Game::getNumPieces() const { 
		int num = 0;

		for (auto it = __grid.begin(); it != __grid.end(); ++it)
			if (*it != nullptr)
				++num;

		return num;
	}

	unsigned int Game::getNumAgents() const { 
		int num = 0;

		for (auto it = __grid.begin(); it != __grid.end(); ++it) {
			Agent *agent = dynamic_cast<Agent*>(*it);

			if (agent) ++num;
		}

		return num;
	}

	unsigned int Game::getNumSimple() const { 
		int num = 0;

		for (auto it = __grid.begin(); it != __grid.end(); ++it) {
			Simple *simple = dynamic_cast<Simple*>(*it);

			if (simple) ++num;
		}

		return num;
	}

	unsigned int Game::getNumStrategic() const { 
		int num = 0;

		for (auto it = __grid.begin(); it != __grid.end(); ++it) {
			Strategic *strategic = dynamic_cast<Strategic*>(*it);

			if (strategic) ++num;
		}

		return num;
	}

	unsigned int Game::getNumResources() const { 
		int num = 0;

		for (auto it = __grid.begin(); it != __grid.end(); ++it) {
			Resource *resource = dynamic_cast<Resource*>(*it);

			if (resource) ++num;
		}

		return num;
	}

	const Piece* Game::getPiece(unsigned int x, unsigned int y) const {
		int place = y + (x * __width);

		return __grid[place];
	}

	// grid population methods
	void Game::addSimple(const Position& position) {
		if ((position.x < 0 && position.x > getWidth()) ||
			(position.y < 0 && position.y > getHeight()))
			throw OutOfBoundsEx(getWidth(), getHeight(), position.x, position.y);

		int place = position.y + (position.x * __width);
		__grid[place] = new Simple(*this, position, STARTING_AGENT_ENERGY);

	}

	void Game::addSimple(const Position& position, double energy) {
		if ((position.x < 0 && position.x > getWidth()) ||
			(position.y < 0 && position.y > getHeight()))
			throw OutOfBoundsEx(getWidth(), getHeight(), position.x, position.y);

		int place = position.y + (position.x * __width);
		__grid[place] = new Simple(*this, position, energy);
	}

	void Game::addSimple(unsigned x, unsigned y) {
		if ((x < 0 && x > getWidth()) ||(y < 0 && y > getHeight()))
			throw OutOfBoundsEx(getWidth(), getHeight(), x, y);

		Position p(x, y);

		int place = y + (x * __width);
		__grid[place] = new Simple(*this, p, STARTING_AGENT_ENERGY);
	}

	void Game::addSimple(unsigned x, unsigned y, double energy) {
		if ((x < 0 && x > getWidth()) || (y < 0 && y > getHeight()))
			throw OutOfBoundsEx(getWidth(), getHeight(), x, y);

		Position p(x, y);

		int place = y + (x * __width);
		__grid[place] = new Simple(*this, p, energy);
	}

	void Game::addStrategic(const Position& position, Strategy* s) {
		int place = position.y + (position.x * __width);

		__grid[place] = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
	}

	void Game::addStrategic(unsigned x, unsigned y, Strategy* s) {
		Position p(x, y);

		int place = y + (x * __width);
		__grid[place] = new Strategic(*this, p, STARTING_AGENT_ENERGY, s);
	}

	void Game::addFood(const Position& position) {
		int place = position.y + (position.x * __width);

		__grid[place] = new Food(*this, position, STARTING_RESOURCE_CAPACITY);
	}

	void Game::addFood(unsigned x, unsigned y) {
		Position p(x, y);

		int place = y + (x * __width);
		__grid[place] = new Food(*this, p, STARTING_RESOURCE_CAPACITY);
	}

	void Game::addAdvantage(const Position& position) {
		int place = position.y + (position.x * __width);

		__grid[place] = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
	}

	void Game::addAdvantage(unsigned x, unsigned y) {
		Position p(x, y);

		int place = y + (x * __width);
		__grid[place] = new Advantage(*this, p, STARTING_RESOURCE_CAPACITY);
	}

	const Surroundings Game::getSurroundings(const Position& pos) const {
		Surroundings s; //makes an array

		for (int i = 0; i < 9; ++i) { //fill array
			if (i == 4)
				s.array[4] = SELF; //puts self in the middle
			else
				s.array[i] = EMPTY;
		}

		int x = pos.x - 1, y = pos.y - 1;
		PieceType type;
		int total = 0;

		for (int row = 0; row < 3; ++row) {
			for (int col = 0; col < 3; ++col) {
				//the point is out of the grid
				if ((x < 0 || x > __width - 1) || (y < 0 || y > __height - 1)) {
					s.array[row + (col * __width)] = INACCESSIBLE;
				}
				else {
					if (__grid[col + (row * 3)] != nullptr) {// checks if position has something
						type = __grid[row + (col * 3)]->getType();
						s.array[row + (col * 3)] = type;
					}
					else
						s.array[col + (row * 3)] = EMPTY;
				}
				x++;
				++total;
			}
			x = pos.x - 1;//resets x
			y++; //goes to tnext row
		}

		return s;
	}

	const ActionType Game::reachSurroundings(const Position& from, const Position& to) {
		if (from.x == to.x && from.y == from.x)
			return STAY;
		
		if (to.x == from.x - 1 && to.y == from.y - 1)
			return NW;
		else if (to.x == from.x && to.y == from.y == to.y - 1)
			return N;
		else if (to.x == from.y + 1 && to.y == from.y - 1)
			return NE;
		else if (to.x == from.x - 1 && to.y == from.y)
			return W;
		else if (to.x == from.x + 1 && to.y == from.y)
			return E;
		else if (to.x == from.x - 1 && to.y == from.y + 1)
			return SW;
		else if (to.x == from.x && to.y == from.y + 1)
			return S;
		else if (to.x == from.x + 1 && to.y == from.y + 1)
			return SE;
	}

	bool Game::isLegal(const ActionType& ac, const Position& pos) const {
		Surroundings s;
		s = getSurroundings(pos);
		bool legal = true;

		switch (ac) {
		case N:
			if (s.array[1] != INACCESSIBLE) legal = true;
			break;
		case NE:
			if (s.array[2] != INACCESSIBLE) legal = true;
			break;
		case NW:
			if (s.array[0] != INACCESSIBLE) legal = true;
			break;
		case E:
			if (s.array[5] != INACCESSIBLE) legal = true;
			break;
		case W:
			if (s.array[3] != INACCESSIBLE) legal = true;
			break;
		case SE:
			if (s.array[8] != INACCESSIBLE) legal = true;
			break;
		case SW:
			if (s.array[6] != INACCESSIBLE) legal = true;
			break;
		case S:
			if (s.array[7] != INACCESSIBLE) legal = true;
			break;
		case STAY:
			legal = true;
			break;
		}
		return legal;
	}

	const Position Game::move(const Position& pos, const ActionType& ac) const {

		Position p(pos.x, pos.y);

		if (isLegal(ac, pos)) {

			switch (ac) {
			case N:
				p.y--;
				break;
			case NE:
				p.y--;
				p.x++;
				break;
			case NW:
				p.y--;
				p.x--;
				break;
			case W:
				p.x--;
				break;
			case E:
				p.x++;
				break;
			case S:
				p.y++;
				break;
			case SE:
				p.y++;
				p.x++;
				break;
			case SW:
				p.y++;
				p.x--;
				break;
			case STAY:
				//nothing because we are staying
				break;
				
			}

		}


		return p;
	}

	void Game::round() {
		std::set<Piece*> board;
		Position pos, New;
		ActionType move;
		Piece* pptr;
		int place;

		for (auto it = __grid.begin(); it < __grid.end(); ++it) {
			if (*it != nullptr) {
				board.insert(*it);
				(*it)->setTurned(false);//resets the pieces of not doing turn yet
			}
		}

		for (auto it = board.begin(); it != board.end(); ++it) {

			if ((*it)->isViable()) {
				(*it)->age();
				(*it)->setTurned(true);
				
				pos = (*it)->getPosition();//puts pieces position in a variable
				move = (*it)->takeTurn(getSurroundings(pos)); //takes the pieces turn

				New = this->move(pos, move);//get's the new position of the piece
				place = New.x + (New.y * __width);

				pptr = __grid[place];

				if (pptr != nullptr) {//there is a piece at position it wants to move

					(*(*it) * *pptr);//the pieces interact

					if ((*it)->isViable()) {//didn't get consumed
						(*it)->setPosition(New);

						//change the board
						__grid[New.x + (New.y * __width)] = *it;
						__grid[pos.x + (pos.y * __width)] = nullptr;
					}
					else {//piece got consumed
						__grid[pos.x + (pos.y * __width)] = nullptr;
					}
				}
				else {//space is empty
					__grid[New.x + (New.y * __width)] = *it;
				}
			}
		}//end of the loop

		for (int i = 0; i < __grid.size(); ++i) {
			if (!__grid[i]->isViable() && __grid[i] != nullptr) {
				delete __grid[i];
				__grid[i] = nullptr;
			}
		}

		if (getNumResources() == 0)
			this->__status = OVER;

	}

	void Game::play(bool verbose) {
		__status = PLAYING;
		//verbose means to show what's going on
		__verbose = verbose;

		//print starting corridants of pieces
		if(__verbose)
			std::cout << this;

		while (__status != OVER) {//start the game!!!
			round();

			if (__verbose)//if true shows the host what is going on in the game
				std::cout << this;
		}

		//print final corrdinants of piecs
		if (__verbose)
			std::cout << this;
	}

	std::ostream& operator<<(std::ostream& os, const Game& game) {
		int x = game.__width, y = game.__height;
		
		os << "Round: " << game.__round << std::endl;
		for (int i = 0; i < y; ++i) {
			for (int j = 0; j < x; ++j) {
				if (game.__grid[j + (i * (game.__width - 1))] == nullptr)
					os << "[     ]";
				else
					os << std::setw(5) << game.__grid[j + (i * (game.__width - 1))] << "]";
			}
			os << std::endl;
		}
		os << "Status: " << game.getStatus() << std::endl;

		return os;
	}
}