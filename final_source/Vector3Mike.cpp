#include "Vector3Mike.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdexcept>

Vector3Mike::Vector3Mike(double x_, double y_, double z_)
{
	x = x_; 
	y = y_; 
	z = z_; 
}

Vector3Mike::Vector3Mike()
{ 
	x=0.0; y=0.0; z=0.0;
}


double Vector3Mike::get_x()
{
	return x; 
} 

double Vector3Mike::get_y()
{
	return y; 
}

double Vector3Mike::get_z()
{
	return z; 
}

double& Vector3Mike::operator[] (const double index)
{
    if(index == 0)
	{
		return x; 
	} 
	else if(index ==1)
	{
		return y; 
	} 
	else if(index ==2)
	{
		return z; 
	}
	else
	{
		throw std::out_of_range ("Index out of bounds");
	} 
}

void Vector3Mike::operator+ (Vector3Mike &b)
{
	x+=b.x; y+=b.y; z+=b.z;
}

void Vector3Mike::operator- (Vector3Mike &a)
{
		x-=a.x; y-=a.y; z-=a.z;
}

void Vector3Mike::set(double x0,double y0,double z0) {x=x0; y=y0; z=z0;}
void Vector3Mike::add(Vector3Mike &a) {x+=a.x; y+=a.y; z+=a.z;}
void Vector3Mike::add(Vector3Mike &a,Vector3Mike &b) {x=a.x+b.x; y=a.y+b.y; z=a.z+b.z;}
void Vector3Mike::subtract(Vector3Mike &a) {x-=a.x; y-=a.y; z-=a.z;}
void Vector3Mike::subtract(Vector3Mike &a,Vector3Mike &b) {x=a.x-b.x; y=a.y-b.y; z=a.z-b.z;}
void Vector3Mike::negate() {x=-x; y=-y; z=-z;}
void Vector3Mike::negate(Vector3Mike &a) {x=-a.x; y=-a.y; z=-a.z;}
void Vector3Mike::scale(double s) {x*=s; y*=s; z*=s;}
void Vector3Mike::scale(double s,Vector3Mike &a) {x=s*a.x; y=s*a.y; z=s*a.z;}
double Vector3Mike::dot(Vector3Mike &a) {return x*a.x+y*a.y+z*a.z;}
void Vector3Mike::cross(Vector3Mike &b) { double temp_x = x; double temp_y = y; double temp_z = z;
	x=temp_y*b.z-temp_z*b.y; y=temp_z*b.x-temp_x*b.z; z=temp_x*b.y-temp_y*b.x;}
void Vector3Mike::cross(Vector3Mike &a,Vector3Mike &b) {x=a.y*b.z-a.z*b.y; y=a.z*b.x-a.x*b.z; z=a.x*b.y-a.y*b.x;}
double Vector3Mike::magnitude() {return sqrt(x*x+y*y+z*z);}
void Vector3Mike::normalize() {scale(1.0/magnitude());}
void Vector3Mike::print()
{
	std::cout<< "x:  "<<this->get_x(); 
	std::cout<< " y: "<<this->get_y(); 
	std::cout<< " z: "<<this->get_z()<<"\n"; 	
}

double Vector3Mike::angle(Vector3Mike b) {
	double dotProd = this->dot(b);
	dotProd /= this->magnitude();
	dotProd /= b.magnitude();

	return acos(dotProd);
}

Vector3Mike::~Vector3Mike(void)
{
}
