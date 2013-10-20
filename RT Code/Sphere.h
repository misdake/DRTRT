#pragma once
#include "object.h"

//class Vector;
//class Object;

class Sphere :
	public Object
{
public:
	Sphere(void);
	~Sphere(void);

	virtual bool rayTest( Vector start, Vector direction, float zMax, float& distance, Vector& hitPosition, Vector& normal );


//private:
	float x,y,z;
	float r;
};