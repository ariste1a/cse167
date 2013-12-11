#pragma once
#include "Geode.h"

class Sphere :
	public Geode
{
protected:
	GLdouble radius;
	GLint slices;
	GLint stacks;

public:
	Sphere(char*,GLdouble, GLint, GLint);
	~Sphere();
	void draw(Matrix4) override;
};

