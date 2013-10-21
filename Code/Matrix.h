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
	Matrix(float x);	//ֻ���Խ����ϵ�4����������Ϊ0

	float v[4][4];
	Matrix operator*(const Matrix& m);
	Matrix transpose();

private:
	//ʱ���ϵ �����Ÿ���testscenes���� push��pop��ûɶ���á��ĵ������Ļ�Ӧ�ò�̫��
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

