#include <iostream>
using namespace std;

#include <math.h>
#include "../GL Lib/glut.h"
#include "Player.h"

Player painter;

void myDisplay() {
	painter.paint();
}

int main(int argc, char *argv[]) {	
	glutInit(&argc, argv);

	argv[2]="../Scene/scene1.test";
	painter.load(argv[2]);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(painter.width, painter.height);
	glutInitWindowPosition(0,0);
	glutCreateWindow("DRTRT");
	
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	
	glutMainLoop();
}