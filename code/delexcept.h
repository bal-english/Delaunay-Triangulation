#ifndef DELEXCEPT_H
#define DELEXCEPT_H

#include <string>
#include "vertex.h"

class DelaunayException : public std::exception {
	protected:
		std::string message;
		
	public:
		DelaunayException(const std::string& str) {
			message = str;
		}
		virtual const char* what() const throw() {
			return message.c_str();
		}
};

class ColinearPointException : public DelaunayException {
	protected:
		Vertex v1;
		Vertex v2;
		Vertex v3;
		
		std::string pointlist;
		
	public:
		ColinearPointException(const Vertex& p1, const Vertex& p2, const Vertex& p3) : DelaunayException("") {
			v1 = p1;
			v2 = p2;
			v3 = p3;
			pointlist = "[" + ("(" + std::to_string(v1.x) + "," + std::to_string(v1.y) + "), ") + ("(" + std::to_string(v2.x) + "," + std::to_string(v2.y) + "), ") + ("(" + std::to_string(v3.x) + "," + std::to_string(v3.y) + ")") + "]";
			message = "ERR: The Vertices: " + pointlist + " are colinear. A Delaunay triangulation cannot be calculated for the given set of points.";
		}
};
#endif
