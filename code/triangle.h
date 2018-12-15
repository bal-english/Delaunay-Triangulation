#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cmath>
#include <limits>
#include <algorithm>
#include <iostream>
#include <vector>
#include "edge.h"
#include "delexcept.h"

class Triangle {
public:
	Vertex p1;
	Vertex p2;
	Vertex p3;
	Edge e1;
	Edge e2;
	Edge e3;
	bool isBad = false;

	Triangle();
	Triangle(const Vertex&, const Vertex&, const Vertex&);
	Vertex circumCenter() const;
	bool circleContains(const Vertex&) const;
	//bool contains(const Vertex&) const;
	//bool contains(const Edge&) const;
	bool has(const Vertex&) const;
	bool has(const Edge&) const;
	std::vector<Edge> edges();
	std::vector<Vertex> vertices();
	void setBad();
	bool operator==(const Triangle&) const;
	bool operator!=(const Triangle&) const;
	friend std::ostream& operator<<(std::ostream&, const Triangle&);
};

#endif
