/* Implement: Define each function of quad class */

#include <iostream>
#include "Quad.h"

Quad::Quad(int x, int y) {
	center_pos[0] = x;
	center_pos[1] = y;
}

Quad::~Quad() {

}

void Quad::setPos(int x, int y) {
	center_pos[0] = x;
	center_pos[1] = y;
}

int Quad::getX() const {
	return center_pos[0];
}

int Quad::getY() const {
	return center_pos[1];
}