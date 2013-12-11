#include "Line.h"


Line::Line(float x1, float y1, float z1, float x2, float y2, float z2)
{
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	this->z1 = z1;
	this->z2 = z2;
}


Line::~Line()
{
}

void Line::draw(Matrix4)
{
	glLineWidth(2.5);
	glBegin(GL_LINES);

	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y2, z2);
	glEnd();
}