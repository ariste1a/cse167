#ifndef _VECTOR3_MIKE_H_
#define _VECTOR3_MIKE_H_


class Vector3Mike
{
private: 
	double x, y, z; 
public:
	Vector3Mike(double x_, double y_, double z_);
	Vector3Mike();
	void set(double x, double y, double z);
	double get_x(); 
	double get_y(); 
	double get_z(); 
	double& operator[] (const double index);
	void operator+ (Vector3Mike &b);
	void add(Vector3Mike &a);
	void add(Vector3Mike &a, Vector3Mike &b);
	void operator-(Vector3Mike &a);
	void subtract(Vector3Mike &a);
	void subtract(Vector3Mike &a, Vector3Mike &b);
	void negate(); 
	void negate(Vector3Mike &a);
	void scale(double s);
	void scale(double s, Vector3Mike &a);
	double dot(Vector3Mike &a);
	void cross(Vector3Mike &b);
	void cross(Vector3Mike &a, Vector3Mike &b);
	double magnitude();
	void normalize();
	void Vector3Mike::print();
	double angle(Vector3Mike b);
	~Vector3Mike(void);
};

#endif