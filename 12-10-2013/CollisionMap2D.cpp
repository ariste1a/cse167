#include "CollisionMap2D.h"


CollisionMap2D::CollisionMap2D(void)
{
}

/**
 * Constructor. Converts given world space boundaries to grid space [x][z], 
 * where [0][0] is (xMin, zMin) and [xMax - xMin][zMax - zMin] is (xMax, zMax).
 *
 * @param xMin		World space min x.
 * @param xMax		World space max x.
 * @param zMin		World space min z.
 * @param zMax		World space max z.
 */
CollisionMap2D::CollisionMap2D(int xMin, int xMax, int zMin, int zMax) : 
	m_xMin(xMin),
	m_xMax(xMax),
	m_zMin(zMin),
	m_zMax(zMax) {
	
	// Check max > min
	if (xMax < xMin || zMax < zMin) {
		fprintf(stderr, "CollisionMap2D error: max parameter cannot be less than min\n");
		return;
	}

	// Convert world to grid space
	xMax -= xMin;
	zMax -= zMin;

	// Initialize array
	m_grid = new bool*[xMax];
	for (int i = 0; i < xMax; ++i) {
		m_grid[i] = new bool[zMax];

		for (int j = 0; j < zMax; ++j) {
			m_grid[i][j] = false;
		}
	}
}


CollisionMap2D::~CollisionMap2D(void)
{
	int xSize = m_xMax - m_xMin;

	for (int i = 0; i < xSize; ++i) {
		delete[] m_grid[i];
	}

	delete[] m_grid;
}

/**	
 * Clear map to free all grid points.
 */
void CollisionMap2D::clear() {
	int xSize = m_xMax - m_xMin;
	int zSize = m_zMax - m_zMin;

	for (int i = 0; i < xSize; ++i) {
		for (int j = 0; j < zSize; ++j) {
			m_grid[i][j] = false;
		}
	}
}

/**
 * Mark a grid point as occupied.
 *
 * @param x			World space x coordinate.
 * @param z			World space z coordinate.
 */
void CollisionMap2D::occupyPoint(int x, int z) {
	// Check input range
	if (x < m_xMin || m_xMax < x || z < m_zMin || m_zMax < z) {
		fprintf(stderr, "CollisionMap2D occupy error: point outside of range\n");
		return;
	}

	x -= m_xMin;
	z -= m_zMin;

	m_grid[x][z] = true;
}

/**
 * Free a grid point.
 * 
 * @param x			World space x coordinate.
 * @param z			World space z coordinate.
 */
void CollisionMap2D::freePoint(int x, int z) {
	// Check input range
	if (x < m_xMin || m_xMax < x || z < m_zMin || m_zMax < z) {
		fprintf(stderr, "CollisionMap2D free error: point outside of range\n");
		return;
	}

	x -= m_xMin;
	z -= m_zMin;

	m_grid[x][z] = false;
}

/**
 * Check the status of a point.
 *
 * @param x			World space x coordinate.
 * @param z			World space z coordinate.
 *
 * @return			True if occupied, false otherwise.
 */
bool CollisionMap2D::checkPoint(int x, int z) {
	// Check input range
	if (x < m_xMin || m_xMax < x || z < m_zMin || m_zMax < z) {
		fprintf(stderr, "CollisionMap2D check error: point outside of range\n");
		return true;
	}

	x -= m_xMin;
	z -= m_zMin;

	return m_grid[x][z];
}