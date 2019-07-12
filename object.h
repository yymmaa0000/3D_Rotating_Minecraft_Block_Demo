#pragma once
#include "fssimplewindow.h"
#include "camera.h"
#include <ctype.h>
#include <stdio.h>
#include "yspng.h"

enum Position{
	XY,XZ,YZ
};

struct Square {
	double centerx, centery, centerz;
	double width;
	double x[4], y[4], z[4];
	Square();
	Square(double cx, double cy, double cz, double width2, Position p);
	void draw(Camera camera);
};

struct Cube {
	double centerx, centery, centerz;
	Square face[6];
	double width;
	Cube();
	void draw(Camera camera);
};

struct Plank : Cube {
	YsRawPngDecoder png[1];
	GLuint texId[1];  // this will be use as texture identifiers for the two PNGs
	Plank();
	void draw(Camera camera);
};