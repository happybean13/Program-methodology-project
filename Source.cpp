#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

/* Implement: Include header file(s) */
#include "Player.h"
#include "Fill.h"
#include "life.h"
/* Implement: Control FPS if you need */

clock_t start = clock();
clock_t endtime;

#define WIDTH 300		// window's width
#define HEIGHT 400		// window's height



int sp_key;				// special key
unsigned char norm_key;


//Node : 0 empty 1 fill 2 boundary 3 boundary_update 4 deleted_boundary 5 flood fill test
int Node[WIDTH][HEIGHT - 100] = { 0 };
int boundary_intersection_x[2];
int boundary_intersection_y[2];
int boundary_intersection_spkey = 0;
int clockwise = 0;
int counter_clockwise = 0;
int win = 1;
int kill = 0;
//
int right_before_added_boundary[2];


Player pl(WIDTH /2 ,(HEIGHT-100)/2, 1, 1, 0, 6);
int present_Node, past_Node = 0;
int boundary_add_switch = 0;
Fill temp(WIDTH / 2, (HEIGHT - 100) / 2);
Square sq0(100, 205, 1, 1, 1, 10);
Square sq1(100, 165, 1, 1, 1, 10);
Square sq2(100, 125, 1, 1, 1, 10);
Square sq3(100, 85, 1, 1, 1, 10);
Square z1(rand() % 300, rand() % 300, 1, 0, 0, 6);
Square z2(rand() % 300, rand() % 300, 0, 1, 0, 6);
Square z3(rand() % 300, rand() % 300, 0, 0, 1, 6);
Square z4(rand() % 300, rand() % 300, 0.5, 0.5, 0.5, 6);
int z_dir[4] = { 0 };
int z_die[4] = { 1,1,1,1 };
Life lf1(20, 370, 1, 0, 0, 16);
Life lf2(40, 370, 1, 0, 0, 16);
Life lf3(60, 370, 1, 0, 0, 16);
int mode = 0;
int sw = 0;

//
int life = 3;

void init() {
	
	int initial_box = 10;
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < (HEIGHT - 100); j++) {
			Node[i][j] = 0;
		}
	}
	//for (int i = -initial_box; i < initial_box; i++) {
	//	for (int j = -initial_box; j < initial_box; j++) {
	//		temp.setPos(WIDTH / 2 + i, (HEIGHT - 100) / 2 + j);
	//		Fl.push_back(temp);
	//		if (i == -initial_box || i == initial_box - 1 || j == -initial_box || j == initial_box - 1)
	//			boundary.push_back(temp);
	//	}
	//}
	for (int i = WIDTH / 2 -initial_box; i < WIDTH / 2+initial_box; i++) {
		for (int j = (HEIGHT - 100) / 2 -initial_box; j <  (HEIGHT - 100) / 2+ initial_box; j++) {
			Node[i][j] = 1;
			if (i == WIDTH / 2 -initial_box || i == WIDTH / 2+ initial_box - 1 || j == (HEIGHT - 100) / 2 -initial_box || j == (HEIGHT - 100) / 2 +initial_box - 1)
				Node[i][j] = 2;
		}
	}
	pl.setPos(WIDTH / 2, (HEIGHT - 100) / 2);
	sp_key = 0;
	present_Node = 0;
	past_Node = 0;
	boundary_add_switch = 0;
	life = 3;
	win = 1;
	z_die[0] = 1;
	z_die[1] = 1;

	z_die[2] = 1;
	z_die[3] = 1;

}

inline void drawNode(int x, int y, int r, int g, int b) {
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + 1, y);
	glVertex2f(x + 1, y + 1);
	glVertex2f(x, y + 1);
	glEnd();
}



