#pragma once

#include "Group.h"

class MatrixTransform :
	public Group
{
protected:
	Matrix4 M;
public:
	MatrixTransform(Matrix4);
	~MatrixTransform();
	void draw(Matrix4) override;
	void setM(Matrix4);
	Matrix4 getM();
};

