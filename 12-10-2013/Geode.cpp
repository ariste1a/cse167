#include "Geode.h"


Geode::Geode()
{
}


Geode::~Geode()
{
}

bool Geode::testSphere(Vector4 normal, Vector4 point, Geode* shape)
{
	double distance = (shape->center - point).multiply(normal);
	if (distance > shape->boundRadius)
		return false;
	else
		return true;

}

/*void Geode::draw(Matrix4)
{

}*/