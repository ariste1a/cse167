#pragma once
#include <vector>
#include <math.h>
#include <cstdlib>
#include <time.h>
class Particles
{
public:
	Particles(void);
	float lifetime; 
	float decay;
	float r,g,b; 
	float emitX, emitY, emitZ; 
	float xpos, ypos, zpos; 
	float xspeed, yspeed, zspeed; 
	bool active; 
	void createParticles(std::vector<Particles*> Particles, float x, float y, float z);
	void evolveParticle(std::vector<Particles*> particle);
	void refreshParticle(Particles* particle, float x, float y, float z);
	virtual ~Particles(void);
};

