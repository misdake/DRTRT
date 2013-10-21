#pragma once

#include <string>
using std::string;
#include <vector>
using std::vector;

#include "Vector.h"
#include "Object.h"

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
};