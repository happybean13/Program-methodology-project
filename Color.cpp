/* Implement: Define each function of Color class */

#include <iostream>
#include "Color.h"

Color::Color(float r, float g, float b) {

	color[0] = r;
	color[1] = g;
	color[2] = b;
}

Color::~Color() {

}

void Color::setColor(float r, float g, float b) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
}