void restart() {

	
	pl.setPos(WIDTH / 2, (HEIGHT - 100) / 2);
	sp_key = 0;
	present_Node = 0;
	past_Node = 0;
	boundary_add_switch = 0;
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < (HEIGHT - 100); j++) {
			if(Node[i][j] ==3)
				Node[i][j] = 0;
		}
	}
	life--;
}
//
void meet_boundary() {
	if (Node[z1.getX()][z1.getY()] == 3 || Node[z2.getX()][z2.getY()] == 3 || Node[z3.getX()][z3.getY()] == 3 || Node[z4.getX()][z4.getY()] == 3) {
		restart();
		cout << "=======  Meet Bugs  =======" << endl;
		cout << "z1 ("  << z1.getX() << " , "<< z1.getY() << ")"<< endl;
	}
	if (right_before_added_boundary[0] == pl.getX() && right_before_added_boundary[1] == pl.getY()) {
		//cout << "?" << endl;
	}
	else if (Node[pl.getX()][ pl.getY()] == 3) {
		restart();
		cout << "=======  Meet Boundary  =======" << endl;

	}


}
void move_z() {
	int rand_num = 20;
	if (z_die[0] == 1) {
		if (Node[z1.getX() + z1.getSideLength() / 2][z1.getY()] == 2) {
			z1.move(3, z_dir, int(WIDTH), int(HEIGHT) - 100);
			cout << "1" << endl;
		}
		else if (Node[z1.getX() - z1.getSideLength() / 2][z1.getY()] == 2) {
			z1.move(4, z_dir, int(WIDTH), int(HEIGHT) - 100);
			cout << "2" << endl;

		}
		else if (Node[z1.getX() ][z1.getY() - z1.getSideLength() / 2] == 2) {
			z1.move(1, z_dir, int(WIDTH), int(HEIGHT) - 100);
			cout << "3" << endl;

		}
		else if (Node[z1.getX()][z1.getY() + z1.getSideLength() / 2] == 2) {
			z1.move(2, z_dir, int(WIDTH), int(HEIGHT) - 100);
			cout << "4" << endl;

		}
		else {
			z1.move(rand() % rand_num, z_dir, int(WIDTH), int(HEIGHT) - 100);
			cout << "5" << endl;
		}
	}
	if (z_die[1] == 1) {
		if (Node[z2.getX() + z2.getSideLength() / 2][z2.getY()] == 2) {
			z2.move(3, z_dir, int(WIDTH), int(HEIGHT) - 100);
		}
		else if (Node[z2.getX() - z2.getSideLength() / 2][z2.getY()] == 2) {
			z2.move(4, z_dir, int(WIDTH), int(HEIGHT) - 100);
		}
		else if (Node[z2.getX()][z2.getY() - z2.getSideLength() / 2] == 2) {
			z2.move(1, z_dir, int(WIDTH), int(HEIGHT) - 100);
		}
		else if (Node[z2.getX()][z2.getY() + z2.getSideLength() / 2] == 2) {
			z2.move(2, z_dir, int(WIDTH), int(HEIGHT) - 100);
		}
		else {
			z2.move(rand() % rand_num, z_dir+1, int(WIDTH), int(HEIGHT) - 100);
		}
	}
	if (z_die[2] == 1) {
		if (Node[z3.getX() + z3.getSideLength() / 2][z3.getY()] == 2) {
			z3.move(3, z_dir, int(WIDTH), int(HEIGHT) - 100);
		}
		else if (Node[z3.getX() - z3.getSideLength() / 2][z3.getY()] == 2) {
			z3.move(4, z_dir, int(WIDTH), int(HEIGHT) - 100);
		}
		else if (Node[z3.getX()][z3.getY() - z3.getSideLength() / 2] == 2) {
			z3.move(1, z_dir, int(WIDTH), int(HEIGHT) - 100);
		}
		else if (Node[z3.getX()][z3.getY() + z3.getSideLength() / 2] == 2) {
			z3.move(2, z_dir, int(WIDTH), int(HEIGHT) - 100);
		}
		else {
			z3.move(rand() % rand_num, z_dir+2, int(WIDTH), int(HEIGHT) - 100);
		}
	}
	if (z_die[3] == 1) {
		if (Node[z4.getX() + z4.getSideLength() / 2][z4.getY()] == 2) {
			z4.move(3, z_dir, int(WIDTH), int(HEIGHT) - 100);
		}
		else if (Node[z4.getX() - z4.getSideLength() / 2][z4.getY()] == 2) {
			z4.move(4, z_dir, int(WIDTH), int(HEIGHT) - 100);
		}
		else if (Node[z4.getX()][z4.getY() - z4.getSideLength() / 2] == 2) {
			z4.move(1, z_dir, int(WIDTH), int(HEIGHT) - 100);
		}
		else if (Node[z4.getX()][z4.getY() + z4.getSideLength() / 2] == 2) {
			z4.move(2, z_dir, int(WIDTH), int(HEIGHT) - 100);
		}
		else {
			z4.move(rand() % rand_num, z_dir+3, int(WIDTH), int(HEIGHT) - 100);
		}
	}
	if (z_die[0] == 0)
		z1.setPos(0, 0);
	if (z_die[1] == 0)
		z2.setPos(0, 0);
	if (z_die[2] == 0)
		z3.setPos(0, 0);
	if (z_die[3] == 0)
		z4.setPos(0, 0);
}
void check_die() {
	if (Node[z1.getX()][z1.getY()] == 1) {
		z_die[0] = 0;
		kill++;
	}
	if (Node[z2.getX()][z2.getY()] == 1) {
		z_die[1] = 0;
		kill++;

	}
	if (Node[z3.getX()][z3.getY()] == 1) {
		z_die[2] = 0;
		kill++;

	}
	if (Node[z4.getX()][z4.getY()] == 1) {
		z_die[3] = 0;
		kill++;

	}
}
void delete_boundary(int x, int y, int d) {
	if (x == boundary_intersection_x[1] && y == boundary_intersection_y[1]) {
		cout << "================DELETE_BOUNDARY_OVER=====================" << endl;
	}
	else {
		Node[x][y] = 4;
		//cout << "DELETE_BOUNDARY" << "  x : " << x << "y : " << y << "direction" << d << endl;
		if (d == 1) {
			if (Node[x - 1][y] == 2) {
				delete_boundary(x - 1, y, 3);
			}
			else if (Node[x + 1][y] == 2) {
				delete_boundary(x + 1, y, 4);
			}
			else if (Node[x][y + 1] == 2) {
				delete_boundary(x, y + 1, 1);
			}
		}
		else if(d==2) {
			if (Node[x - 1][y] == 2) {
				delete_boundary(x - 1, y, 3);
			}
			else if (Node[x + 1][y] == 2) {
				delete_boundary(x + 1, y, 4);
			}
			else if (Node[x][y - 1] == 2) {
				delete_boundary(x, y - 1, 2);
			} 
		}
		else if (d == 3) {
			if (Node[x][y-1] == 2) {
				delete_boundary(x, y-1, 2);
			}
			else if (Node[x][y + 1] == 2) {
				delete_boundary(x, y + 1, 1);
			}
			else if (Node[x-1][y] == 2) {
				delete_boundary(x-1, y, 3);
			}
		}
		else if (d == 4) {
			if (Node[x][y - 1] == 2) {
				delete_boundary(x, y - 1, 2);
			}
			else if (Node[x][y + 1] == 2) {
				delete_boundary(x, y + 1, 1);
			}
			else if (Node[x +1][y] == 2) {
				delete_boundary(x +1, y , 4);
			}
		}

	}

}
void delete_boundary2(int x, int y, int d) {
	if (x == boundary_intersection_x[1] && y == boundary_intersection_y[1]) {
		cout << "================DELETE_BOUNDARY_OVER=====================" << endl;
	}
	else {
		Node[x][y] = 4;
		//cout << "DELETE_BOUNDARY" << "  x : " << x << "y : " << y << "direction" << d << endl;
		if (d == 1) {
			if (Node[x - 1][y] == 2) {
				delete_boundary2(x - 1, y, 3);
			}
			else if (Node[x + 1][y] == 2) {
				delete_boundary2(x + 1, y, 4);
			}
			else if (Node[x][y + 1] == 2) {
				delete_boundary2(x, y + 1, 1);
			}
		}
		else if (d == 2) {
			if (Node[x - 1][y] == 2) {
				delete_boundary2(x - 1, y, 3);
			}
			else if (Node[x + 1][y] == 2) {
				delete_boundary2(x + 1, y, 4);
			}
			else if (Node[x][y - 1] == 2) {
				delete_boundary2(x, y - 1, 2);
			}
		}
		else if (d == 3) {
			if (Node[x][y - 1] == 2) {
				delete_boundary2(x, y - 1, 2);
			}
			else if (Node[x][y + 1] == 2) {
				delete_boundary2(x, y + 1, 1);
			}
			else if (Node[x - 1][y] == 2) {
				delete_boundary2(x - 1, y, 3);
			}
		}
		else if (d == 4) {
			if (Node[x][y - 1] == 2) {
				delete_boundary2(x, y - 1, 2);
			}
			else if (Node[x][y + 1] == 2) {
				delete_boundary2(x, y + 1, 1);
			}
			else if (Node[x + 1][y] == 2) {
				delete_boundary2(x + 1, y, 4);
			}
		}

	}

}
void Flood_fill(int x, int y) {
	if (Node[x][y] == 1 || Node[x][y] == 2 || Node[x][y] == 3)  {

	}
	else if (x <0 || y<0 || x> WIDTH - 1 || y> HEIGHT - 100 - 1) {
		cout << "Flood FIll out of range" << endl;
	}
	else {
		//cout << "FIlled (x,y,) " << "( " << x << ", " << y << " , " << ")" << endl;
		Node[x][y] = 1;
		Flood_fill(x + 1, y);
		Flood_fill(x - 1, y);
		Flood_fill(x, y+1);
		Flood_fill(x , y-1);
	}
}

