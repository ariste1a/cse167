#define _CRT_SECURE_NO_WARNINGS
//This example program is created by thecplusplusuy for demonstration purposes. It's a simple 3D model loader (wavefront (.obj)), which is capable to load materials and UV textures:
//http://www.youtube.com/user/thecplusplusguy
//Free source, modify if you want, LGPL licence (I guess), I would be happy, if you would not delete the link
//so other people can see the tutorial
//this file is third.cpp an example, how to use the class
#include "objloader.h"
#include "particles.h"

float angle=0.0;
int cube;
std::vector<Particles*> particles; 
objloader obj;	//create an instance of the objloader
unsigned int particleTexture; 
void init()
{
	Particles a = *(new Particles()); 
	glClearColor(0.5,0.5,0.5,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,640.0/480.0,1.0,500.0);
	//glFrustum(-10, 10, -10, 10, 10, 1000); 
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	cube=obj.load("temple.obj");	//load it
	glEnable(GL_NORMALIZE); 
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1); 

	float col[]={1.0,1.0,1.0,1.0};
	float direction[] = {0, 0, 0}; 
	float pos[] = {1, 1, 1, 1}; 
	float color[] = {1, 0.5, 0.5, 1}; 
	
	glLightfv(GL_LIGHT0,GL_DIFFUSE,col);
	
	//glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction); 
	glLightfv(GL_LIGHT1, GL_DIFFUSE, color); 
	//glLightfv(GL_LIGHT1, GL_POSITION, pos); 
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 5 );
	for(int i =0; i < 1000; i++)
	{
		particles.push_back(new Particles()); 
	} 
	a.createParticles(particles); 
	particleTexture = obj.loadTexture("fire.bmp"); 	
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	float pos[]={-1.0,1.0,-2.0,1.0};
	gluLookAt(0, 3, -1, 0, 0, 0, 0, 1, 0); 
	glLightfv(GL_LIGHT0,GL_POSITION,pos);
	//glTranslatef(0.0, 0,-5);
	glCallList(cube);	//and display it
	 glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
	 glEnable ( GL_COLOR_MATERIAL );
	 glDisable(GL_LIGHTING); 
	 glDepthMask(false); 
	 glEnable(GL_TEXTURE_2D);
	 glBindTexture(GL_TEXTURE_2D, particleTexture);
	 
	 glEnable(GL_BLEND);
	 //glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);
	 glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	 //glBlendEquation(GL_FUNC_ADD);
	 for (int i=0;i< particles.size();i++)
	 {
		 if(particles[i]->ypos< 0.0)
		 {
		   particles[i]->lifetime=0.0;
		 }		
		 if((particles[i]->active==true) && (particles[i]->lifetime>0.0))
		 {		   
		   glColor4f(particles[i]->r, particles[i]->g, particles[i]->b, 0.8);
		   glBegin(GL_TRIANGLE_STRIP);
		     glTexCoord2f(0.0, 1.0); 
			 glVertex3f(particles[i]->xpos+0.1, particles[i]->ypos+0.1, particles[i]->zpos+0.0);     // top    right

			 glTexCoord2f(0, 0); 
			 glVertex3f(particles[i]->xpos-0.1, particles[i]->ypos+0.1, particles[i]->zpos+0.0);     // top    left

			 glTexCoord2f(1, 1); 
			 glVertex3f(particles[i]->xpos+0.1, particles[i]->ypos-0.1, particles[i]->zpos+0.0);     // bottom right

			 glTexCoord2f(1, 0); 
			 glVertex3f(particles[i]->xpos-0.1, particles[i]->ypos-0.1, particles[i]->zpos+0.0);     // bottom left
		   glEnd();
		  }
		 else
		 {
			 particles[i]->refreshParticle(particles[i]); 
		 }
		}
	particles[0]->evolveParticle(particles);	
	glDisable(GL_COLOR_MATERIAL); 
	glDisable(GL_TEXTURE_2D); 
	glDisable(GL_BLEND); 
	glDepthMask(true); 
	glEnable(GL_LIGHTING); 
}


int main(int argc,char** argv)
{
	srand (time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface* screen=SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);	
	SDL_WM_SetCaption("Temple of Time", "asdf");
	bool running=true;
	Uint32 start;
	SDL_Event event;
	init();
	while(running)
	{
		start=SDL_GetTicks();
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					running=false;
					break;
			}
		}
		display();
		SDL_GL_SwapBuffers();
		angle+=0.5;
		if(angle>360)
			angle-=360;
		if(1000/30>(SDL_GetTicks()-start))
			SDL_Delay(1000/30-(SDL_GetTicks()-start));
	}
	SDL_Quit();
	return 0;	
}