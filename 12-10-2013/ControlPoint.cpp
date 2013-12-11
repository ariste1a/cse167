#include "ControlPoint.h"


ControlPoint::ControlPoint(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	drawPoint = false;
}


ControlPoint::~ControlPoint()
{
}

void ControlPoint::setXYZ(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float ControlPoint::getX()
{
	return x;
}

float ControlPoint::getY()
{
	return y;
}

float ControlPoint::getZ()
{
	return z;
}

void ControlPoint::setDraw(bool draw)
{
	this->drawPoint = draw;
}

void ControlPoint::draw(Matrix4 m)
{
	glPointSize(6);
	glColor3f(0, 1, 1);
	if (drawPoint)
	{
		glBegin(GL_POINTS);

		glVertex3f(x, y, z);

		glEnd();
	}


}