void Flood_fill2(int x, int y, int * onoff) {
	if (*onoff == 1) {
		if (Node[x][y] == 1 || Node[x][y] == 2 || Node[x][y] == 3 || Node[x][y] ==5) {

		}
		else if (x <0 || y<0 || x> WIDTH - 1 || y> HEIGHT - 100 - 1) {
			cout << "Flood FIll out of range" << endl;
			*onoff = 0;
		}
		else {
			//cout << "FIlled (x,y,) " << "( " << x << ", " << y << " , " << ")" << endl;
			Node[x][y] = 5;
			Flood_fill2(x + 1, y,onoff);
			Flood_fill2(x - 1, y,onoff);
			Flood_fill2(x, y + 1,onoff);
			Flood_fill2(x, y - 1,onoff);
		}
	}
}
void add_boundary() {
	present_Node = Node[pl.getX()][pl.getY()];
	int it_x, it_y, it_spkey;

		if ( present_Node ==0 && past_Node == 2) {
			boundary_intersection_x[0] = pl.getX();
			boundary_intersection_y[0] = pl.getY();
			boundary_intersection_spkey = sp_key;
			boundary_add_switch = 1;
		}
		

		
		else if (present_Node == 2 && past_Node == 0 ) {
			
			boundary_intersection_x[1] = pl.getX();
			boundary_intersection_y[1] = pl.getY();
			if (clockwise > counter_clockwise) {
				if (boundary_intersection_spkey == 1) {
					boundary_intersection_x[0]++;
					boundary_intersection_y[0]--;
					it_spkey = 4;
				}
				else if (boundary_intersection_spkey == 2) {
					boundary_intersection_x[0]--;
					boundary_intersection_y[0]++;
					it_spkey = 3;
				}
				else if (boundary_intersection_spkey == 3) {
					boundary_intersection_x[0]++;
					boundary_intersection_y[0]++;
					it_spkey = 1;
				}
				else if (boundary_intersection_spkey == 4) {
					boundary_intersection_x[0]--;
					boundary_intersection_y[0]--;
					it_spkey = 2;
				}
				it_x = boundary_intersection_x[0];
				it_y = boundary_intersection_y[0];
				delete_boundary(it_x, it_y, it_spkey);
				for (int i = 0; i < WIDTH; i++) {
					for (int j = 0; j < (HEIGHT - 100); j++) {
						if (Node[i][j] == 3)
							Node[i][j] = 2;
					}
				}
				Flood_fill(boundary_intersection_x[0], boundary_intersection_y[0]);

			}
			else if (clockwise < counter_clockwise) {
				if (boundary_intersection_spkey == 1) {
					boundary_intersection_x[0]--;
					boundary_intersection_y[0]--;
					it_spkey = 3;
				}
				else if (boundary_intersection_spkey == 2) {
					boundary_intersection_x[0]++;
					boundary_intersection_y[0]++;
					it_spkey = 4;
				}
				else if (boundary_intersection_spkey == 3) {
					boundary_intersection_x[0]++;
					boundary_intersection_y[0]--;
					it_spkey = 2;
				}
				else if (boundary_intersection_spkey == 4) {
					boundary_intersection_x[0]--;
					boundary_intersection_y[0]++;
					it_spkey = 1;
				}
				it_x = boundary_intersection_x[0];
				it_y = boundary_intersection_y[0];
				delete_boundary(it_x, it_y, it_spkey);
				for (int i = 0; i < WIDTH; i++) {
					for (int j = 0; j < (HEIGHT - 100); j++) {
						if (Node[i][j] == 3)
							Node[i][j] = 2;
					}
				}
				Flood_fill(boundary_intersection_x[0], boundary_intersection_y[0]);
			}
			else if (clockwise == counter_clockwise) {
				int left_on = 1;
				int right_on = 1;
				cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
				if (boundary_intersection_spkey == 1) {
					Flood_fill2(boundary_intersection_x[0] - 1, boundary_intersection_y[0], &left_on);
					Flood_fill2(boundary_intersection_x[0] + 1, boundary_intersection_y[0], &right_on);
					if (left_on == 1) {
						boundary_intersection_x[0]--;
						boundary_intersection_y[0]--;
						it_spkey = 3;
					}
					if (right_on == 1) {
						boundary_intersection_x[0]++;
						boundary_intersection_y[0]--;
						it_spkey = 4;
					}
				}
				else if (boundary_intersection_spkey == 2) {
					Flood_fill2(boundary_intersection_x[0] + 1, boundary_intersection_y[0], &left_on);
					Flood_fill2(boundary_intersection_x[0] - 1, boundary_intersection_y[0], &right_on);
					if (left_on == 1) {
						boundary_intersection_x[0]++;
						boundary_intersection_y[0]++;
						it_spkey = 4;
					}
					if (right_on == 1) {
						boundary_intersection_x[0]--;
						boundary_intersection_y[0]++;
						it_spkey = 3;
					}
				}
				else if (boundary_intersection_spkey == 3) {
					Flood_fill2(boundary_intersection_x[0] , boundary_intersection_y[0]-1, &left_on);
					Flood_fill2(boundary_intersection_x[0] , boundary_intersection_y[0]+1, &right_on);
					if (left_on == 1) {
						boundary_intersection_x[0]++;
						boundary_intersection_y[0]--;
						it_spkey = 2;
					}
					if (right_on == 1) {
						boundary_intersection_x[0]++;
						boundary_intersection_y[0]++;
						it_spkey = 1;
					}
				}
				else if (boundary_intersection_spkey == 4) {
					Flood_fill2(boundary_intersection_x[0], boundary_intersection_y[0] + 1, &left_on);
					Flood_fill2(boundary_intersection_x[0], boundary_intersection_y[0] - 1, &right_on);
					if (left_on == 1) {
						boundary_intersection_x[0]--;
						boundary_intersection_y[0]++;
						it_spkey = 1;
					}
					if (right_on == 1) {
						boundary_intersection_x[0]--;
						boundary_intersection_y[0]--;
						it_spkey = 2;
					}
				}
				for (int i = 0; i < WIDTH; i++) {
					for (int j = 0; j < (HEIGHT - 100); j++) {
						if (Node[i][j] == 5)
							Node[i][j] = 0;
					}
				}
				it_x = boundary_intersection_x[0];
				it_y = boundary_intersection_y[0];
				delete_boundary(it_x, it_y, it_spkey);
				for (int i = 0; i < WIDTH; i++) {
					for (int j = 0; j < (HEIGHT - 100); j++) {
						if (Node[i][j] == 3)
							Node[i][j] = 2;
					}
				}
				Flood_fill(boundary_intersection_x[0], boundary_intersection_y[0]);
			}

			boundary_add_switch = 0;
			clockwise = 0;
			counter_clockwise = 0;
			boundary_intersection_spkey = 0;
		}
		if (boundary_add_switch == 1) {
			Node[pl.getX()][pl.getY()] = 3;
			right_before_added_boundary[0] = pl.getX();
			right_before_added_boundary[1] = pl.getY();

		}
		//cout << "past, present, onoff  : "<< past_Node << " ," << present_Node << " , " << boundary_add_switch	<< endl;

		past_Node = present_Node;
	}
