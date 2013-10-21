#pragma once

#include <string>
using std::string;
#include <vector>
using std::vector;

#include "Vector.h"
#include "MultiThreadedWorker.h"

#include "Player.h"
extern Player player;

class Painter : public MultiThreadedWorker {
public:
	Painter();
	~Painter();

	void load(string fileName);
	void setCameraPosition(float x, float y, float z) { camPosition = Vector(x, y, z); };
	void setCameraTarget(float x, float y, float z) { camTarget = Vector(x, y, z); };
	void setCameraUp(float x, float y, float z) { camUp = Vector(x, y, z); };
	void setCameraFov(float fov) { this->fov = fov; };

	void paint();

	void unload();

private:
	vector<Object*> objList;
	Vector currentColor;

	int* input;
	Vector paint(Vector& targetPoint);
	virtual void generateTasks();
	virtual void runTask(void*);
	virtual void finishTasks();

	Vector camPosition;
	Vector camTarget;
	Vector camUp;
	float fov;

	//temporary variables. not always safe.
	Vector w, h;
	int width;
	int height;
	float* frameBuffer;
};

