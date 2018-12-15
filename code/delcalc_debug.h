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
	std::cout << "Super Triangle: " << super << std::endl;
	triangulation.push_back(super);
	for(Vertex& v : vertices) {
		std::cout << "Adding Vertex: " << v << std::endl;
		std::vector<Triangle> badts;
		std::cout << "\tChecking Existing Triangles..." << std::endl;
		for(Triangle& t : triangulation) {
			std::cout << "\t\tTriangle: " << t << std::endl;
			if(t.circleContains(v)) {
				std::cout << "\t\tVertex: " << v << " is within the circumcircle. Adding it to bad triangles." << std::endl;
				t.setBad();
				badts.push_back(t);
			}
			else
				std::cout << "\t\tVertex: " << v << " is outside the circumcircle. Ignoring Triangle" << std::endl;
		}

		std::vector<Edge> polygon;
		std::cout << "\tChecking Bad Triangles for Shared Edges." << std::endl;
		for(Triangle& t : badts) {
			std::cout << "\t\tTriangle: " << t;
			if(badts.size() == 1) {
				std::cout << " is the only triangle. Its Edges cannot be shared. Adding them to them to the polygon." << std::endl;
				for(Edge e : t.edges()) {
					std::cout << "\t\t\tEdge: " << e << std::endl;
					polygon.push_back(e);
				}
			}
			else {
				std::cout << std::endl;
				for(Edge& e : t.edges()) {
					std::cout << "\t\t\tEdge: " << e << std::endl;
					std::cout << "\t\t\tLooping through other triangles." << std::endl;
					bool shared = false;
					// Check if Shared
					for(Triangle& t2 : badts) {
						std::cout << "\t\t\t\tTriangle t: " << t << std::endl << "\t\t\t\tTriangle t2: " << t2 << std::endl;
						if(t != t2) {
							if(t2.has(e)) {
								std::cout << "\t\t\t\t\tEdge: " << e << " is shared. Bool Updated";
								shared = true;
							}
						}
						else {
							std::cout << "\t\t\t\t\tTriangles are the same. Ignoring." << std::endl;
						}
					}
					std::cout << "\t\t\tEdge: " << e;
					if(!shared) {
						std::cout << " was not shared. Adding it to polygon." << std::endl;
						polygon.push_back(e);
					}
					else
						std::cout << " was shared. Ignoring." << std::endl;
					std::cout << std::endl;
				}
			}
		}


		std::vector<Triangle> newtriangulation;
		std::cout << "\tRemoving bad triangles..." << std::endl;
		for(Triangle& t : triangulation) {
			bool bad = t.isBad;
			std::cout << "\t\tTriangle: " << t;
			if(!t.isBad) {
				std::cout << " is not bad. Adding to the new set." << std::endl;
				newtriangulation.push_back(t);
			}
			else
				std::cout << " is bad. Ignoring." << std::endl;
		}
		std::cout << "\tUpdating triangulation." << std::endl;
		triangulation = newtriangulation;
		newtriangulation.clear();

		std::cout << "\tAdding new triangles formed from the new Vertex: " << v << " and edges in polygon." << std::endl;
		for(Edge& e : polygon) {
			std::cout << "\t\tEdge: " << e << std::endl;
			Triangle t(e.p1, e.p2, v);
			std::cout << "\t\t\tFormed Triangle: " << t << std::endl;
			triangulation.push_back(t);
		}
	}
	std::cout << "Removing any triangles with vertex from super triangle: " << super.p1 << ", " << super.p2 << ", " << super.p3 << std::endl;
	std::vector<Triangle> newtriangulation;
	for(Triangle& t : triangulation) {
		std::cout << "\tTriangle: " << t;
		if(!(t.has(super.p1) || t.has(super.p2) || t.has(super.p3))) {
			std::cout << " does not have a super vertex. Adding to new set." << std::endl;
			newtriangulation.push_back(t);
		} else
			std::cout << " has a shared super vertex. Ignoring... " << std::endl;
	}
	std::cout << "Updating triangle set." << std::endl;
	triangulation = newtriangulation;
	return triangulation;
}


#endif
