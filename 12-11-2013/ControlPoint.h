#pragma once
#include "Geode.h"

class ControlPoint : 
	public Geode
{
protected:
	float x;
	float y;
	float z;
	bool drawPoint;

public:
	ControlPoint(float,float,float);
	~ControlPoint();
	void setXYZ(float, float,float);
	void setMoving(bool);
	float getX();
	float getY();
	float getZ();
	void setDraw(bool);
	void draw(Matrix4) override;
	friend class Bezier;
};

