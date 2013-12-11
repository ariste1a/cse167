#pragma once
#include "ControlPoint.h"
#include "Point.h"
#include "Geode.h"
#include "Line.h"
#include "Vector4.h"
#include <math.h>

class ControlPoint;
class Point;

class Bezier :
	public Geode
{
protected:
	// Four Points for cubic lerping
	ControlPoint* p1;
	ControlPoint* p2;
	ControlPoint* p3;
	ControlPoint* p4;
	Line* line1;
	Line* line2;
	Line* line3;

	std::vector<ControlPoint*> points;
	std::vector<Line*> lines;
	std::vector<Point> curve;
	std::vector<Vector4> normals;
	std::vector<std::vector<Point>> surface;
	std::vector<std::vector<Vector4>> surfaceNormals;
	int samplePts;
	int degrees;
	bool textureOn;
	bool runOnce;
	
public:
	Bezier(ControlPoint*, ControlPoint*, ControlPoint*, ControlPoint*);
	~Bezier();
	int getSamplePts();
	std::vector<ControlPoint*> getPoints();
	std::vector<Line*> getLines();
	std::vector<Point> getCurve();
	void resetLines();
	void setSamplePts(int);
	void setDegrees(int);
	void draw(Matrix4) override;
	void toggleTexture();
	void drawCurve();

};

