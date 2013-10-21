#include "Mesh.h"


Mesh::Mesh(void)
{
	min = Vector(1000.0f,1000.0f,1000.0f);
	max = Vector(-1000.0f,-1000.0f,-1000.0f);
}


Mesh::~Mesh(void)
{
}

bool Mesh::rayTest( Vector start, Vector d, float zMax, float& distance, Vector& hitPosition, Vector& normal )
{
	d *= 10.0f;
	bool hit=false;
	float z=1000.0f;
	for(int i=0; i!=vertex.size(); i++) {
//test bounding box
		Vector p0 = start;
		Vector p1 = start + d*100.0f;
		//-------------------------------------------------
		//from book <<Real-Time Collision Detection>> 5.3.3
		//Nice book, don't you think?
		Vector e = max - min;
		Vector d = p1 - p0;
		Vector m = p0 + p1 - min - max;

		float adx = abs(d.x);
		if(abs(m.x>e.x+adx)) return false;
		float ady = abs(d.y);
		if(abs(m.y)>e.y+ady) return false;
		float adz=abs(d.z);
		if(abs(m.z)>e.z+adz) return false;

		adx += 0.0001f; ady += 0.0001f; adz += 0.0001f;
		if(abs(m.y*d.z-m.z*d.y)>e.y*adz+e.z*ady) return false;
		if(abs(m.z*d.x-m.x*d.z)>e.x*adz+e.z*adx) return false;
		if(abs(m.x*d.y-m.y*d.x)>e.x*ady+e.y*adx) return false;
		//-------------------------------------------------

//test mesh
		Vector* v3=vertex[i];
		//-------------------------------------------------
		//from book <<Real-Time Collision Detection>> 5.3.4
		Vector& a=v3[0]; Vector& b=v3[1]; Vector& c=v3[2];
		Vector p = d / start;	//cross
		float s = p * (c-b);
		float t = p * (a-c);
		float u = d * (c/b) + s; //cross
		float v = d * (a/c) + t;
		float w = d * (b/a) - s - t;
		if(u<0 || v<0 || w<0)
			continue;
		
		float denom = 1.0f / (u + v + w);
		u*=denom; v*=denom; w*=denom;

		hitPosition = a*u+b*v+c*w;
		distance = (hitPosition-start).length();
		//-------------------------------------------------
		if(distance<z)
			z=distance;
	}
	return (z<999.0f);
}
