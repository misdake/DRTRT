#pragma once

#include <string>
using std::string;
#include <vector>
using std::vector;

#include "Vector.h"
#include "MultiThreadedWorker.h"
#include "Object.h"

#include "JobSet.h"
#include "Main.h"

class Painter : public MultiThreadedWorker {
public:
	Painter();
	~Painter();

	void load(string fileName);

	void paint();
	void paint(JobSet*);
	void runTask(int);

	void unload();

private:
	vector<Object*> objList;
	Vector currentColor;

	JobSet * jobSet;
	float** lineBuffer;
	Vector paint(Vector& targetPoint);
	virtual void generateTasks();
	virtual void runTask(void*, int);
	virtual void finishTasks();

	//copied from Player every frame.
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

