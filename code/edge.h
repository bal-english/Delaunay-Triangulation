#ifndef EDGE_H
#define EDGE_H

#include "vertex.h"
#include <cmath>
#include <limits>
#include <algorithm>

class Edge {
public:
	Vertex p1;
	Vertex p2;
	bool isBad = false;

	Edge();
	Edge(const Vertex&, const Vertex&);
	Edge(const Edge&);
	//Vertex midpoint() const;
	float length() const;
	void flip();
	Edge& operator=(const Edge& v);
	bool operator==(const Edge& v) const;
	friend std::ostream& operator<<(std::ostream&, const Edge&);
};

#endif
