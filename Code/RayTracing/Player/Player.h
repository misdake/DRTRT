#pragma once

#include <string>
using std::string;
#include <vector>
using std::vector;

#include "Vector.h"

class Player
{
public:
	Player(void);
	~Player(void);


	void display();

	int width, height;
	float * frameBuffer;

	void setSize(int width, int height) {
		if (frameBuffer != nullptr) {
			delete [] frameBuffer;
		}
		this->width = width;
		this->height = height;
		frameBuffer = new float[width * height * 3];
	}

	inline void setPixel(int left, int top, float r, float g, float b) {
		float* c = &frameBuffer[top * width * 3 + left * 3];
		c[0] = r; c[1] = g; c[2] = b;
	}
};