#pragma once
class Vector
{
public:
	Vector();
	~Vector();

	void setRichting(double xIn, double yIn);

	double getLength();


	double x;
	double y;
};

