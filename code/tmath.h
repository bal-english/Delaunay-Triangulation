#ifndef TMATH_H
#define TMATH_H

#include "vertex.h"

// ax + by = c
void getLine(Vertex v1, Vertex v2, float& a, float& b, float& c) {
	a = v2.y - v1.y;
	b = v1.x - v2.x;
	c = a*v1.x + b*v1.y;
}

void getBisectorFromLine(Vertex v1, Vertex v2, float& a, float& b, float& c) {
	Vertex mid((v1.x+v2.x)/2, (v1.y + v2.y)/2);

	// c = -bx + ay
	c =  -b*(mid.x) + a*(mid.y);

	float temp = a;
	a = -b;
	b = temp;
}

Vertex lineIntersection(float a1, float b1, float c1, float a2, float b2, float c2) {
	float determinant = a1*b2 - a2*b1;
	if(determinant == 0)
		throw std::invalid_argument("ERR: Lines are parrallel");

	double x = (b2*c1 - b1*c2)/determinant;
	double y = (a1*c2 - a2*c1)/determinant;
	return Vertex(x, y);
}

#endif
