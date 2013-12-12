#pragma once

#include <GL/glut.h>

#include "Matrix4Mike.h"
#include "Vector3Mike.h"
#include "Vector4Mike.h"
#include "CollisionMap2D.h"

/**
 * Represents a first person view camera. Camera position can be moved along
 * the XZ plane, and view direction can be moved along the XY plane relative to the screen.
 * Call lookAt to place scene in viewpoint of the camera.
 */
class FPSView
{
public:
	/**
	 * Default constructor.
	 * Camera at (0, 0, 1), looking at (0, 0, 0).
	 */
	FPSView(void);

	/**
	 * Constructor taking Vector3Mike parameters for eye, center, and up.
	 */
	FPSView(Vector3Mike eye, Vector3Mike center, Vector3Mike up);

	/**
	 * Constructor taking in components of eye, center, and up.
	 */
	FPSView(double eye0, double eye1, double eye2,
			double center0, double center1, double center2,
			double up0, double up1, double up2);

	~FPSView(void);

	/**
	 * Helper method to construct view direction and x axis.
	 */
	void setup();

	/**
	 * Walk forward.
	 *
	 * @param map	Collision map
	 */
	void walkForward(CollisionMap2D &map);

	/**
	 * Walk backward.
	 *
	 * @param map	Collision map
	 */
	void walkBack(CollisionMap2D &map);

	/**
	 * Walk left.
	 *
	 * @param map	Collision map
	 */
	void walkLeft(CollisionMap2D &map);

	/**
	 * Walk right.
	 *
	 * @param map	Collision map
	 */
	void walkRight(CollisionMap2D &map);

	/**
	 * Sprint forward.
	 *
	 * @param map	Collision map
	 */
	void sprintForward(CollisionMap2D &map);

	/**
	 * Sprint backward.
	 *
	 * @param map	Collision map
	 */
	void sprintBack(CollisionMap2D &map);

	/**
	 * Sprint left.
	 *
	 * @param map	Collision map
	 */
	void sprintLeft(CollisionMap2D &map);

	/**
	 * Sprint right.
	 *
	 * @param map	Collision map
	 */
	void sprintRight(CollisionMap2D &map);

	/**
	 * Move in arbitrary direction.
	 *
	 * @param dir	Direction and distance to move.
	 * @param map	Collision map
	 */
	void move(Vector3Mike dir, CollisionMap2D &map);

	/**
	 * Move in arbitrary direction.
	 *
	 * @param x		X distance to move.
	 * @param y		Y distance to move.
	 * @param z		Z distance to move.
	 * @param map	Collision map
	 */
	void move(double x, double y, double z, CollisionMap2D &map);

	/**
	 * Change view direction.
	 *
	 * @param x		Change in x
	 * @param y		Change in y
	 */
	void changeView(double x, double y);

	/**
	 * Mimic gluLookAt().
	 */
	void lookAt();

	/**
	 * Print cam values.
	 */
	void print();

	/**
     * Get eye.
	 *
	 * @return eye
	 */
	Vector3Mike getEye() {
		return mEye;
	}

private:
	/**
	 * Check if current location is valid on collision map.
	 *
	 * @param map		Collision map
	 *
	 * @return			True of valid, false if collision.
	 */
	bool checkPos(CollisionMap2D &map);

	/** Eye coordinates */
	Vector3Mike mEye;
	/** Center coordinates (what camera is looking at) */
	Vector3Mike mCenter;
	/** Up direction */
	Vector3Mike mUp;
	/** View direction */
	Vector3Mike mDirection;
	/** View XZ direction */
	Vector3Mike mXZDirection;
	/** Increased scale view XZ direction */
	Vector3Mike mScaleXZDirection;
	/** Left direction */
	Vector3Mike mLeft;
	/** Increased scale left direction */
	Vector3Mike mScaleLeft;
	/** X axis direction */
	Vector3Mike mXAxis;
};

