#include <iostream>
using namespace std;

#include <math.h>
#include "../GL Lib/glut.h"
#include "Painter.h"

Painter painter;

void myDisplay() {
	bool SSAA = false;
	painter.paint(SSAA);
}

int main(int argc, char *argv[]) {	
	glutInit(&argc, argv);

	argv[2]="scene1.test";
	painter.load(argv[2]);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(painter.width, painter.height);
	glutInitWindowPosition(0,0);
	glutCreateWindow("DRTRT");
	
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	
	glutMainLoop();
}