#pragma once

#include <string>
using std::string;
#include <vector>
using std::vector;

#include "Vector.h"
#include "Painter.h"

class Player
{
public:
	Player(void);
	~Player(void);

	void keyUp(unsigned char key);
	void keyDown(unsigned char key);
	virtual void load(string);

	void frame();
	float frameTime;

	void input();
	virtual void paint();
	void display();

	int width, height;
	float * frameBuffer;

	Vector camPosition;
	Vector camTarget;
	Vector camUp;
	float fov;

	void setSize(int width, int height) {
		if (frameBuffer != nullptr) {
			delete [] frameBuffer;
		}
		this->width = width;
		this->height = height;
		frameBuffer = new float[width * height * 3];
	}

	virtual void combine(int top, float* data) {
		memcpy(&frameBuffer[3 * top * width], data, 3 * width * 4);
	}

protected:
	float camXSpeed, camYSpeed;

	Painter painter;
};