#include "Player.h"

Player::Player(int x, int y, float r, float g, float b, int sl) : Square(x, y, r, g, b, sl) {};

Player::~Player() {};

void Player::move(int direction,int w, int h) {
	int d = 1;
	if (direction == 1)
		if (center_pos[1] +  side_length/ 2 > h)
			setPos(center_pos[0], center_pos[1]);
		else
			setPos(center_pos[0], center_pos[1]+d);
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
