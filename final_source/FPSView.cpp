#include "FPSView.h"
#include "Camera.h"

/**
 * Default constructor.
 * Camera at (0, 0, 1), looking at (0, 0, 0).
 */
FPSView::FPSView(void) :
	mEye(0, 0, 1),
	mCenter(0, 0, 0),
	mUp(0, 1, 0)
{
	setup();
}

/**
 * Constructor taking Vector3Mike parameters for eye, center, and up.
 */
FPSView::FPSView(Vector3Mike eye, Vector3Mike center, Vector3Mike up) :
	mEye(eye),
	mCenter(center),
	mUp(up)
{
	setup();
}

/**
 * Constructor taking in components of eye, center, and up.
 */
FPSView::FPSView(double eye0, double eye1, double eye2,
		double center0, double center1, double center2,
		double up0, double up1, double up2) :
	mEye(eye0, eye1, eye2),
	mCenter(center0, center1, center2),
	mUp(up0, up1, up2)
{
	setup();
}

//Vector3Mike getEye
FPSView::~FPSView(void) {
}

/**
 * Helper method to construct view direction and x axis.
 */
void FPSView::setup() {
	mDirection = mCenter;
	mDirection.subtract(mEye);
	mDirection.normalize();

	mXZDirection = Vector3Mike(mDirection.get_x(), 0, mDirection.get_z());
	mXZDirection.normalize();
	mScaleXZDirection = mXZDirection;
	mScaleXZDirection.scale(2);

	Vector3Mike zero(0, 0, 0);

	mLeft = mXZDirection;
	mLeft.cross(mUp);
	mLeft.normalize();

	zero.subtract(mLeft);
	mLeft = zero;

	mScaleLeft = mLeft;
	mScaleLeft.scale(2);

	mXAxis = mLeft;

	mDirection.scale(.1);
	mXZDirection.scale(.1);
	mScaleXZDirection.scale(.1);
	mLeft.scale(.1);
	mScaleLeft.scale(.1);
}

/**
 * Walk forward.
 *
 * @param map	Collision map
 */
void FPSView::walkForward(CollisionMap2D &map) {
	mEye.add(mXZDirection);
	mCenter.add(mXZDirection);

	if (!checkPos(map)) {
		mEye.subtract(mXZDirection);
		mCenter.subtract(mXZDirection);
	}
}

/**
 * Walk backward.
 *
 * @param map	Collision map
 */
void FPSView::walkBack(CollisionMap2D &map) {
	mEye.subtract(mXZDirection);
	mCenter.subtract(mXZDirection);

	if (!checkPos(map)) {
		mEye.add(mXZDirection);
		mCenter.add(mXZDirection);
	}
}

/**
 * Walk left.
 *
 * @param map	Collision map
 */
void FPSView::walkLeft(CollisionMap2D &map) {
	mEye.add(mLeft);
	mCenter.add(mLeft);

	if (!checkPos(map)) {
		mEye.subtract(mLeft);
		mCenter.subtract(mLeft);
	}
}

/**
 * Walk right.
 *
 * @param map	Collision map
 */
void FPSView::walkRight(CollisionMap2D &map) {
	mEye.subtract(mLeft);
	mCenter.subtract(mLeft);

	if (!checkPos(map)) {
		mEye.add(mLeft);
		mCenter.add(mLeft);
	}
}

/**
 * Sprint forward.
 *
 * @param map	Collision map
 */
void FPSView::sprintForward(CollisionMap2D &map) {
	mEye.add(mScaleXZDirection);
	mCenter.add(mScaleXZDirection);

	if (!checkPos(map)) {
		mEye.subtract(mScaleXZDirection);
		mCenter.subtract(mScaleXZDirection);
	}
}

/**
 * Sprint backward.
 *
 * @param map	Collision map
 */
void FPSView::sprintBack(CollisionMap2D &map) {
	mEye.subtract(mScaleXZDirection);
	mCenter.subtract(mScaleXZDirection);

	if (!checkPos(map)) {
		mEye.add(mScaleXZDirection);
		mCenter.add(mScaleXZDirection);
	}
}

/**
 * Sprint left.
 *
 * @param map	Collision map
 */
void FPSView::sprintLeft(CollisionMap2D &map) {
	mEye.add(mScaleLeft);
	mCenter.add(mScaleLeft);

	if (!checkPos(map)) {
		mEye.subtract(mScaleLeft);
		mCenter.subtract(mScaleLeft);
	}
}

/**
 * Sprint right.
 *
 * @param map	Collision map
 */
void FPSView::sprintRight(CollisionMap2D &map) {
	mEye.subtract(mScaleLeft);
	mCenter.subtract(mScaleLeft);

	if (!checkPos(map)) {
		mEye.add(mScaleLeft);
		mCenter.add(mScaleLeft);
	}
}

/**
 * Move in arbitrary direction.
 *
 * @param dir	Direction and distance to move.
 * @param map	Collision map
 */
void FPSView::move(Vector3Mike dir, CollisionMap2D &map) {
	dir = Vector3Mike(dir.get_x(), 0, dir.get_z());
	mEye.add(dir);
	mCenter.add(dir);

	if (!checkPos(map)) {
		mEye.subtract(dir);
		mCenter.subtract(dir);
	}
}

/**
 * Move in arbitrary direction.
 *
 * @param x		X distance to move.
 * @param y		Y distance to move.
 * @param z		Z distance to move.
 * @param map	Collision map
 */
void FPSView::move(double x, double y, double z, CollisionMap2D &map) {
	Vector3Mike dir(x, 0, z);
	mEye.add(dir);
	mCenter.add(dir);

	if (!checkPos(map)) {
		mEye.subtract(dir);
		mCenter.subtract(dir);
	}
}

/**
 * Change view direction.
 *
 * @param x		Change in x
 * @param y		Change in y
 */
void FPSView::changeView(double x, double y) {
	Matrix4Mike change;
	Matrix4Mike rotateX;
	Matrix4Mike rotateY;

	rotateX = change.makeRotateY(- x * 0.005);
	rotateY = change.makeRotate(mXAxis, y * 0.005);

	mDirection = rotateY.multiply(mDirection);
	mUp = rotateY.multiply(mUp);

	mDirection = rotateX.multiply(mDirection);
	mXZDirection = rotateX.multiply(mXZDirection);
	mScaleXZDirection = rotateX.multiply(mScaleXZDirection);
	mLeft = rotateX.multiply(mLeft);
	mScaleLeft = rotateX.multiply(mScaleLeft);
	mUp = rotateX.multiply(mUp);
	mXAxis = rotateX.multiply(mXAxis);

	mCenter = mEye;
	mCenter.add(mDirection);
}

/**
 * Mimic gluLookAt().
 */
void FPSView::lookAt() {
	gluLookAt(mEye.get_x(), mEye.get_y(), mEye.get_z(), 
			  mCenter.get_x(), mCenter.get_y(), mCenter.get_z(), 
			  mUp.get_x(), mUp.get_y(), mUp.get_z());
	
}

/**
 * Check if current location is valid on collision map.
 *
 * @param map		Collision map
 *
 * @return			True of valid, false if collision.
 */
bool FPSView::checkPos(CollisionMap2D &map) {
	return !(map.checkPoint(mEye.get_x() * 100, mEye.get_z() * 100));
}

/**
* Print cam values.
*/
void FPSView::print() {
	mEye.print();
	mCenter.print();
	mUp.print();
	fprintf(stderr, "\n");
}