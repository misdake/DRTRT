#include "Painter.h"

#include <Windows.h>
#include "../GL Lib/glut.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
using std::ifstream;
using std::istringstream;
using std::string;
using std::cout;
using std::endl;

Painter::Painter(void)
{
}


Painter::~Painter(void)
{
}

void Painter::load( string fileName )
{/*
	Sphere* p;

	Matrix::translate(0,1,1);
	p= new Sphere();
	p->x=0; p->y=0; p->z=0; p->r=1;
	p->color=Vector(1,1,1);
	p->getMatrix();
	objList.push_back(p);

	Matrix::popMatrix();
	Matrix::scale(1,0.1,0.2);
	p = new Sphere();
	p->x=0; p->y=0; p->z=0; p->r=1;
	p->color=Vector(1,1,1);
	p->getMatrix();
	objList.push_back(p);*/

	vector<Vector> originalVertices;
	Mesh* currentMesh = 0;

	ifstream input(fileName);
	char line[512];
	while(input.getline(line,512)) {
		if(line[0]=='#' || line[0]=='\0')
			continue;
		istringstream l(line);
		string s;
		l>>s;
		       if(s == "size") {
			l>>width>>height;
		} else if(s == "maxdepth") {
			//作用不大 没实现
		} else if(s == "output") {
			//没实现
		} else if(s == "camera") {
			float x,y,z;
			l>>x>>y>>z;
			setCameraPosition(x,y,z);
			l>>x>>y>>z;
			setCameraTarget(x,y,z);
			l>>x>>y>>z;
			setCameraUp(x,y,z);
			l>>x;
			setCameraFov(x/180*pi);
		} else if(s == "sphere") {
			float x,y,z,r;
			l>>x>>y>>z>>r;
			Sphere* p = new Sphere();
			p->x=x; p->y=y; p->z=z; p->r=r;
			p->color=currentColor;
			p->getMatrix();
			objList.push_back(p);
		} else if(s == "maxverts") {
			//用了自增长数组，不必实现
		} else if(s == "maxvertnormals") {
			//用了自增长数组，不必实现
		} else if(s == "vertex") {
			float x,y,z;
			l>>x>>y>>z;
			originalVertices.push_back(Vector(x,y,z));
		} else if(s == "tri") {
			if(!currentMesh) {
				currentMesh = new Mesh();
				currentMesh->getMatrix();
				currentMesh->color = currentColor;
				objList.push_back(currentMesh);
			}
			float x,y,z;
			l>>x>>y>>z;
			Vector* v = new Vector[3];
			v[0]=originalVertices[x]; v[1]=originalVertices[y]; v[2]=originalVertices[z];
			Vector& min=currentMesh->min; Vector& max=currentMesh->max;
			for(int j=0; j!=3; j++) {
				v[j] = v[j] * currentMesh->p;
				if(v[j].x<min.x) min.x = v[j].x;
				if(v[j].y<min.y) min.y = v[j].y;
				if(v[j].z<min.z) min.z = v[j].z;
				if(v[j].x>max.x) max.x = v[j].x;
				if(v[j].y>max.y) max.y = v[j].y;
				if(v[j].z>max.z) max.z = v[j].z;
			}
			currentMesh->vertex.push_back(v);
		} else if(s == "trinormal") {
			//没实现
		} else if(s == "translate") {
			currentMesh=0;
			float x,y,z; l>>x>>y>>z;
			Matrix::translate(x,y,z);
		} else if(s == "rotate") {
			currentMesh=0;
			float x,y,z,a; l>>x>>y>>z>>a;
			Matrix::rotate(x,y,z,a);
		} else if(s == "scale") {
			currentMesh=0;
			float x,y,z; l>>x>>y>>z;
			Matrix::scale(x,y,z);
		} else if(s == "pushTransform") {
			Matrix::pushMatrix();
		} else if(s == "popTransform") {
			currentMesh=0;
			Matrix::popMatrix();
		} else if(s == "directional") {
			//没实现
		} else if(s == "point") {
			//没实现
		} else if(s == "attenuation") {
			//没实现
		} else if(s == "ambient") {
			currentMesh=0;
			float x,y,z; l>>x>>y>>z;
			currentColor=Vector(x,y,z);
		} else if(s == "diffuse") {
			currentMesh=0;
			float x,y,z; l>>x>>y>>z;
			currentColor+=Vector(x,y,z);
		} else if(s == "specular") {
			//没实现
		} else if(s == "shininess") {
			//没实现
		} else if(s == "emission") {
			//没实现
		}
	}
}

