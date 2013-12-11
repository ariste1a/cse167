#pragma once

#include <stdio.h>

/**
 * Representation of a 2D grid marking what coordinates in 
 * world space are occupied by an object.
 * Internally converts world space to grid space (positive coordinates).
 */
class CollisionMap2D
{
public:
	CollisionMap2D(void);

	/**
	 * Constructor. Converts given world space boundaries to grid space [x][z], 
	 * where [0][0] is (xMin, zMin) and [xMax - xMin][zMax - zMin] is (xMax, zMax).
	 *
	 * @param xMin		World space min x.
	 * @param xMax		World space max x.
	 * @param zMin		World space min z.
	 * @param zMax		World space max z.
	 */
	CollisionMap2D(int xMin, int xMax, int zMin, int zMax);

	~CollisionMap2D(void);

	/**
	 * Clear map to free all grid points.
	 */
	void clear();

	/**
	 * Mark a grid point as occupied.
	 *
	 * @param x			World space x coordinate.
	 * @param z			World space z coordinate.
	 */
	void occupyPoint(int x, int z);

	/**
	 * Free a grid point.
	 * 
	 * @param x			World space x coordinate.
	 * @param z			World space z coordinate.
	 */
	void freePoint(int x, int z);

	/**
	 * Check the status of a point.
	 *
	 * @param x			World space x coordinate.
	 * @param z			World space z coordinate.
	 *
	 * @return			True if occupied, false otherwise.
	 */
	bool checkPoint(int x, int z);


private:
	// Grid representation. 2d array, where each element represents a grid coordinate.
	// False means space is open. True means space is occupied.
	bool **m_grid;
	// World space min x.
	int m_xMin;
	// World space max x.
	int m_xMax;
	// World space min z.
	int m_zMin;
	// World space max z.
	int m_zMax;
};