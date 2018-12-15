#include "edge.h"

//----------------------
// Constructors
//----------------------
Edge::Edge() {

}
Edge::Edge(const Vertex& _p1, const Vertex& _p2) {
	p1 = _p1;
	p2 = _p2;
}
Edge::Edge(const Edge& e) {
	p1 = e.p1;
	p2 = e.p2;
	isBad = e.isBad;
}

/*Vertex Edge::midpoint() const {

}*/

//----------------------
// Math
//----------------------
float Edge::length() const {
	return p1.dist(p2);
}
void Edge::flip() {
	Vertex temp(p1);
	p1 = p2;
	p2 = temp;
}

//----------------------
// Operators
//----------------------
Edge& Edge::operator=(const Edge& e) {
	p1 = e.p1;
	p2 = e.p2;
	isBad = e.isBad;
	return *this;
}

bool Edge::operator ==(const Edge& e) const {
	return ((p1 == e.p1) && (p2 == e.p2)) || ((p1 == e.p2) && (p2 == e.p1));
}
std::ostream& operator<<(std::ostream& os, const Edge& e) {
	os << "[" << e.p1 << "," << e.p2 << "]";
	return os;
}
