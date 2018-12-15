#include "triangle.h"
#include "delcalc.h"
#include "testing.h"
#include "imagewriter.h"

#include <vector>
#include <iostream>

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
	
	cout << "Saving to: \'output.pbm\'" << endl; 
	savetoImage(triangulation);
}