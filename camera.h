#pragma once
#include <math.h>

#define WINDOW_X 1024.
#define WINDOW_Y 768.
#define PI 3.1415927
#define CAMERA_ANGLE 30.

struct screen_coord {
	double x, y, scale;
	screen_coord() { x = y = scale = 0; }
};

class Camera {
	double x, y, z, r, theta;
	double front[3];
	double left[3];
	double up[3];
	double norm(const double vector[3]);
	void normalize(double vector[3]);
	void cross_product(double x[3], double y[3], double result[3]);
	void face_origin();
public:
	Camera();
	double get_distance(double x2, double y2, double z2);
	double get_scale(double distance);
	screen_coord project(double x2, double y2, double z2);
	void move();
};
