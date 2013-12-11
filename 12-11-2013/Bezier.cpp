#include "Bezier.h"
#include <iostream>
#define PI 3.14159265

Bezier::Bezier(ControlPoint* p1, ControlPoint* p2, ControlPoint* p3, ControlPoint* p4)
{
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->p4 = p4;
	this->line1 = new Line(p1->x, p1->y, p1->z, p2->x, p2->y, p2->z);
	this->line2 = new Line(p2->x, p2->y, p2->z, p3->x, p3->y, p3->z);
	this->line3 = new Line(p3->x, p3->y, p3->z, p4->x, p4->y, p4->z);

	samplePts = 30;
	degrees = 10;

	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
	points.push_back(p4);
	lines.push_back(line1);
	lines.push_back(line2);
	lines.push_back(line3);
	textureOn = true;
	runOnce = false;
}


Bezier::~Bezier()
{
	delete p1;
	delete p2;
	delete p3;
	delete p4;
	delete line1;
	delete line2;
	delete line3;

	points.clear();
	normals.clear();
	curve.clear();
	surface.clear();
	surfaceNormals.clear();
}

std::vector<ControlPoint*> Bezier::getPoints()
{
	return points;
}

std::vector<Line*> Bezier::getLines()
{
	return lines;
}

int Bezier::getSamplePts()
{
	return samplePts;
}

void Bezier::setSamplePts(int samples)
{
	samplePts = samples;
}

void Bezier::draw(Matrix4 m)
{
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_LIGHTING);
	glColor3f(1.0, 0.0, 0.0);
	p1->draw(m);
	p2->draw(m);
	p3->draw(m);
	p4->draw(m);
	glColor3f(0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);

	/*line1->draw(m);
	line2->draw(m);
	line3->draw(m);*/


	drawCurve();
}

void Bezier::drawCurve()
{
	float x, y, z;
	float xPrime, yPrime;

	if (!runOnce)
	{
		runOnce = true;
		curve.clear();
		normals.clear();
		glEnable(GL_LIGHTING);
		for (float t = 0; t <= 1 + (1.0 / samplePts); t += (1.0 / samplePts))
		{
			x = (-pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * p1->x +
				(3 * pow(t, 3) - 6 * pow(t, 2) + 3 * t) * p2->x +
				(-3 * pow(t, 3) + 3 * pow(t, 2)) * p3->x + (pow(t, 3)) * p4->x;

			y = (-pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * p1->y +
				(3 * pow(t, 3) - 6 * pow(t, 2) + 3 * t) * p2->y +
				(-3 * pow(t, 3) + 3 * pow(t, 2)) * p3->y + pow(t, 3) * p4->y;

			z = (-pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * p1->z +
				(3 * pow(t, 3) - 6 * pow(t, 2) + 3 * t) * p2->z +
				(-3 * pow(t, 3) + 3 * pow(t, 2)) * p3->z + pow(t, 3) * p4->z;

			xPrime = (-3 * pow(t, 2) + 6 * t - 3) * p1->x +
				(9 * pow(t, 2) - 12 * t + 3) * p2->x +
				(-9 * pow(t, 2) + 6 * t) * p3->x + 3 * pow(t, 2) * p4->x;
			yPrime = (-3 * pow(t, 2) + 6 * t - 3) * p1->y +
				(9 * pow(t, 2) - 12 * t + 3) * p2->y +
				(-9 * pow(t, 2) + 6 * t) * p3->y + 3 * pow(t, 2) * p4->y;

			normals.push_back(Vector4(-yPrime, xPrime, z));
			curve.push_back(Point(x, y, z));
		}

		// That's a lot of normal
		for (Vector4 normal : normals)
		{
			normal.normalize();
		}
	}

	/*Vector4 normal = Vector4((surface[i][j].x - surface[i][j + 1].x) / (1.0 / samplePts),
		(surface[i][j].y - surface[i][j + 1].y) / (1.0 / samplePts),
		(surface[i][j].z - surface[i][j + 1].z) / (1.0 / samplePts));
	normal.normalize();

	glNormal3f(normal.v1, normal.v2, normal.v3);*/

	/*glLineWidth(2.5);
	glBegin(GL_LINES);
	for (unsigned i = 0; i < curve.size() - 1; i++)
	{
		glVertex3f(curve[i].x, curve[i].y, curve[i].z);
		glVertex3f(curve[i + 1].x, curve[i + 1].y, curve[i + 1].z);
	}
	glEnd();*/
}

std::vector<Point> Bezier::getCurve()
{
	return curve;
}

void Bezier::setDegrees(int degrees)
{
	this->degrees = degrees;
}

void Bezier::toggleTexture()
{

	if (textureOn)
		textureOn = false;
	else
		textureOn = true;
}