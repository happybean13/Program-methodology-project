#pragma once
#include <GL/glut.h>
#include "Square.h"

class Fill : public Square {
public:
	Fill(int x, int y);
	~Fill();
	virtual void draw() const;


};