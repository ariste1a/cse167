#include <math.h>
#include "Camera.h"

Camera::Camera()
{
	e = Vector4();
	d = Vector4();
	up = Vector4();
	x = Vector4();
	y = Vector4();
	z = Vector4();
	C = Matrix4();
	Cinv = Matrix4();
}

Camera::Camera(Vector4 ee, Vector4 dd, Vector4 newup)
{
	e = ee;
	d = dd;
	up = newup;

	Vector4 zz = e - d;
	z.setV1(zz.getV1() / zz.magnitude());
	z.setV2(zz.getV2() / zz.magnitude());
	z.setV3(zz.getV3() / zz.magnitude());
	z.setW(zz.getW() / zz.magnitude());
	Vector4 temp1 = z;

	Vector4 temp2 = up;

	temp2.crossProduct(z);
	
	x = temp2;
	x.setV1(x.getV1() / x.magnitude());
	x.setV2(x.getV2() / x.magnitude());
	x.setV3(x.getV3() / x.magnitude());
	x.setW(x.getW() / x.magnitude());

	temp1.crossProduct(x);
	y = temp1;

	// pg 146
	// use vector4
	C = Matrix4(x.getV1(), x.getV2(), x.getV3(), 0,
				y.getV1(), y.getV2(), y.getV3(), 0,
				z.getV1(), z.getV2(), z.getV3(), 0,
				e.getV1(), e.getV2(), e.getV3(), 1);

	Matrix4 rotationInv = Matrix4(  x.getV1(), y.getV1(), z.getV1(), 0,
									x.getV2(), y.getV2(), z.getV2(), 0,
									x.getV3(), y.getV3(), z.getV3(), 0,
									0, 0, 0, 1);


	Matrix4 translationInv = Matrix4(1, 0, 0, -e.getV1(),
		0, 1, 0, -e.getV2(),
		0, 0, 1, -e.getV3(),
										0, 0, 0, 1);

	Cinv = rotationInv.multiply(translationInv);
}

void Camera::setCamera(Vector4 ee, Vector4 dd, Vector4 newup)
{
	e = ee;
	d = dd;
	up = newup;

	Vector4 zz = e - d;
	z.setV1(zz.getV1() / zz.magnitude());
	z.setV2(zz.getV2() / zz.magnitude());
	z.setV3(zz.getV3() / zz.magnitude());
	z.setW(zz.getW() / zz.magnitude());
	Vector4 temp1 = z;

	Vector4 temp2 = up;

	temp2.crossProduct(z);

	x = temp2;
	x.setV1(x.getV1() / x.magnitude());
	x.setV2(x.getV2() / x.magnitude());
	x.setV3(x.getV3() / x.magnitude());
	x.setW(x.getW() / x.magnitude());

	temp1.crossProduct(x);
	y = temp1;

	// pg 146
	// use vector4
	C = Matrix4(x.getV1(), x.getV2(), x.getV3(), 0,
		y.getV1(), y.getV2(), y.getV3(), 0,
		z.getV1(), z.getV2(), z.getV3(), 0,
		e.getV1(), e.getV2(), e.getV3(), 1);

	Matrix4 rotationInv = Matrix4(x.getV1(), y.getV1(), z.getV1(), 0,
		x.getV2(), y.getV2(), z.getV2(), 0,
		x.getV3(), y.getV3(), z.getV3(), 0,
		0, 0, 0, 1);


	Matrix4 translationInv = Matrix4(1, 0, 0, -e.getV1(),
		0, 1, 0, -e.getV2(),
		0, 0, 1, -e.getV3(),
		0, 0, 0, 1);

	Cinv = rotationInv.multiply(translationInv);
}

Matrix4& Camera::getMatrix()
{
	return Cinv;
}

void Camera::setMatrix(Matrix4 matrix)
{
	Cinv = matrix;
}

GLdouble* Camera::getGLMatrix()
{
	/*double camMatrix[4][4];
	
	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 4; ++j)
		{
			camMatrix[i][j]= 
		}
	}*/

	GLdouble m[16];
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m[4 * i + j] = Cinv.getElement(i, j);
		}
	}
	return m;
}

Camera::~Camera()
{
}
