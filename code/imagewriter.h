#include "triangle.h"

#include <vector>
//#include <iostream>
//#include <chrono>
//#include <ctime>
#include <fstream>
#include <math.h>

using namespace std;

void setPixel(int x, int y, int** image, int v) {
	image[y][x] = v;
}
void setPixel(int x, int y, int** image) {
	setPixel(x, y, image, 0);
}
void setEdge(Edge e, int** image, int v) {
	if(e.p1.x > e.p2.x) {
		e.flip();
	}

	double dx = e.p2.x - e.p1.x;
	double dy = e.p2.y - e.p1.y;

	if(dx == 0) {
		double x = e.p1.x;
		double y = e.p1.y;
		for(int a = 0; a < abs(dy); a++) {
				setPixel((int) (x+(dx/dy)*a), (int) (y+(dy/abs(dy))*a), image);
		}
	} else if(dy/dx == 1) {
		double x = e.p1.x;
		double y = e.p1.y;
		for(int a = 0; a < dx; a++) {
				setPixel((int) (x+(dx/dx)*a), (int) (y+(dy/dx)*a), image);
		}
	} else if(dy/dx == -1) {
		double x = e.p1.x;
		double y = e.p1.y;
		for(int a = 0; a < dx; a++) {
			setPixel((int) (x+(dx/dx)*a), (int) (y+(dy/dx)*a), image);
		}
	} else if(abs(dy/dx) < 1) {
		double x = e.p1.x;
		double y = e.p1.y;
		for(int a = 0; a < dx; a++) {
			setPixel((int) (x+(dx/dx)*a), (int) (y+(dy/dx)*a), image);
		}
	}
	else {
		if(e.p1.y > e.p2.y) {
			e.flip();
			dx = e.p2.x - e.p1.x;
			dy = e.p2.y - e.p1.y;
		}
		if(abs(dy/dx) > 1) {
			double x = e.p1.x;
			double y = e.p1.y;
			for(int a = 0; a < dy; a++) {
				setPixel((int) (x+(dx/dy)*a), (int) (y+(dy/dy)*a), image);
			}
		}
	}
}
void setVertex(int x, int y, int width, int** image, int minx, int maxx, int miny, int maxy) {
	int d = (width/2 + (1 - width%2));
	int sx = max(x - d, minx);
	int ex = min(x + d, maxx-1);
	int sy = max(y - d, miny);
	int ey = min(y + d, maxy-1);
	for(int a = sy; a < ey; a++) {
		for(int b = sx; b < ex; b++) {
			setPixel(b, a, image);
		}
	}
}
int** initialize(int x, int y, vector<Triangle> triangulation) {
	int** image = new int*[y];

	for(int a = 0; a < y; a++)
		image[a] = new int[x];

	for(int a = 0; a < y; a++)
		for(int b = 0;  b < x; b++)
			image[a][b] = 1;

	for(Triangle t : triangulation) {
		for(Edge e : t.edges()) {
			setEdge(e, image, 0);
		}
		for(Vertex v : t.vertices()) {
			setVertex(v.x, v.y, 7, image, 20, 780, 20, 580);
		}
	}
	return image;
}
int** createEdgeTest(int x, int y) {
	int** image = new int*[y];

	for(int a = 0; a < y; a++)
		image[a] = new int[x];

	for(int a = 0; a < y; a++)
		for(int b = 0; b < x; b++)
			image[a][b] = 1;

	Vertex mid(150, 150);
	Edge e(Vertex(100, 100), mid);
	setEdge(e, image, 0);
	
	e = Edge(Vertex(150, 100), mid);
	setEdge(e, image, 0);
	
	e = Edge(Vertex(200, 100), mid);
	setEdge(e, image, 0);
	
	e = Edge(Vertex(200, 150), mid);
	setEdge(e, image, 0);
	
	e = Edge(Vertex(200, 200), mid);
	setEdge(e, image, 0);
	
	e = Edge(Vertex(150, 200), mid);
	setEdge(e, image, 0);
	
	e = Edge(Vertex(100, 200), mid);
	setEdge(e, image, 0);
	
	e = Edge(Vertex(100, 150), mid);
	setEdge(e, image, 0);
	

	e = Edge(Vertex(125, 100), mid);
	setEdge(e, image, 0);
	
		e = Edge(Vertex(175, 100), mid);
		setEdge(e, image, 0);
		
	e = Edge(Vertex(200, 125), mid);
	setEdge(e, image, 0);
	
	e = Edge(Vertex(200, 175), mid);
	setEdge(e, image, 0);
	
	e = Edge(Vertex(175, 200), mid);
	setEdge(e, image, 0);
	
		e = Edge(Vertex(125, 200), mid);
		setEdge(e, image, 0);
		
	e = Edge(Vertex(100, 175), mid);
	setEdge(e, image, 0);
	
	e = Edge(Vertex(100, 125), mid);
	setEdge(e, image, 0);

	return image;
}
void savetoImage(vector<Triangle> triangulation) {
	int x = 800; int y = 600;
	int** image = initialize(x, y, triangulation);
	string filename("output.pbm");
	//int** image = createEdgeTest(x, y);
	//string filename("edgetest.pbm");
	
	fstream file;
	file.open(filename, fstream::out);

	file << "P1\n";
	file << x << " " << y << "\n";
	
	for(int a = 0; a < y; a++) {
		for(int b = 0; b < x; b++) {
			file << image[a][b] << " ";
			if(b%76 == 0 && b != 0)
				file << "\n";
		}
		file << "\n";
	}
	file.close();
}
