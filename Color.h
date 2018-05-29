#pragma once

/* Implement: Define Color class */

#include <GL/glut.h>

class Color {
public: 
	Color(float r, float g, float b);
	~Color();

	void setColor(float r, float g, float b);

protected:
	float color[3];
};