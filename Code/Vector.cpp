#include "Vector.h"
#include "Matrix.h"

Vector::Vector(void)
{
	x=y=z=0;
}

Vector::Vector(const float a[])
{
	x=a[0]; y=a[1]; z=a[2];
}

Vector::Vector(float a,float b,float c)
{
	x=a; y=b; z=c;
}

Vector::Vector(const Vector& r)
{
	x=r.x; y=r.y; z=r.z;
}

Vector::~Vector(void)
{
}

Vector& Vector::normalize()
{
	*this/=length();
	return *this;
}

float Vector::length()
{
	return sqrtf(x*x+y*y+z*z);
}

Vector& Vector::operator=( const Vector& r )
{
	x=r.x; y=r.y; z=r.z;
	return *this;
}

Vector Vector::operator+( const Vector& r )
{
	return Vector(x+r.x, y+r.y, z+r.z);
}

Vector Vector::operator-( const Vector& r )
{
	return Vector(x-r.x, y-r.y, z-r.z);
}

float Vector::operator*( const Vector& r )
{
	return x*r.x+y*r.y+z*r.z;
}

Vector Vector::operator*( float t )
{
	return Vector(x*t, y*t, z*t);
}

Vector Vector::operator*(const Matrix& m)
{
	float l[4]; l[0]=x; l[1]=y; l[2]=z; l[3]=1;
	float r[4]; r[0]=r[1]=r[2]=r[3]=0;
	for(int i=0; i!=4; i++)
		for(int k=0; k!=4; k++)
			r[i] += m.v[i][k] * l[k];
	return Vector(r[0],r[1],r[2]);
}

Vector Vector::operator/( const Vector& r )	//ÕâÊÇ²æ»ý!!!
{
	return Vector(y*r.z-z*r.y, z*r.x-x*r.z, x*r.y-y*r.x);
}

Vector Vector::operator/( float t )
{
	if(t==0)
		return Vector();
	return *this * (1/t);
}

Vector& operator+=( Vector& l,const Vector& r )
{
	l.x+=r.x; l.y+=r.y; l.z+=r.z;
	return l;
}

Vector& operator-=( Vector& l,const Vector& r )
{
	l.x-=r.x; l.y-=r.y; l.z-=r.z;
	return l;
}

Vector& operator*=( Vector& l,float t )
{
	l.x*=t; l.y*=t; l.z*=t;
	return l;
}

Vector& operator/=( Vector& l,float t )
{
	if(t==0)
		return l;
	l.x/=t; l.y/=t; l.z/=t;
	return l;
}

ostream& operator<<( ostream& output, Vector& v )
{
	output<<"("<<v.x<<", "<<v.y<<", "<<v.z<<")";
	return output;
}