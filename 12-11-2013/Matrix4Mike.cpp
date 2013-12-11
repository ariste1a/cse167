#include <math.h>

#include "Matrix4Mike.h"
#include "Vector3Mike.h"
#include "Vector4Mike.h"

Matrix4Mike::Matrix4Mike()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[i][j] = 0;
    }
  }
} 

Matrix4Mike::Matrix4Mike(Matrix4Mike &other) {
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
		m[i][j] = other.get(j, i);
    }
  }
}

Matrix4Mike::Matrix4Mike(
  double m00, double m01, double m02, double m03,
  double m10, double m11, double m12, double m13,
  double m20, double m21, double m22, double m23,
  double m30, double m31, double m32, double m33 )
{
  m[0][0] = m00;
  m[1][0] = m01;
  m[2][0] = m02;
  m[3][0] = m03;
  m[0][1] = m10;
  m[1][1] = m11;
  m[2][1] = m12;
  m[3][1] = m13;
  m[0][2] = m20;
  m[1][2] = m21;
  m[2][2] = m22;
  m[3][2] = m23;
  m[0][3] = m30;
  m[1][3] = m31;
  m[2][3] = m32;
  m[3][3] = m33;
}

double Matrix4Mike::get(int x, int y) {
	if (-1 < x && x < 4 && -1 < y && y < 4) {
		return m[y][x];
	}
	else {
		fprintf(stderr, "Invalid index");
		return -999;
	}
}

void Matrix4Mike::set(int x, int y, double value) {
	if (-1 < x && x < 4 && -1 < y && y < 4) {
		m[y][x] = value;
	}
	else {
		fprintf(stderr, "Invalid index");
	}
}

void Matrix4Mike::multiply(Matrix4Mike other) {
	double answer[4][4];

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			answer[i][j] = (m[0][i] * other.get(0, j)) + (m[1][i] * other.get(1, j)) + 
						   (m[2][i] * other.get(2, j)) + (m[3][i] * other.get(3, j));
		}
	}

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			m[j][i] = answer[i][j];
		}
	}
}

Vector4Mike Matrix4Mike::multiply(Vector4Mike other) {
	double answer[4];

	for (int i = 0; i < 4; ++i) {
		answer[i] = (m[0][i] * other[0]) + (m[1][i] * other[1]) + (m[2][i] * other[2]) + (m[3][i] * other[3]);
	}

	Vector4Mike result(answer[0], answer[1], answer[2], answer[3]);
	return result;
}

Vector3Mike Matrix4Mike::multiply(Vector3Mike other) {
	double answer[4];

	Vector4Mike other2 = Vector4Mike(other.get_x(), other.get_y(), other.get_z(), 0);
	for (int i = 0; i < 4; ++i) {
		answer[i] = (m[0][i] * other2[0]) + (m[1][i] * other2[1]) + (m[2][i] * other2[2]) + (m[3][i] * other2[3]);
	}

	Vector3Mike result(answer[0], answer[1], answer[2]);
	return result;
}

void Matrix4Mike::rotateX(double angle) {
	Vector3Mike axis(1, 0, 0);
	rotate(axis, angle);
}

void Matrix4Mike::rotateY(double angle) {
	Vector3Mike axis(0, 1, 0);
	rotate(axis, angle);
} 
	
void Matrix4Mike::rotateZ(double angle) {
	Vector3Mike axis(0, 0, 1);
	rotate(axis, angle);
}

void Matrix4Mike::rotate(Vector3Mike axis, double angle) {
	Matrix4Mike rotationMatrix = Matrix4Mike::makeRotate(axis, angle);
	rotationMatrix.multiply(*this);

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			m[j][i] = rotationMatrix.get(i, j);
		}
	}
}

Matrix4Mike Matrix4Mike::makeRotateX(double angle) {
	Matrix4Mike result(1, 0, 0, 0,
				   0, cos(angle), -sin(angle), 0,
				   0, sin(angle), cos(angle), 0,
				   0, 0, 0, 1);
	return result;
}

Matrix4Mike Matrix4Mike::makeRotateY(double angle) {
	Matrix4Mike result(cos(angle), 0, sin(angle), 0,
				   0, 1, 0, 0,
				   -sin(angle), 0, cos(angle), 0,
				   0, 0, 0, 1);
	return result;
}

/*
void Matrix4::rotateY(double angle)
{
	m[0][0] = cos(angle);
	m[0][1] = 0;
	m[0][2] = sin(angle);
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = -sin(angle);
	m[2][1] = 0;
	m[2][2] = cos(angle);
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}*/ 

Matrix4Mike Matrix4Mike::makeRotateZ(double angle) {
	Matrix4Mike result(cos(angle), -sin(angle), 0, 0,
				   sin(angle), cos(angle), 0, 0,
				   0, 0, 1, 0,
				   0, 0, 0, 1);
	return result;
}

Matrix4Mike Matrix4Mike::makeRotate(Vector3Mike axis, double angle) {
	double x = axis.get_x();
	double y = axis.get_y();
	double z = axis.get_z();
    double c = cos(angle);
	double s = sin(angle);
	//axis.normalize();
	//axis.dehomogenize();
	Matrix4Mike result(((x * x) + (c * (1 - x * x))),
				   ((x * y * (1 - c)) - (z * s)),
				   ((x * z * (1 - c)) + (y * s)), 
					0,
				   ((x * y * (1 - c)) + (z * s)), 
				   ((y * y) + (c * (1 - y * y))), 
				   ((y * z * (1 - c)) - (x * s)), 
				   0,
				   ((x * z * (1 - c)) - (y * s)),
				   ((y * z * (1 - c)) + (x * s)), 
				   ((z * z) + (c * (1 - z * z))), 
				   0,
				   0, 0, 0, 1);
	return result;
}

