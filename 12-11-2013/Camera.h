#pragma once
#include <GL/glut.h>
#include "Matrix4.h"
#include "Vector4.h"
class Camera
{
protected:
	Vector4 e; // center of projection
	Vector4 d; // look at point
	Vector4 up; // up vector
	Vector4 x;
	Vector4 y;
	Vector4 z;
	Matrix4 C; // Internal camera matrix
	Matrix4 Cinv; // Inverse of internal camera matrix

public:
	Matrix4& getMatrix();
	Camera();
	Camera(Vector4, Vector4, Vector4);
	~Camera();
	void setMatrix(Matrix4);
	void setCamera(Vector4, Vector4, Vector4);
	GLdouble* getGLMatrix();

};

