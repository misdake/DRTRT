#pragma once
#include "object.h"
#include <vector>
using std::vector;

class Mesh :
	public Object
{
public:
	Mesh(void);
	~Mesh(void);

	virtual bool rayTest( Vector start, Vector direction, float zMax, float& distance, Vector& hitPosition, Vector& normal );

	bool lighting;
	vector<Vector*> vertex;
	vector<Vector*> normal;

	//Bounding Box
	Vector min,max;
};

