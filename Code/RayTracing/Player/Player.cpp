#include "Player.h"

#include <Windows.h>
#include "../../GL Lib/glut.h"
#include <iostream>
using std::string;
using std::cout;
using std::endl;

Player::Player(void)
{
	camXSpeed = 0;
	camYSpeed = 0;
}


Player::~Player(void)
{
}


void Player::frame() {
	input();
	paint();
	display();
}

void Player::input() {
	float camXDistance = camXSpeed * frameTime;
	float camYDistance = camYSpeed * frameTime;

	camPosition.x += camXSpeed; camTarget.x += camXSpeed;
	camPosition.y += camYSpeed; camTarget.y += camYSpeed;
}


void Player::paint() {
	painter.paint();
}

void Player::display() {
	glDrawPixels(width, height, GL_RGB, GL_FLOAT, frameBuffer);
	glutSwapBuffers();
}

void Player::keyUp( unsigned char key ) {
	if(key == 'w') {
		camYSpeed = 0;
	} else if(key == 's') {
		camYSpeed = 0;
	} else if(key == 'a') {
		camXSpeed = 0;
	} else if(key == 'd') {
		camXSpeed = 0;
	}
}

void Player::keyDown( unsigned char key ) {
	if(key == 'w') {
		camYSpeed = 1;
	} else if(key == 's') {
		camYSpeed = -1;
	} else if(key == 'a') {
		camXSpeed = -1;
	} else if(key == 'd') {
		camXSpeed = 1;
	}
}

void Player::load(string fileName) {
	painter.load(fileName);
}
