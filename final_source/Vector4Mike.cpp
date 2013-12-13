#include "Vector4Mike.h"

Vector4Mike::Vector4Mike() :
	x(0),
	y(0),
	z(0),
	w(0)
{
}

Vector4Mike::Vector4Mike(double _x, double _y, double _z) :
	x(_x),
	y(_y),
	z(_z),
	w(0.0)
{
}

Vector4Mike::Vector4Mike(double _x, double _y, double _z, double _w) :
	x(_x),
	y(_y),
	z(_z),
	w(_w)
{
}

Vector4Mike::~Vector4Mike(void)
{
}

void Vector4Mike::set(char c, double d) {
	switch (c) {
	case 'x':
		x = d;
		break;
	case 'y':
		y = d;
		break;
	case 'z':
		z = d;
		break;
	case 'w':
		w = d;
		break;
	default:
		fprintf(stderr, "Invalid character\n");
		break;
	}
}


double Vector4Mike::get(char c) {
	switch (c) {
	case 'x':
		return x;
	case 'y':
		return y;
	case 'z':
		return z;
	case 'w':
		return w;
	default:
		fprintf(stderr, "Invalid character\n");
		break;
	}
}

double Vector4Mike::operator[](int index) {
	switch (index) {
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	case 3:
		return w;
	default:
		fprintf(stderr, "Invalid index\n");
		break;
	}	
}

void Vector4Mike::add(Vector4Mike other) {
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	this->w += other.w;
}

void Vector4Mike::operator+(Vector4Mike other) {
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	this->w += other.w;
}

void Vector4Mike::subtract(Vector4Mike other) {
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	this->w -= other.w;
}
	
void Vector4Mike::operator-(Vector4Mike other) {
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	this->w -= other.w;
}

void Vector4Mike::dehomogenize() {
	x /= w;
	y /= w;
	z /= w;
	w = 1;
}

void Vector4Mike::print() {
	fprintf(stdout, "x: %f\ny: %f\nz: %f\nw: %f\n", x, y, z, w);
}