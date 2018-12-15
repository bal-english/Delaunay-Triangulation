#ifndef DELCALC_H
#define DELCALC_H

#include <vector>
#include "triangle.h"

void calcSuperDimensions(std::vector<Vertex> vertices, float& deltaMax, float& midx, float& midy) {
	float minx = vertices[0].x;
	float miny = vertices[0].y;
	float maxx = minx;
	float maxy = miny;

	for(auto p = vertices.begin(); p != vertices.end(); p++) {
		if(p->x < minx)
			minx = p->x;
		if(p->x > maxx)
			maxx = p->x;
		if(p->y < miny)
			miny = p->y;
		if(p->y > maxy)
			maxy = p->y;
	}

	float dx = maxx - minx;
	float dy = maxy - miny;
	deltaMax = std::max(dx, dy);
	midx = 0.5f*(minx + maxx);
	midy = 0.5f*(miny + maxy);
}
Triangle calcSuperTriangle(std::vector<Vertex> vertices) {
	int mult = 20;
	float deltaMax;
	float midx;
	float midy;
	calcSuperDimensions(vertices, deltaMax, midx, midy);
	return Triangle(Vertex(midx - mult*deltaMax, midy - deltaMax), Vertex(midx, midy + mult*deltaMax), Vertex(midx + mult*deltaMax, midy - deltaMax));
}

std::vector<Triangle> triangulate(std::vector<Vertex> vertices) {
	std::vector<Triangle> triangulation;
	if(vertices.size() == 3) {
		// Add edge case if points are all parallel in a line
		Triangle t(vertices[0], vertices[1], vertices[2]);
		triangulation.push_back(t);
		return triangulation;
	}
	Triangle super(calcSuperTriangle(vertices));
	triangulation.push_back(super);
	for(Vertex& v : vertices) {
		std::vector<Triangle> badts;
		for(Triangle& t : triangulation) {
			if(t.circleContains(v)) {
				t.setBad();
				badts.push_back(t);
			}
		}

		std::vector<Edge> polygon;
		for(Triangle& t : badts) {
			if(badts.size() == 1) {
				for(Edge e : t.edges()) {
					polygon.push_back(e);
				}
			}
			else {
				for(Edge& e : t.edges()) {
					bool shared = false;
					// Check if Shared
					for(Triangle& t2 : badts) {
						if(t != t2) {
							if(t2.has(e)) {
								shared = true;
							}
						}
					}
					if(!shared) {
						polygon.push_back(e);
					}
				}
			}
		}


		std::vector<Triangle> newtriangulation;
		for(Triangle& t : triangulation) {
			bool bad = t.isBad;
			if(!t.isBad) {
				newtriangulation.push_back(t);
			}
		}
		triangulation = newtriangulation;
		newtriangulation.clear();

		for(Edge& e : polygon) {
			Triangle t(e.p1, e.p2, v);
			triangulation.push_back(t);
		}
	}
	std::vector<Triangle> newtriangulation;
	for(Triangle& t : triangulation) {
		if(!(t.has(super.p1) || t.has(super.p2) || t.has(super.p3))) {
			newtriangulation.push_back(t);
		}
	}
	triangulation = newtriangulation;
	return triangulation;
}

#endif
