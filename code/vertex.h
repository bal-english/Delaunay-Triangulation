#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <cmath>
#include <limits>
#include <algorithm>
#include <iostream>

class Vertex {
public:
	float y;
	float x;

	Vertex();
	Vertex(float, float);
	Vertex(const Vertex&);
	//void set(float, float);
	float rawdist(const Vertex&) const;
	float dist(const Vertex&) const;
	float square() const;
	void print() const;
	Vertex& operator=(const Vertex&);
	bool operator==(const Vertex&) const;
	friend std::ostream& operator<<(std::ostream&, const Vertex&);
};

#endif