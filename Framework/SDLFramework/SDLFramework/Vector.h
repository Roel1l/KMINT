#pragma once
class Vector
{
public:
	Vector() { x = 0, y = 0; }
	~Vector();

	void setRichting(double xIn, double yIn);

	double getLength();


	double x;
	double y;
};

