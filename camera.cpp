#include "camera.h"
#include <iostream>

using namespace std;

double Camera::norm(const double vector[3])
{
	double result = 0;
	for (int i = 0; i < 3; i++) {
		result += vector[i] * vector[i];
	}
	return sqrt(result);
}

void Camera::normalize(double vector[3])
{
	double magnitude = norm(vector);
	for (int i = 0; i < 3; i++) {
		vector[i] /= magnitude;
	}
}

void Camera::cross_product(double x[3], double y[3], double result[3])
{
	result[0] = -x[2] * y[1] + x[1] * y[2];
	result[1] = x[2] * y[0] - x[0] * y[2];
	result[2] = -x[1] * y[0] + x[0] * y[1];
}

void Camera::face_origin()
{
	front[0] = -x;
	front[1] = -y;
	front[2] = -z;
	left[0] = -front[1];
	left[1] = front[0];
	left[2] = 0;
	cross_product(front, left, up);
	normalize(front);
	normalize(left);
	normalize(up);
}

Camera::Camera()
{
	x = r = z = WINDOW_X*2;
	y = 0;
	theta = 0;
	face_origin();
}

double Camera::get_distance(double x2, double y2, double z2)
{
	double distance = (x2 - x) * front[0] + (y2 - y) * front[1] + (z2 - z) * front[2];
	return distance;
}

double Camera::get_scale(double distance)
{
	if (distance < 0) return 0;
	double real_size = distance * tan(CAMERA_ANGLE / 180. * PI);
	double x_scale = WINDOW_X / (WINDOW_X + real_size);
	double y_scale = WINDOW_Y / (WINDOW_Y + real_size);
	if (x_scale < y_scale) return x_scale;
	else return y_scale;
}

screen_coord Camera::project(double x2, double y2, double z2)
{
	screen_coord result;
	double distance = get_distance(x2, y2, z2);
	if (distance < 0) return result;
	double scale = get_scale(distance);

	double screen_x = (x2 - front[0] * distance - x) * left[0] + (y2 - front[1] * distance - y) * left[1] + (z2 - front[2] * distance - z) * left[2];
	double screen_y = (x2 - front[0] * distance - x) * up[0] + (y2 - front[1] * distance - y) * up[1] + (z2 - front[2] * distance - z) * up[2];
	
	screen_x *= scale;
	screen_y *= scale;
	screen_x = -screen_x + WINDOW_X / 2.;
	screen_y = -screen_y + WINDOW_Y / 2.;

	result.x = screen_x;
	result.y = screen_y;
	result.scale = scale;
	return result;
}

void Camera::move()
{
	theta += 0.05;
	x = r * cos(theta);
	y = r * sin(theta);
	z = r * cos(theta) * 0.9 + r;
	face_origin();
}