void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 'r')
		init();
	if (key == 13) {
		mode += 4;
		sw = 1;
	}
}
void processSpecialKeys(int key, int x, int y) {
	/* Implement: Set key input */

	switch (key) {
	case GLUT_KEY_UP:
		if (sw == 1) {
			if (sp_key != 2) {
				if (boundary_add_switch == 1) {
					if (sp_key == 3)
						clockwise++;
					if (sp_key == 4)
						counter_clockwise++;
				}
				sp_key = 1;
			}
		}
		else if (sw == 0) {
			if (mode > 0)
				mode--;
		}
		break;
	case GLUT_KEY_DOWN:
		if (sw == 1) {
			if (sp_key != 1) {
				if (boundary_add_switch == 1) {
					if (sp_key == 4)
						clockwise++;
					if (sp_key == 3)
						counter_clockwise++;
				}
				sp_key = 2;
			}
		}
		else if (sw == 0) {
			if (mode < 3)
				mode++;
		}
		break;
	case GLUT_KEY_LEFT:
		if (sw == 1) {
			if (sp_key != 4) {
				if (boundary_add_switch == 1) {
					if (sp_key == 2)
						clockwise++;
					if (sp_key == 1)
						counter_clockwise++;
				}
				sp_key = 3;
			}
		}
		break;
	case GLUT_KEY_RIGHT:
		if (sw == 1) {
			if (sp_key != 3) {
				if (boundary_add_switch == 1) {
					if (sp_key == 1)
						clockwise++;
					if (sp_key == 2)
						counter_clockwise++;
				}
				sp_key = 4;
			}
		}
		break;

	}
}

