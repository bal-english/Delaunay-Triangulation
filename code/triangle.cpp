#include "triangle.h"
#include "tmath.h"

//----------------------
// Constructors
//----------------------
Triangle::Triangle() {
	p1 = Vertex();
	p2 = Vertex();
	p3 = Vertex();

	e1 = Edge(p1, p2);
	e2 = Edge(p2, p3);
	e3 = Edge(p3, p1);
}
Triangle::Triangle(const Vertex& _p1, const Vertex& _p2, const Vertex& _p3) {
	p1 = _p1;
	p2 = _p2;
	p3 = _p3;

	e1 = Edge(_p1, _p2);
	e2 = Edge(_p2, _p3);
	e3 = Edge(_p3, _p1);
}

//----------------------
// Math
//----------------------
Vertex Triangle::circumCenter() const {
	float a, b, c;
	getLine(p1, p2, a, b, c);

	float d, e, f;
	getLine(p2, p3, d, e, f);

	getBisectorFromLine(p1, p2, a, b, c);
	getBisectorFromLine(p2, p3, d, e, f);
	
	Vertex center;
	try {
		center = lineIntersection(a, b, c, d, e, f);
	} catch (std::invalid_argument e) {
		throw ColinearPointException(p1, p2, p3);
	}

	return center;
}
bool Triangle::circleContains(const Vertex& _v) const {
	Vertex cCenter(circumCenter());
	const float radius = p1.dist(cCenter);
	const float dist = _v.dist(cCenter);
	return dist <= radius;
}

/*bool Triangle::contains(const Vertex& _v) const {
	return ((p1 == _v) || (p2 == _v) || (p3 == _v));
}

bool Triangle::contains(const Edge& _e) const {
	return ((e1 == _e) || (e2 == _e) || (e3 == _e));
}*/

//----------------------
// Scanning
//----------------------
bool Triangle::has(const Vertex& v) const {
	return (p1 == v) || (p2 == v) || (p3 == v);
}
bool Triangle::has(const Edge& e) const {
	return (e1 == e) || (e2 == e) || (e3 == e);
}
std::vector<Edge> Triangle::edges() {
	std::vector<Edge> es;
	es.push_back(e1);
	es.push_back(e2);
	es.push_back(e3);
	return es;
}
std::vector<Vertex> Triangle::vertices() {
	std::vector<Vertex> vs;
	vs.push_back(p1);
	vs.push_back(p2);
	vs.push_back(p3);

	return vs;
}
void Triangle::setBad() {
	isBad = true;
	e1.isBad = true;
	e2.isBad = true;
	e3.isBad = true;
}

//----------------------
// Operators
//----------------------
bool Triangle::operator==(const Triangle& t) const {
	return
			(t.has(p1) && t.has(p2) && t.has(p3)) &&
			(t.has(e1) && t.has(e2) && t.has(e3));
}
bool Triangle::operator!=(const Triangle& t) const {
	return !(*this == t);
}
std::ostream& operator<<(std::ostream& os, const Triangle& t) {
	os << "(" << t.p1 << "," << t.p2 << "," << t.p3;
	return os;
}
