#include "Sphere.h"

Sphere::Sphere(void)
{
}


Sphere::~Sphere(void)
{
}

bool Sphere::rayTest( Vector start, Vector direction, float zMax, float& distance, Vector& hitPosition, Vector& normal)
{
	Vector oldStart = start;
	Vector target = start + direction*100.0f;
	target = target * n;	//把ray逆变换一下 这样检测的本体仍然是球而不是椭球 判断交点相比之下就容易多了
	start = start * n;
	direction = (target-start).normalize();

	//-------------------------------------------------
	//from book <<Real-Time Collision Detection>> 5.3.2
	Vector m = start - Vector(x,y,z);
	float b = m * direction;
	float c = m * m - r * r;
	if(c>0 && b>0) return false;
	float discr = b*b-c;
	if(discr<0) return false;
	distance = -b - sqrt(discr);
	if(distance<0) distance=0;
	hitPosition = start + direction * distance;
	//-------------------------------------------------

	//normal = (hitPosition - Vector(x,y,z)) * n.transpose();	//球的法线做逆转置变换 但愿是对的
	hitPosition = hitPosition * p;	//把交点进行变换 得到真实的交点位置 求出真实距离
	distance = (hitPosition - oldStart).length();
	return true;
}
