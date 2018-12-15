#ifndef TESTING_H
#define TESTING_H

#include <vector>
#include "triangle.h"
#include <ctime>

const int default_window_dimension_x = 800;
const int default_window_dimension_y = 600;
const int default_window_border = 20;

std::vector<Vertex> randomPointSet(const int n) {
	
	const int xmin = default_window_border;
	const int ymin = default_window_border;
	const int xmax = default_window_dimension_x - default_window_border;
	const int ymax = default_window_dimension_y - default_window_border;
	
	std::srand(time(NULL));
	
	std::vector<Vertex> v;
	for(int a = 0; a < n; a++)
		v.push_back(Vertex((rand()%(xmax+1-xmin))+xmin, (rand()%(ymax+1-ymin))+ymin));
	return v;
}
std::vector<Vertex> basicDegenerateCase() {
	const int centerx = default_window_dimension_x/2;
	const int centery = default_window_dimension_y/2;
	const int dx = default_window_dimension_x/8;
	const int dy = default_window_dimension_y/8;
	
	std::vector<Vertex> v;
	v.push_back(Vertex(centerx + dx, centery + dy));
	v.push_back(Vertex(centerx - dx, centery + dy));
	v.push_back(Vertex(centerx - dx, centery - dy));
	v.push_back(Vertex(centerx + dx, centery - dy));
	
	return v;
}
// Basic Triangle
std::vector<Vertex> sampleTrianglePointSet() {
	std::vector<Vertex> v;
	v.push_back(Vertex(250, 100));
	v.push_back(Vertex(550, 100));
	v.push_back(Vertex(400, 500));
	
	return v;
}
std::vector<Vertex> basicExamplePointSet() {
	std::vector<Vertex> v;
	v.push_back(Vertex(150, 475));
	v.push_back(Vertex(650, 475));
	v.push_back(Vertex(400, 125));
	v.push_back(Vertex(300, 425));
	v.push_back(Vertex(425, 225));
	
	return v;
}

#endif
