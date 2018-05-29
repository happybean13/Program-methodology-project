#include "Fill.h"

Fill::Fill(int x, int y) :Square(x,y,1,1,1,1) {

}

Fill::~Fill() {};

void Fill::draw() const {
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_QUADS);
	glVertex2f(center_pos[0] , center_pos[1] );
	glVertex2f(center_pos[0] + side_length , center_pos[1]);
	glVertex2f(center_pos[0] + side_length, center_pos[1]+ side_length);
	glVertex2f(center_pos[0] , center_pos[1] + side_length);
	glEnd();
}

