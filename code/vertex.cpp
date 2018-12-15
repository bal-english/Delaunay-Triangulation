#include "vertex.h"

//----------------------
// Constructors
//----------------------
Vertex::Vertex() {
	x = 0;
	y = 0;
}
Vertex::Vertex(float _x, float _y) {
	x = _x;
	y = _y;
}
Vertex::Vertex(const Vertex& v) {
	x = v.x;
	y = v.y;
}

/*void Vertex::set(float _x, float _y) {
	x = _x;
	y = _y;
}*/

//----------------------
// Math
//----------------------
float Vertex::rawdist(const Vertex& v) const {
	float dx = x - v.x;
	float dy = y - v.y;
	return dx * dx + dy * dy;
}
float Vertex::dist(const Vertex& v) const {
	return sqrt(rawdist(v));
}
float Vertex::square() const {
	return x * x + y * y;

}

//----------------------
// Debug Info
//----------------------
void Vertex::print() const {
	std::cout << "(" << x << "," << y << ")" << std::endl;
}

//----------------------
// Operators
//----------------------
Vertex& Vertex::operator=(const Vertex& v) {
	x = v.x;
	y = v.y;
	return *this;
}
bool Vertex::operator==(const Vertex& v) const {
	return ((x == v.x) && (y == v.y));
}
std::ostream& operator<<(std::ostream& os, const Vertex& v){
	os << "(" << v.x << "," << v.y << ")";
	return os;
}
