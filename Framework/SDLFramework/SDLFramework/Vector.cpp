#include "Vector.h"
#include <cmath>


Vector::Vector()
{
}


Vector::~Vector()
{
}

void Vector::setRichting(double xIn, double yIn)
{
	x = xIn;
	y = yIn;
}

double Vector::getLength() {
	double lengte = sqrt((std::pow(x, 2) + std::pow(y, 2)));
	return lengte;
}

