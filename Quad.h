#pragma once

/* Implement: Define Quad class */

class Quad {
public:
	Quad(int x, int y);
	~Quad();
	void setPos(int x, int y);
	virtual void draw() const = 0;
	int getX() const;
	int getY() const;
protected:
	int center_pos[2];
};