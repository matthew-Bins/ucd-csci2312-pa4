#include"Exceptions.h"
#include<string>

namespace Gaming {

	///////////////////////////////Base Game Exceptions//////////////////////////////////
	void GamingException::setName(std::string name) { __name = name; }
	std::ostream& operator<<(std::ostream& os, const GamingException& ex) {
		ex.__print_args(os);
		return os;
	}

	//////////////////////////////game base Dimension Exception////////////////////////////
	DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height) {
		__exp_width = expWidth;
		__exp_height = expHeight;
		__width = width;
		__height = height;
	}

	unsigned DimensionEx::getExpWidth() const { return __exp_width; }
	unsigned DimensionEx::getExpHeight() const { return __exp_height; }
	unsigned DimensionEx::getWidth() const { return __width; }
	unsigned DimensionEx::getHeight() const { return __height; }

	/////////////////////////game dimension Insufficient exception/////////////////////////
	InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned minWidth, unsigned minHeight, 
		unsigned width, unsigned height) : DimensionEx(minWidth, minHeight, width, height){
		setName("InsufficientDimensionsEx");
	}

	void InsufficientDimensionsEx::__print_args(std::ostream& os) const {
		os << getName() << ": " << getExpWidth() << ", " << getExpHeight() << ", " << getWidth() << ", "
			<< getHeight();
	}

	/////////////////////// game dimension OutOfBounds exception/////////////////////////////
	OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height) :
		DimensionEx(maxWidth, maxHeight, width, height) {
		setName("OutOfBoundsEx");
	}

	void OutOfBoundsEx::__print_args(std::ostream& os) const {
		os << getName() << ": " << getExpWidth() << ", " << getExpHeight() << ", " << getWidth() << ", "
			<< getHeight();
	}

	/////////////////////////// game base Position exception////////////////////////////////
	PositionEx::PositionEx(unsigned x, unsigned y) {
		__x = x;
		__y = y;
	}

	void PositionEx::__print_args(std::ostream& os) const {
		os << getName() << ": x =" << __x << ", y =" << __y;
	}

	/////////////////////////// game position PositionNonempty Exception////////////////////
	PositionNonemptyEx::PositionNonemptyEx(unsigned x, unsigned y) :
		PositionEx(x, y) {
		setName("PositionNonemptyEx");
	}

	///////////////////////// game position PositionEmpty exception//////////////////////
	PositionEmptyEx::PositionEmptyEx(unsigned x, unsigned y) :
		PositionEx(x, y) {
		setName("PositionEmptyEx");
	}

	/////////////////////// game PosVectorEmpty exception/////////////////////////////
	PosVectorEmptyEx::PosVectorEmptyEx() {
		setName("PosVectorEmptyEx");
	}

	void PosVectorEmptyEx::__print_args(std::ostream& os) const {
		os << getName();
	}
}