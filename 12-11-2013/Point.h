#pragma once
class Point
{
protected:
	float x;
	float y;
	float z;
public:
	Point(float, float, float);
	float getX();
	float getY();
	float getZ();
	void setXYZ(float, float, float);
	~Point();
	friend class Bezier;
};

