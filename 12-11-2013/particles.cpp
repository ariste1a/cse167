#include "Particles.h"


Particles::Particles(void)
{
}

void Particles::createParticles(std::vector<Particles*> particles, float x, float y, float z)
{	 	 
	 for(int i =0; i<particles.size(); i++)
	 {
		 particles[i]->lifetime= rand() / float(RAND_MAX); 
		 particles[i]->decay=0.001;
		 particles[i]->r = 0.6;
		 particles[i]->g = 0.6;
		 particles[i]->b = 1;
		 particles[i]->emitX = x; 
		 particles[i]->emitY = y;
		 particles[i]->emitZ = z; 
		 particles[i]->xpos= x;
		 particles[i]->ypos= y;
		 particles[i]->zpos= z;		 
		 particles[i]->xspeed = 0.0005-((rand() % 100)/100000.0);
		 particles[i]->yspeed = 0.01-((rand() % 100)/100000.0);
		 particles[i]->zspeed = 0.0005-((rand() % 100)/100000.0);
		 particles[i]->active = true;
	 } 
}

void Particles::refreshParticle(Particles* particle, float x, float y, float z)
{
		 particle->lifetime= rand() / float(RAND_MAX); 
		 particle->decay= (5 + rand() / (RAND_MAX / (8 - 5 + 1) + 1))/1000.0;// 0.00005;
		 particle->r = 0.6;
		 particle->g = 0.6;
		 particle->b = 1;
		 particle->emitX = x;
		 particle->emitY = y;
		 particle->emitZ = z;
		 particle->xpos= x;
		 particle->ypos= y;
		 particle->zpos= z;
		 particle->xspeed = (-5 + rand() / (RAND_MAX / (5 + 5 + 1) + 1)) / 10000.0;//0.000005f;
		 particle->yspeed = (5 + rand() / (RAND_MAX / (8 - 5 + 1) + 1)) / 10000000000000000.0; //0.00000000000000000005f; 
		 particle->zspeed = (-5 + rand() / (RAND_MAX / (5 + 5 + 1) + 1)) / 10000.0;//0.000005f; 
		 particle->active = true;
}

/*
void Particles::moveParticle(Particles* particle, float x, float y, float z)
{
		 particle->lifetime= rand() / float(RAND_MAX); 
		 particle->decay= (5 + rand() / (RAND_MAX / (8 - 5 + 1) + 1))/100000.0;// 0.00005;
		 particle->r = 0.6;
		 particle->g = 0.6;
		 particle->b = 1;
		 particle->xpos= 0+x;
		 particle->ypos= 0.3+y;
		 particle->zpos= 0+z;
		 particle->emitX= 0+x;
		 particle->emitY= 0.3+y;
		 particle->emitZ= 0+z;
		 particle->xspeed = (-5 + rand() / (RAND_MAX / (5 + 5 + 1) + 1))/1000000.0;//0.000005f;
		 particle->yspeed = (5 + rand() / (RAND_MAX / (8 - 5 + 1) + 1))/10000000000000000000.0; //0.00000000000000000005f; 
		 particle->zspeed = (-5 + rand() / (RAND_MAX / (5 + 5 + 1) + 1))/1000000.0;//0.000005f; 
		 particle->active = true;
}
*/ 
void Particles::evolveParticle(std::vector<Particles*> particle)
{
   for(int i=0;i< particle.size();i++){      // evolve the particle parameters
     particle[i]->lifetime-=particle[i]->decay;
     particle[i]->xpos+=particle[i]->xspeed;
     particle[i]->ypos+=particle[i]->yspeed;
     particle[i]->zpos+=particle[i]->zspeed;
	 particle[i]->yspeed -= 0.0000004;
   }
}

Particles::~Particles(void)
{
}

