#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

/* Implement: Include header file(s) */
#include "Player.h"
#include "Fill.h"
/* Implement: Control FPS if you need */

clock_t start = clock();
clock_t endtime;

#define WIDTH 300		// window's width
#define HEIGHT 400		// window's height



int sp_key;				// special key
unsigned char norm_key;


//Node : 0 empty 1 fill 2 boundary 3 boundary_update 4 deleted_boundary
int Node[WIDTH][HEIGHT - 100] = { 0 };
int boundary_intersection_x[2];
int boundary_intersection_y[2];
int boundary_intersection_spkey = 0;
int clockwise = 0;
int counter_clockwise = 0;

Player pl(WIDTH /2 ,(HEIGHT-100)/2, 1, 1, 0, 6);
int present_Node, past_Node = 0;
int boundary_add_switch = 0;
Fill temp(WIDTH / 2, (HEIGHT - 100) / 2);


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

	

	init();

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
		cout << "DELETE_BOUNDARY" << "  x : " << x << "y : " << y << "direction" << d << endl;
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
	if (Node[x][y] == 1 || Node[x][y] == 2 || Node[x][y] == 3) {

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

			boundary_add_switch = 0;
			clockwise = 0;
			counter_clockwise = 0;
			boundary_intersection_spkey = 0;
		}
		if (boundary_add_switch == 1) {
			Node[pl.getX()][pl.getY()] = 3;

		}
		cout << "past, present, onoff  : "<< past_Node << " ," << present_Node << " , " << boundary_add_switch	<< endl;

		past_Node = present_Node;
	}
void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 'r')
		init();
}
void processSpecialKeys(int key, int x, int y) {
	/* Implement: Set key input */

	switch (key) {
	case GLUT_KEY_UP:
		if (sp_key != 2) {
			if (boundary_add_switch == 1) {
				if (sp_key == 3)
					clockwise++;
				if (sp_key == 4)
					counter_clockwise++;
			}
			sp_key = 1;
		}
		break;
	case GLUT_KEY_DOWN:
		if (sp_key != 1) {
			if (boundary_add_switch == 1) {
				if (sp_key == 4)
					clockwise++;
				if (sp_key == 3)
					counter_clockwise++;
			}
			sp_key = 2;
		}
		break;
	case GLUT_KEY_LEFT:
		if (sp_key != 4) {
			if (boundary_add_switch == 1) {
				if (sp_key == 2)
					clockwise++;
				if (sp_key == 1)
					counter_clockwise++;
			}
			sp_key = 3;
		}
		break;
	case GLUT_KEY_RIGHT:
		if (sp_key != 3) {
			if (boundary_add_switch == 1) {
				if (sp_key == 1)
					clockwise++;
				if (sp_key == 2)
					counter_clockwise++;
			}
			sp_key = 4;
		}
		break;

	}
}

void idle() {
	/* Implement: Move the square */
	endtime = clock();
	if (endtime - start > 1000 / 60) {
		pl.move(sp_key,int(WIDTH),int(HEIGHT)-100);
		add_boundary();
		//cout << "clock" << clockwise << " " << counter_clockwise << endl;

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
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT - 100; j++) {
			if (Node[i][j] == 1) {
				drawNode(i, j,1,1,1);

			}
			else if (Node[i][j] == 2) {
				drawNode(i, j,1,0,0);
			}
			else if (Node[i][j] == 3) {
				drawNode(i, j, 0, 0, 1);
			}
		}		
	}
	pl.draw();

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
