#pragma once

#include <iostream>
using std::ostream;

class Matrix;

class Vector
{
public:
	Vector(void);
	~Vector(void);

	Vector(const float[]);
	Vector(float a,float b,float c);
	Vector(const Vector&);

	float x,y,z;

	Vector& normalize();
	float length();

	Vector& operator=(const Vector& r);
	Vector operator+(const Vector& r);
	Vector operator-(const Vector& r);
	float operator*(const Vector& r);
	Vector operator*(const Matrix& m);	//做变换
	Vector operator/(const Vector& r);	//!!!!!!!!!!特殊 这是叉积!!!!!!!!!!
	Vector operator*(float t);
	Vector operator/(float t);

	friend Vector& operator+=(Vector& l,const Vector& r);
	friend Vector& operator-=(Vector& l,const Vector& r);
	friend Vector& operator*=(Vector& l,float t);
	friend Vector& operator/=(Vector& l,float t);

	friend ostream& operator<<(ostream& output, Vector& v);

	//friend Vecotr& operator*(const Matrix& m, const Vector& v);
	//friend Vecotr& operator*(const Vector& v, const Matrix& m);
};

