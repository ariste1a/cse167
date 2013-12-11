#pragma once
#include "Geode.h"
#include <vector>

class Line :
	public Geode
{
protected:
	int x1, y1, x2, y2, z1, z2;
public:
	Line(float,float,float,float,float,float);

	~Line();

	void draw(Matrix4) override;

	friend class Bezier;
};

