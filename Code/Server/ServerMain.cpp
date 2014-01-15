#include <iostream>
#include "Main.h"

#include "../../GL Lib/glut.h"
#include "ServerPlayer.h"
#include "Painter.h"

Player * player;

void myKeyboardUp(unsigned char key, int x, int y) {
	player->keyUp(key);
}
void myKeyboardDown(unsigned char key, int x, int y) {
	player->keyDown(key);
}

void myDisplay() {
	player->frame();
}

int main(int argc, char *argv[]) {	
	glutInit(&argc, argv);

	player = new ServerPlayer();

	player->load("../Scene/scene1.test");
	((ServerPlayer*)player)->loadClientList("../Scene/client.test");
	((ServerPlayer*)player)->start();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(player->width, player->height);
	glutInitWindowPosition(0,0);
	glutCreateWindow("DRTRT");

	glutKeyboardUpFunc(myKeyboardUp);
	glutKeyboardFunc(myKeyboardDown);
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	
	glutMainLoop();
}