#ifndef _MATRIX4_MIKE_H_
#define _MATRIX4_MIKE_H_

#include <math.h>

class Vector3Mike;
class Vector4Mike;

// Access to class Matrix4 is row-major, but values are stored internally as column-major
class Matrix4Mike
{
  protected:
    double m[4][4];   // matrix elements	column-major
    
  public:
    Matrix4Mike();        // constructor
	Matrix4Mike(Matrix4Mike&);
    Matrix4Mike(double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double);
	double get(int, int);	// get matrix element	row-major
	void set(int, int, double);  // set a matric element    row-major
	void multiply(Matrix4Mike); // matrix times matrix
	Vector4Mike multiply(Vector4Mike); // matrix times vector
	Vector3Mike multiply(Vector3Mike);
	void rotateX(double);	// rotation about x axis	angle in radians
	void rotateY(double);	// rotation about y axis	angle in radians
	void rotateZ(double);	// rotation about z axis	angle in radians
	void rotate(Vector3Mike, double);	// rotation about arbitrary axis	angle in radians
	static Matrix4Mike makeRotateX(double);	// make rotation matrix
	static Matrix4Mike makeRotateY(double);
	void Matrix4Mike::rotateY_(double angle);
	Matrix4Mike makeRotateZ(double);
	Matrix4Mike makeRotate(Vector3Mike, double);
	Matrix4Mike makeScale(double, double, double);	// make non-uniform scaling matrix
	Matrix4Mike makeScale(Vector3Mike);
	Matrix4Mike makeTranslate(double, double, double);	// make translation matrix
	Matrix4Mike makeTranslate(Vector3Mike);
	void print();	// display matrix components
	void transpose();	// transpose matrix
    double* getPointer();  // return pointer to matrix elements		returns column-major version
    void identity();  // create identity matrix
	void clear();

	void copyRot(Matrix4Mike);

	/** Rotates the matrix according to a fictitious trackball, placed in
    the middle of the given window.
    The trackball is approximated by a Gaussian curve.
    The trackball coordinate system is: x=right, y=up, z=to viewer<BR>
    The origin of the mouse coordinates zero (0,0) is considered to be top left.
	@param width, height  window size in pixels
    @param fromX, fromY   mouse starting position in pixels
    @param toX, toY       mouse end position in pixels
    */
	Matrix4Mike trackballRotation(int width, int height, int fromX, int fromY, int toX, int toY);
};

#endif