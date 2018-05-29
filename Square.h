#pragma once

/* Implement: Define Quad class */

#include <GL/glut.h>
#include "Color.h"
#include "Quad.h"

class Square : public Quad, public Color {

public:
	Square(int x, int y, float r, float g, float b, int sl);
	~Square();
	virtual void draw() const;
	int getSideLength() const;
protected:
	int  side_length;
};