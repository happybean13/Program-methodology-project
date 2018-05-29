#pragma once
#include <GL/glut.h>
#include "Square.h"

class Player : public Square {
public:
	Player(int x, int y, float r, float g, float b, int sl);
	~Player();
	void move(int direction,int w, int h);
	int operator[](int i) {
		return center_pos[i];
	}


};