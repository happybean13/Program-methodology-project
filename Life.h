#pragma once

#include <GL/glut.h>
#include "Color.h"
#include "Quad.h"

class Life : public Quad, public Color {

public:
	Life(int x, int y, float r, float g, float b, int sl);
	~Life();
	virtual void draw() const;
	void move(int direction, int w, int h);
	int getSideLength() const;
protected:
	int  side_length;
};