void Painter::paint(bool enableSSAA)
{
	static long time = timeGetTime();

	glClear(GL_COLOR_BUFFER_BIT);

	Vector eyeRay(camTarget-camPosition);
	float hl=tanf(fov/2)*eyeRay.length();
	float wl=hl*width/height;
	w=(camUp/eyeRay);	//这是叉积!!!
	h=(eyeRay/w);	//这是叉积!!!
	w.normalize();
	w*=-wl;
	h.normalize();
	h*=hl;

	static float* frameBuffer;
	if(frameBuffer == 0)
		frameBuffer = new float[height * width * 3];

	for(int j=height-1; j>=0; j--) {
		for(int i=0; i!=width; i++) {
			Vector color(0,0,0);
			float x,y;

			if(enableSSAA) {
				x=(i+0.5f   -0.25f   )/width*2-1.0f; y=(j+0.5f   -0.25f   )/height*2-1.0f;
				color += paint(camTarget + w*x + h*y - camPosition) * 0.25f;
				x=(i+0.5f   +0.25f   )/width*2-1.0f; y=(j+0.5f   -0.25f   )/height*2-1.0f;
				color += paint(camTarget + w*x + h*y - camPosition) * 0.25f;
				x=(i+0.5f   -0.25f   )/width*2-1.0f; y=(j+0.5f   +0.25f   )/height*2-1.0f;
				color += paint(camTarget + w*x + h*y - camPosition) * 0.25f;
				x=(i+0.5f   +0.25f   )/width*2-1.0f; y=(j+0.5f   +0.25f   )/height*2-1.0f;
				color += paint(camTarget + w*x + h*y - camPosition) * 0.25f;
			} else {
				x=(i+0.5f)/width*2-1.0f; y=(j+0.5f)/height*2-1.0f;
				color = paint(camTarget + w*x + h*y - camPosition);
			}
			float* c = &frameBuffer[j * width * 3 + i * 3];
			c[0] = color.x; c[1] = color.y; c[2] = color.z;
		}
	}

	cout << timeGetTime() - time << endl;
	long time2 = timeGetTime();
	/*
	glPointSize(1);
	glBegin(GL_POINT);
	for (int j = 0; j != height; j++) {
		for (int i = 0; i != width; i++) {
			float x, y;
			x = (i + 0.5f) / width * 2 - 1.0f; y = (j + 0.5f) / height * 2 - 1.0f;
			glColor3f(
				frameBuffer[j * width * 3 + i * 3 + 0],
				frameBuffer[j * width * 3 + i * 3 + 1],
				frameBuffer[j * width * 3 + i * 3 + 2]);
			glVertex2f(x, y);
		}
	}
	glEnd();
	*/
	glColor3f(1.0f, 1.0f, 1.0f);
	glDrawPixels(width, height, GL_RGB, GL_FLOAT, frameBuffer);

	cout << time2 - time << endl;

	time = time2;
	glutSwapBuffers();
}

Vector Painter::paint( Vector& ray )
{
	ray.normalize();
	float z=1000.0f;
	Vector color(0,0,0);
	Vector a,b;
	for(int i=0; i!=objList.size(); i++) {
		float d=z; Vector n;
		bool hit = objList[i]->rayTest(camPosition, ray, 1000.0f,d,a,n);
		if(hit && (d<z)) {
			color=objList[i]->color;
			//color=Vector(1-d/20,1-d/20,1-d/20);	//这句话用来画深度图
			z=d;
		}
	}
	return color;
}

void Painter::unload()
{
	for(int i=0; i!=objList.size(); i++)
		delete objList[i];
}
