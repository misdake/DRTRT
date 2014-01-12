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
	Matrix p,n;	//p�Ǳ任���� n����任����

//private:
	//����
	//float ka,kd,ks,kp; //�ֲ�����
	//float kr;	//����ϵ��


	//Ӧ��testscenes��д�� ��ʱ������
	Vector color;
};

#include "Mesh.h"
#include "Sphere.h"