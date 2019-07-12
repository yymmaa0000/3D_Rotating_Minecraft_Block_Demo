#include "object.h"
#include <iostream>

using namespace std;

Square::Square()
{
	centerx = centery = centerz = z[0] = z[1] = z[2] = z[3] = 0;
	width = WINDOW_X;
	x[0] = width / 2;
	x[1] = width / 2;
	x[2] = -width / 2;
	x[3] = -width / 2;
	y[0] = width / 2;
	y[1] = -width / 2;
	y[2] = -width / 2;
	y[3] = width / 2;
}

Square::Square(double cx, double cy, double cz, double width2, Position p)
{
	centerx = cx;
	centery = cy;
	centerz = cz;
	width = width2;
	switch (p) {
	case XY:
		x[0] = width / 2;
		x[1] = width / 2;
		x[2] = -width / 2;
		x[3] = -width / 2;
		y[0] = width / 2;
		y[1] = -width / 2;
		y[2] = -width / 2;
		y[3] = width / 2;
		z[0] = z[1] = z[2] = z[3] = cz;
		break;
	case XZ:
		x[0] = width / 2;
		x[1] = width / 2;
		x[2] = -width / 2;
		x[3] = -width / 2;
		z[0] = width / 2;
		z[1] = -width / 2;
		z[2] = -width / 2;
		z[3] = width / 2;
		y[0] = y[1] = y[2] = y[3] = cy;
		break;
	case YZ:
		y[0] = width / 2;
		y[1] = width / 2;
		y[2] = -width / 2;
		y[3] = -width / 2;
		z[0] = width / 2;
		z[1] = -width / 2;
		z[2] = -width / 2;
		z[3] = width / 2;
		x[0] = x[1] = x[2] = x[3] = cx;
		break;
	}
}

void Square::draw(Camera camera)
{

	screen_coord proj[4];

	double distance = camera.get_distance(centerx, centery, centerz);
	if (distance < 0) return;

	for (int i = 0; i < 4; i++) {
		proj[i] = camera.project(x[i], y[i], z[i]);
	}
	
	//glColor3ub(255, 255, 255);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex2d(proj[0].x, proj[0].y);
	glTexCoord2d(1.0, 0.0);
	glVertex2d(proj[1].x, proj[1].y);
	glTexCoord2d(1.0, 1.0);
	glVertex2d(proj[2].x, proj[2].y);
	glTexCoord2d(0.0, 1.0);
	glVertex2d(proj[3].x, proj[3].y);
	glEnd();
	/*
	glColor3ub(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(proj[0].x, proj[0].y);
	glVertex2d(proj[1].x, proj[1].y);
	glVertex2d(proj[2].x, proj[2].y);
	glVertex2d(proj[3].x, proj[3].y);
	glEnd();
	*/

}

Cube::Cube()
{
	centerx = centery = centerz = 0;
	width = WINDOW_X;
	face[0] = Square(width/2, 0.0, 0.0, width, YZ);
	face[1] = Square(-width/2, 0.0, 0.0, width, YZ);
	face[2] = Square(0.0, width/2,  0.0, width, XZ);
	face[3] = Square(0.0, -width/2, 0.0, width, XZ);
	face[4] = Square(0.0, 0.0, width/2, width, XY);
	face[5] = Square(0.0, 0.0, -width/2, width, XY);
}

void Cube::draw(Camera camera)
{
	double distance[6];

	for (int i = 0; i < 6; i++) {
		distance[i] = camera.get_distance(face[i].centerx, face[i].centery, face[i].centerz);
	}

	double max;
	int max_index;
	for (int i = 0; i < 6; i++) {
		max = 0.0;
		max_index = 0;
		for (int k = 0; k < 6; k++) {
			if (distance[k] > max) {
				max = distance[k];
				max_index = k;
			}
		}
		distance[max_index] = -1;
		if (i < 2) continue;
		else face[max_index].draw(camera);
	}

}

Plank::Plank()
{
	/*
	png[0].Decode("Planks.png");

	// glGenTextures(2,texId);  // You can also reserve two texture identifies with one call this way.

	glGenTextures(1, &texId[0]);  // Reserve one texture identifier
	glBindTexture(GL_TEXTURE_2D, texId[0]);  // Making the texture identifier current (or bring it to the deck)

	// set up parameters for the current texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D
	(GL_TEXTURE_2D,
		0,    // Level of detail
		GL_RGBA,
		png[0].wid,
		png[0].hei,
		0,    // Border width, but not supported and needs to be 0.
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		png[0].rgba);
		*/
}

void Plank::draw(Camera camera)
{
	double max, distance [6];
	int max_index;
	for (int i = 0; i < 6; i++) {
		distance[i] = camera.get_distance(face[i].centerx, face[i].centery, face[i].centerz);
	}
	

	png[0].Decode("Rock.png");

	// glGenTextures(2,texId);  // You can also reserve two texture identifies with one call this way.

	glGenTextures(1, &texId[0]);  // Reserve one texture identifier
	glBindTexture(GL_TEXTURE_2D, texId[0]);  // Making the texture identifier current (or bring it to the deck)

	// set up parameters for the current texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D
	(GL_TEXTURE_2D,
		0,    // Level of detail
		GL_RGBA,
		png[0].wid,
		png[0].hei,
		0,    // Border width, but not supported and needs to be 0.
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		png[0].rgba);

	for (int i = 0; i < 6; i++) {
		int wid, hei;
		FsGetWindowSize(wid, hei);

		// in order for textures to show, you must create a projection
		glViewport(0, 0, wid, hei);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glColor4d(1.0, 1.0, 1.0, 1.0);

		// enable texture mapping
		glEnable(GL_TEXTURE_2D);

		// bind a texture to OpenGL primitives
		glBindTexture(GL_TEXTURE_2D, texId[0]);

		max = 0.0;
		max_index = 0;
		for (int k = 0; k < 6; k++) {
			if (distance[k] > max) {
				max = distance[k];
				max_index = k;
			}
		}
		distance[max_index] = -1;
		if (i < 2) continue;
		else face[max_index].draw(camera);
	}
}
