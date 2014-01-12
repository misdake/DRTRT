#pragma once

#include "MyMath.h"

//class Vector;

class Object
{
public:
	Object(void);
	~Object(void);

	//return true if hit.
	virtual bool rayTest(Vector start, Vector direction, float zMax, float& distance, Vector& hitPosition, Vector& normal) = 0;

	void getMatrix() { Matrix::getMatrix(p,n); };
	Matrix p,n;	//p是变换矩阵 n是逆变换矩阵

//private:
	//材质
	//float ka,kd,ks,kp; //局部光照
	//float kr;	//反射系数


	//应对testscenes的写法 暂时这样。
	Vector color;
};

#include "Mesh.h"
#include "Sphere.h"