#include "triangle.h"
#include "testing.h"
#include "graphics.h"
#include "SFML/Graphics.hpp"

#include <vector>
#include <iostream>

#include "delcalc.h"

using namespace std;

int main(int argc, char* argv[]) {
	int vertcount = 5;
	if(argc < 2) {
		cout << "Vertex count not specified. Using default: " << vertcount << endl;
	} else
		vertcount = stoi(argv[1]);
	
	cout << "Generating a random set of " << vertcount << " points..." << endl;
	std::vector<Vertex> vertices = randomPointSet(vertcount);
	
	std::vector<Triangle> triangulation;
	cout << "Attempting to calculate the set's Delaunay triangulation..." << endl;
	try {
		triangulation = triangulate(vertices);
	} catch (ColinearPointException cpe) {
		cout << "\tERR: The randomly generated point set does not have a valid Delaunay triangulation due to having colinear points. Please try rerunning the program to get a new point set. (If this keeps occuring, you can lower the number of points you are trying to generate)." << endl;
		return 0;
	}
	cout << "Triangulation successfully calculated" << endl;
	
	// Create new application window
	sf::RenderTexture rt;
	rt.create(800, 600);
	initializeScreen(rt);
	
	// Draw the Structure
	drawStructure(rt, triangulation);
	
	// Display the Structure
	cout << "Displaying the structure in the application window. Press Alt-F4 to quit." << endl;
	displayScreen(rt);
	cout << "Application Closed." << endl;
}
