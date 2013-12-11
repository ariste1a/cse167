#ifndef _VECTOR4_MIKE_H_
#define _VECTOR4_MIKE_H_

#include <stdio.h>

class Vector4Mike
{
private:
	double x, y, z, w;

public:
	Vector4Mike();
	Vector4Mike(double, double, double);	// Constructor
	Vector4Mike(double, double, double, double);
	void set(char, double);	// Set specific coordinate
	double get(char); // Get specific coordinate
	double operator[](int);	// Alternative to get
	void add(Vector4Mike);	// Add vector
	void operator+(Vector4Mike);
	void subtract(Vector4Mike);	// Subtract
	void operator-(Vector4Mike);
	void dehomogenize();	// Make fourth component equal to 1
	void print();

	~Vector4Mike();	// Destructor


};

#endif _VECTOR4_MIKE_H_

