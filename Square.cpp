/* Implement: Define each function of Square class */
#include <iostream>
#include "Square.h"

Square::Square(int x, int y, float r, float g, float b, int sl) : Quad(x, y), Color(r, g, b) {
	side_length = sl;
}


Square::~Square() {

}

int Square::getSideLength() const {
	return side_length;
}

void Square::draw()const {

	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_QUADS);
	glVertex2f(center_pos[0] + side_length /2, center_pos[1] + side_length / 2);
	glVertex2f(center_pos[0] - side_length / 2, center_pos[1] + side_length / 2);
	glVertex2f(center_pos[0] - side_length/ 2, center_pos[1] - side_length / 2);
	glVertex2f(center_pos[0] + side_length / 2, center_pos[1] - side_length / 2);
	glEnd();
}