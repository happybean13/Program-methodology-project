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

void Square::move(int direction, int *direct_past, int w, int h) {
	int d = 1;
	if (direction > 4)
		direction = *direct_past;

	if (direction == 1)
		if (center_pos[1] + side_length / 2 > h)
			setPos(center_pos[0], center_pos[1]);
		else {
			setPos(center_pos[0], center_pos[1] + d);
			*direct_past = 1;
		}
	if (direction == 2)
		if (center_pos[1] - side_length / 2 < 0)
			setPos(center_pos[0], center_pos[1]);
		else {
			setPos(center_pos[0], center_pos[1] - d);
			*direct_past = 2;

		}
	if (direction == 3)
		if (center_pos[0] - side_length / 2 < 0)
			setPos(center_pos[0], center_pos[1]);
		else {
			setPos(center_pos[0] - d, center_pos[1]);
			*direct_past = 3;

		}
	if (direction == 4)
		if (center_pos[0] + side_length / 2 > w)
			setPos(center_pos[0], center_pos[1]);
		else {
			setPos(center_pos[0] + d, center_pos[1]);
			*direct_past = 4;

		}
}