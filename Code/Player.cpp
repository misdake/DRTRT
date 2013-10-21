#include "Player.h"

#include <Windows.h>
#include "../GL Lib/glut.h"
#include <iostream>
using std::string;
using std::cout;
using std::endl;

Player::Player(void)
{
}


Player::~Player(void)
{
}

void Player::display() {
	//time thing.
	static DWORD time = timeGetTime();
	DWORD last = time;
	time = timeGetTime();
	cout << time - last << endl;

	//display the frame buffer
	glDrawPixels(width, height, GL_RGB, GL_FLOAT, frameBuffer);

	glutSwapBuffers();
}