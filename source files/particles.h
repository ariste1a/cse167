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
	float xpos, ypos, zpos; 
	float xspeed, yspeed, zspeed; 
	bool active; 
	void createParticles(std::vector<Particles*> Particles);
	void evolveParticle(std::vector<Particles*> particle);
	void refreshParticle(Particles* particle); 
	virtual ~Particles(void);
};

