#include "Particles.h"


Particles::Particles(void)
{
}

void Particles::createParticles(std::vector<Particles*> particles)
{	 	 
	 for(int i =0; i<particles.size(); i++)
	 {
		 particles[i]->lifetime= rand() / float(RAND_MAX); 
		 particles[i]->decay=0.001;
		 particles[i]->r = 0.6;
		 particles[i]->g = 0.6;
		 particles[i]->b = 1;
		 particles[i]->xpos= 0.5;
		 particles[i]->ypos= 0.5;
		 particles[i]->zpos= 0.5;
		 particles[i]->xspeed = 0.0005- ((rand() % 100)/ 100000.0);
		 particles[i]->yspeed = 0.01-((rand() % 100)/ 100000.0);
		 particles[i]->zspeed = 0.0005-((rand() % 100)/ 100000.0);
		 particles[i]->active = true;
	 } 
}

void Particles::refreshParticle(Particles* particle)
{
		 particle->lifetime= rand() / float(RAND_MAX); 
		 particle->decay=0.001;
		 particle->r = 0.6;
		 particle->g = 0.6;
		 particle->b = 1;
		 particle->xpos= 0.5;
		 particle->ypos= 0.5;
		 particle->zpos= 0.5;
		 particle->xspeed = 0.0005- ((rand() % 100)/ 100000.0);
		 particle->yspeed = 0.01-((rand() % 100)/ 100000.0);
		 particle->zspeed = 0.0005-((rand() % 100)/ 100000.0);
		 particle->active = true;
}

void Particles::evolveParticle(std::vector<Particles*> particle)
{
   for(int i=0;i< particle.size();i++){      // evolve the particle parameters
     particle[i]->lifetime-=particle[i]->decay;
     particle[i]->xpos+=particle[i]->xspeed;
     particle[i]->ypos+=particle[i]->yspeed;
     particle[i]->zpos+=particle[i]->zspeed;
     particle[i]->yspeed-=0.00007;
   }
}

Particles::~Particles(void)
{
}