void draw_string(void*font, const char* str, float x, float y) {
	glRasterPos2f(x, y);
	for (int i = 0; i < strlen(str); i++)
		glutBitmapCharacter(font, str[i]);
}


void idle() {
	/* Implement: Move the square */
	endtime = clock();
	if (endtime - start > 1000 / 120) {
		if (mode >= 4) {
			pl.move(sp_key, int(WIDTH), int(HEIGHT) - 100);
			meet_boundary();
			add_boundary();
			check_die();
			move_z();

		}
		start = endtime;
	}
	glutPostRedisplay();
}


void renderScene() {
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, 0, HEIGHT);
	if (mode < 4) {
		glColor3f(1, 1, 1);
		draw_string(GLUT_BITMAP_9_BY_15, "Select Level", 110, 250);
		glColor3f(0, 1, 1);
		draw_string(GLUT_BITMAP_9_BY_15, "EASY", 110, 200);
		glColor3f(1, 1, 0);
		draw_string(GLUT_BITMAP_9_BY_15, "NORMAL", 110, 160);
		glColor3f(1, 0, 1);
		draw_string(GLUT_BITMAP_9_BY_15, "HARD", 110, 120);
		glColor3f(1, 0, 0);
		draw_string(GLUT_BITMAP_9_BY_15, "HELL", 110, 80);
		if (mode == 0)
			sq0.draw();
		else if (mode == 1)
			sq1.draw();
		else if (mode == 2)
			sq2.draw();
		else if (mode == 3)
			sq3.draw();
	}
	else if (mode >= 4) {
		int count = 0;
		
		if(life >0)
			lf1.draw();
		if(life>1)
			lf2.draw();
		if(life>2)
			lf3.draw();
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT - 100; j++) {
				if (Node[i][j] == 1) {
					drawNode(i, j, 1, 1, 1);
					count++;
				}
				else if (Node[i][j] == 2) {
					drawNode(i, j, 1, 0, 0);
				}
				else if (Node[i][j] == 3) {
					drawNode(i, j, 0, 0, 1);
				}
			}
		}
		pl.draw();
		char kill2[100];                                                  //요기부터
		sprintf_s(kill2, "%d", kill);
		glColor3f(1, 1, 1);
		draw_string(GLUT_BITMAP_HELVETICA_10, "You've killed", 85, 300);
		draw_string(GLUT_BITMAP_HELVETICA_10, kill2, 150, 300);
		draw_string(GLUT_BITMAP_HELVETICA_10, "enemy(enemies)", 160, 300);
		float percent = (float)count / 90000 * 100;
		char q[100];
		sprintf_s(q, "%d", (int)percent);
		glColor3f(1, 1, 1);
		//cout << percent << endl;
		draw_string(GLUT_BITMAP_9_BY_15, q, 190, 365);
		draw_string(GLUT_BITMAP_9_BY_15, "%", 210, 365);


		
		switch (mode) {
		case 4:
			if(z_die[0] ==1)
				z1.draw();
			z_die[1] = 0;
			z_die[2] = 0;
			z_die[3] = 0;
			break;
		case 5:
			if (z_die[0] == 1)
				z1.draw();
			if (z_die[1] == 1)
				z2.draw();
			z_die[2] = 0;
			z_die[3] = 0;
			break;
		case 6:
			if (z_die[0] == 1)
			z1.draw();
			if (z_die[1] == 1)
			z2.draw();
			if (z_die[2] == 1)
			z3.draw();
			z_die[3] = 0;
			break;
		case 7:
			if (z_die[0] == 1)
			z1.draw();
			if (z_die[1] == 1)
			z2.draw();
			if (z_die[2] == 1)
			z3.draw();
			if (z_die[3] == 1)
			z4.draw();
			break;
		}
		if (percent>60) {
			glColor3f(1, 0.3, 1);
			draw_string(GLUT_BITMAP_9_BY_15, "WIIIINNNNNN", 120, 150);
		}
	}
	if (life == 0) {
		glColor3f(1, 0.3, 1);
		draw_string(GLUT_BITMAP_9_BY_15, "GAME OVER", 120, 150);
	}

	glutSwapBuffers();
}


void main(int argc, char **argv) {
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(WIDTH, HEIGHT);

	glutCreateWindow("Project");


	init();
	// register callbacks
	glutDisplayFunc(renderScene);
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(processNormalKeys);
	glutIdleFunc(idle);

	// enter GLUT event processing cycle
	glutMainLoop();

}
