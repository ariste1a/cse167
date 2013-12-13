#include "Sphere.h"


Sphere::Sphere(char* c, GLdouble radius, GLint slices, GLint stacks)
{
	name = c;
	this->radius = radius;
	this->slices = slices;
	this->stacks = stacks;
	skip = false;
}


Sphere::~Sphere()
{
}

void Sphere::draw(Matrix4 C)
{
	//Matrix4 temp = Matrix4();
	//temp.identity();

	//glLoadMatrixd(C.getPointer());
	//glTranslatef(C.getElement(0, 3), C.getElement(1, 3), C.getElement(2, 3));
	if (skip)
		return;
	else
		glutSolidSphere(radius, slices, stacks);

}

