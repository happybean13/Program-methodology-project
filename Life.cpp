
#include <iostream>
#include "Life.h"

Life::Life(int x, int y, float r, float g, float b, int sl) : Quad(x, y), Color(r, g, b) {
	side_length = sl;
}


Life::~Life() {

}

int Life::getSideLength() const {
	return side_length;
}

void Life::draw()const {

	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_POLYGON);
	glVertex2f(center_pos[0], center_pos[1] - side_length / 2);
	glVertex2f(center_pos[0] - side_length / 2, center_pos[1]);
	glVertex2f(center_pos[0] - side_length / 3, center_pos[1] + side_length / 3);
	glVertex2f(center_pos[0], center_pos[1]);
	glVertex2f(center_pos[0] + side_length / 3, center_pos[1] + side_length / 3);
	glVertex2f(center_pos[0] + side_length / 2, center_pos[1]);
	glEnd();
}


void Life::move(int direction, int w, int h) {
	int d = 5;
	if (direction == 1)
		if (center_pos[1] + side_length / 2 > h)
			setPos(center_pos[0], center_pos[1]);
		else
			setPos(center_pos[0], center_pos[1] + d);
	if (direction == 2)
		if (center_pos[1] - side_length / 2 < 0)
			setPos(center_pos[0], center_pos[1]);
		else
			setPos(center_pos[0], center_pos[1] - d);
	if (direction == 3)
		if (center_pos[0] - side_length / 2 < 0)
			setPos(center_pos[0], center_pos[1]);
		else
			setPos(center_pos[0] - d, center_pos[1]);
	if (direction == 4)
		if (center_pos[0] + side_length / 2 > w)
			setPos(center_pos[0], center_pos[1]);
		else
			setPos(center_pos[0] + d, center_pos[1]);

}