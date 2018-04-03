#include "Vector.h"
#include <cmath>


Vector::~Vector()
{
}

void Vector::setRichting(double xIn, double yIn)
{
	x = xIn;
	y = yIn;
}

double Vector::getLength() {
	double length = sqrt((std::pow(x, 2) + std::pow(y, 2)));
	return length;
}