Matrix4Mike Matrix4Mike::makeScale(double x, double y, double z) {
	Matrix4Mike result(x, 0, 0, 0,
				   0, y, 0, 0,
				   0, 0, z, 0,
				   0, 0, 0, 1);
	return result;
}

Matrix4Mike Matrix4Mike::makeScale(Vector3Mike other) {
	return Matrix4Mike::makeScale(other.get_x(), other.get_y(), other.get_z());
}

//need to make this inherit the rest of the matrix too
Matrix4Mike Matrix4Mike::makeTranslate(double x, double y, double z) {
	Matrix4Mike result(1, 0, 0, x,
				   0, 1, 0, y,
				   0, 0, 1, z,
				   0, 0, 0, 1);
	return result;
}

Matrix4Mike Matrix4Mike::makeTranslate(Vector3Mike other) {
	return Matrix4Mike::makeTranslate(other.get_x(), other.get_y(), other.get_z());
}

void Matrix4Mike::print() {
	fprintf(stdout, "Matrix elements:\n  %5.2f  %5.2f  %5.2f  %5.2f\n  %5.2f  %5.2f  %5.2f  %5.2f\n  %5.2f  %5.2f  %5.2f  %5.2f\n  %5.2f  %5.2f  %5.2f  %5.2f\n",
			m[0][0], m[1][0], m[2][0], m[3][0], m[0][1], m[1][1], m[2][1], m[3][1], m[0][2], m[1][2], m[2][2], m[3][2], m[0][3], m[1][3], m[2][3], m[3][3]);
}
	
void Matrix4Mike::transpose() {
	double copy[4][4];

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			copy[i][j] = m[i][j];
		}
	}

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			m[i][j] = copy[j][i];
		}
	}
}


double* Matrix4Mike::getPointer()
{
  return &m[0][0];
}

void Matrix4Mike::identity()
{
  double ident[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[j][i] = ident[i][j];
    }
  }
}

void Matrix4Mike::clear()
{
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			m[i][j] = 0;
		}
	}
}

void Matrix4Mike::copyRot(Matrix4Mike b) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			this->set(i, j, b.get(i, j));
		}
	}
}

/** Rotates the matrix according to a fictitious trackball, placed in
    the middle of the given window.
    The trackball is approximated by a Gaussian curve.
    The trackball coordinate system is: x=right, y=up, z=to viewer<BR>
    The origin of the mouse coordinates zero (0,0) is considered to be top left.
    @param width, height  window size in pixels
    @param fromX, fromY   mouse starting position in pixels
    @param toX, toY       mouse end position in pixels
*/
Matrix4Mike Matrix4Mike::trackballRotation(int width, int height, int fromX, int fromY, int toX, int toY) {
  const float TRACKBALL_SIZE = 1.3f;              // virtual trackball size (empirical value)
  Matrix4Mike mInv;                                   // inverse of ObjectView matrix
  Vector3Mike v1, v2;                                 // mouse drag positions in normalized 3D space
  float smallSize;                                // smaller window size between width and height
  float halfWidth, halfHeight;                    // half window sizes
  float angle;                                    // rotational angle
  float d;                                        // distance

  // Compute mouse coordinates in window and normalized to -1..1
  // ((0,0)=window center, (-1,-1) = bottom left, (1,1) = top right)
  halfWidth   = (float)width  / 2.0f;
  halfHeight  = (float)height / 2.0f;
  smallSize   = (halfWidth < halfHeight) ? halfWidth : halfHeight;
  v1[0]       = ((float)fromX - halfWidth)  / smallSize;
  v1[1]       = ((float)(height-fromY) - halfHeight) / smallSize;
  v2[0]       = ((float)toX   - halfWidth)  / smallSize;
  v2[1]       = ((float)(height-toY)   - halfHeight) / smallSize;

  // Compute z-coordinates on Gaussian trackball:
  d       = sqrtf(v1[0] * v1[0] + v1[1] * v1[1]);
  v1[2]   = expf(-TRACKBALL_SIZE * d * d);
  d       = sqrtf(v2[0] * v2[0] + v2[1] * v2[1]);
  v2[2]   = expf(-TRACKBALL_SIZE * d * d);

  // Compute rotational angle:
  angle = v1.angle(v2);                          // angle = angle between v1 and v2

  // Compute rotational axis:
  v2.cross(v1);                                  // v2 = v2 x v1 (cross product)

  // Convert axis coordinates (v2) from WCS to OCS:
  mInv.identity();
  //mInv.copyRot(*this);                             // copy rotational part of mv to mInv
  mInv.transpose();
  //mInv.invertOrtho();                             // invert orthogonal matrix mInv
  //v2.multiply(&mInv);                             // v2 = v2 x mInv (matrix multiplication)
  Vector4Mike v2_(v2[0], v2[1], v2[2], 0);
  v2_ = mInv.multiply(v2_);
  v2 = Vector3Mike(v2_.get('x'), v2_.get('y'), v2_.get('z'));
  v2.normalize();                                 // normalize v2 before rotation
  
  // Perform acutal model view matrix modification:
  return this->makeRotate(v2, -angle);
  //return rotate(-angle, v2[0], v2[1], v2[2]);      // rotate model view matrix
}