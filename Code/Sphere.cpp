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
	target = target * n;	//��ray��任һ�� �������ı�����Ȼ������������� �жϽ������֮�¾����׶���
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

	//normal = (hitPosition - Vector(x,y,z)) * n.transpose();	//��ķ�������ת�ñ任 ��Ը�ǶԵ�
	hitPosition = hitPosition * p;	//�ѽ�����б任 �õ���ʵ�Ľ���λ�� �����ʵ����
	distance = (hitPosition - oldStart).length();
	return true;
}
