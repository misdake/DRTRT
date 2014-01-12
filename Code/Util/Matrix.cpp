#include "Matrix.h"
#include "MyMath.h"


Matrix::Matrix(void)
{
	Matrix(1.0f);
}

Matrix::Matrix( float a00,float a01,float a02,float a03, float a10,float a11,float a12,float a13, float a20,float a21,float a22,float a23, float a30,float a31,float a32,float a33 )
{
	v[0][0]=a00; v[0][1]=a01; v[0][2]=a02; v[0][3]=a03;
	v[1][0]=a10; v[1][1]=a11; v[1][2]=a12; v[1][3]=a13;
	v[2][0]=a20; v[2][1]=a21; v[2][2]=a22; v[2][3]=a23;
	v[3][0]=a30; v[3][1]=a31; v[3][2]=a32; v[3][3]=a33;
}

Matrix::Matrix( float x[4][4] )
{
	for(int i=0; i!=4; i++)
		for(int j=0; j!=4; j++)
			v[i][j]=x[i][j];
}

Matrix::Matrix( float x )
{
	for(int i=0; i!=4; i++)
		for(int j=0; j!=4; j++)
			v[i][j]=(i==j)?x:0;
}


Matrix::~Matrix(void)
{
}

Matrix Matrix::operator*( const Matrix& m )
{
	Matrix r(0.0f);
	for(int i=0; i!=4; i++)
		for(int k=0; k!=4; k++)
			for(int j=0; j!=4; j++)
				r.v[i][j] += v[i][k] * m.v[k][j];
	return r;
}

Matrix Matrix::cp(1.0f);
Matrix Matrix::cn(1.0f);

void Matrix::translate( float x, float y, float z )
{
	Matrix p(
		1,0,0,x,
		0,1,0,y,
		0,0,1,z,
		0,0,0,1
		);
	Matrix n(
		1,0,0,-x,
		0,1,0,-y,
		0,0,1,-z,
		0,0,0,1
		);
	cp = cp * p;
	cn = n * cn;
}

void Matrix::rotate( float x, float y, float z, float angle )
{
	float a = angle / 180 * pi;
	if(x==1) {
		Matrix p(
			1,0,0,0,
			0,cosf(a),-sinf(a),0,
			0,sinf(a),cosf(a),0,
			0,0,0,1
			);
		Matrix n(
			1,0,0,0,
			0,cosf(a),sinf(a),0,
			0,-sinf(a),cosf(a),0,
			0,0,0,1
			);
		cp = cp * p;
		cn = n * cn;
	} else if(y==1) {
		Matrix p(
			cosf(a),0,sinf(a),0,
			0,1,0,0,
			-sinf(a),0,cosf(a),0,
			0,0,0,1
			);
		Matrix n(
			cosf(a),0,-sinf(a),0,
			0,1,0,0,
			sinf(a),0,cosf(a),0,
			0,0,0,1
			);
		cp = cp * p;
		cn = n * cn;
	} else if(z==1){
		Matrix p(
			cosf(a),-sinf(a),0,0,
			sinf(a),cosf(a),0,0,
			0,0,1,0,
			0,0,0,1
			);
		Matrix n(
			cosf(a),sinf(a),0,0,
			-sinf(a),cosf(a),0,0,
			0,0,1,0,
			0,0,0,1
			);
		cp = cp * p;
		cn = n * cn;
	} else {
		return;
	}
}

void Matrix::scale( float x, float y, float z )
{
	Matrix p(
		x,0,0,0,
		0,y,0,0,
		0,0,z,0,
		0,0,0,1
		);
	Matrix n(
		1.0f/x,0,0,0,
		0,1.0f/y,0,0,
		0,0,1.0f/z,0,
		0,0,0,1
		);
	cp = cp * p;
	cn = n * cn;
}

void Matrix::pushMatrix()
{

}

void Matrix::popMatrix()
{
	cp=Matrix(1.0f);
	cn=Matrix(1.0f);
}

void Matrix::getMatrix( Matrix& p, Matrix& n )
{
	p=cp;
	n=cn;
}

Matrix Matrix::transpose()
{
	return Matrix(
		v[0][0],v[1][0],v[2][0],v[3][0],
		v[0][1],v[1][1],v[2][1],v[3][1],
		v[0][2],v[1][2],v[2][2],v[3][2],
		v[0][3],v[1][3],v[2][3],v[3][3]
		);
}
