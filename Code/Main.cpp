#include <iostream>
using namespace std;

#include <math.h>
#include "../GL Lib/glut.h"
#include "Player.h"
#include "Painter.h"

Painter painter;
Player player;

void myDisplay() {
	painter.paint();
	player.display();
}

int main(int argc, char *argv[]) {	
	glutInit(&argc, argv);

	argv[2]="../Scene/scene1.test";
	painter.load(argv[2]);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(player.width, player.height);
	glutInitWindowPosition(0,0);
	glutCreateWindow("DRTRT");
	
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	
	glutMainLoop();
}