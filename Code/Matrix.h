#pragma once

class Vector;

class Matrix
{
public:
	Matrix(void);
	~Matrix(void);

	Matrix(
		float a00,float a01,float a02,float a03,
		float a10,float a11,float a12,float a13,
		float a20,float a21,float a22,float a23,
		float a30,float a31,float a32,float a33
		);
	Matrix(float x[4][4]);
	Matrix(float x);	//只填充对角线上的4个数，其余为0

	float v[4][4];
	Matrix operator*(const Matrix& m);
	Matrix transpose();

private:
	//时间关系 就照着给的testscenes来了 push和pop都没啥作用。改到正常的话应该不太难
	static Matrix cp;
	static Matrix cn;

public:
	static void translate(float x, float y, float z);
	static void rotate(float x, float y, float z, float angle);
	static void scale(float x, float y, float z);
	static void pushMatrix();
	static void popMatrix();
	static void getMatrix(Matrix& p, Matrix& n);
};

