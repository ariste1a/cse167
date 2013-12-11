#pragma once
#include "Node.h"
#include "Vector4.h"
#include <GL/glut.h>
class Geode :
	public Node
{
protected:
	char* name;

public:
	double boundRadius;
	Vector4 center;
	bool skip;
	Geode();
	~Geode();
	virtual void draw(Matrix4) = 0;
	//virtual void boundingSphere(Matrix4) = 0;
	static bool testSphere(Vector4, Vector4, Geode*);
};

