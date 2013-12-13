#include "shader.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "objloader.h"
#include "CollisionMap2D.h"
#include "Vector3Mike.h"
#include "Vector4Mike.h"
#include "Matrix4Mike.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Camera.h"
#include "FPSView.h"
#include "Node.h"
#include "Line.h"
#include "Geode.h"
#include "Group.h"
#include "MatrixTransform.h"
#include "ControlPoint.h"
#include "Bezier.h"
#include "particles.h"
#undef main

using namespace std;

static std::vector<Particles*> particles;
unsigned int particleTexture;
unsigned int naviSprite; 
unsigned int _skybox[6]; 
static Camera camera;
static FPSView *fpsView;
static CollisionMap2D *map;

static bool useShaders = true;

static Shader *shade;
static unsigned int glslProg;
static int glslUseToonShading;
static int glslEye;

static int useToonShading = 0;

static Matrix4 xformationMatrix;
static Matrix4 scaleMatrix;
static Matrix4 model;
static Matrix4 rotationMatrix;
float scale = 1;

int oldMouseX, oldMouseY;

// For scaling and translating objects
float minX = 0;
float minY = 0;
float minZ = 0;
float maxX = 0;
float maxY = 0;
float maxZ = 0;
float translateX = 0;
float translateY = 0;
float translateZ = 0;

// How fast to move
float velocity = 0.1;

// For bezier curve
float bezierTime = 0;
int width = 512;   // set window width in pixels here
int height = 512;   // set window height in pixels here


// For surface of revolution
static float revolutionAngle;
static vector<ControlPoint*> points;
static int numCurves;
static int currCurve = 0;
static int samples = 20;
static int currSample = 0;
// This data structure defines a simple house
//nVerts = 42;    your vertex array needs to have this many entries

Vector4 e = Vector4(.4, .2, 0, 1);
Vector4 d = Vector4(-.6, .2, 0, 1);
Vector4 up = Vector4(0, 1, 0, 0);

float position[] = { 0.3, 0.6, 0, 0.0}; //dot position on curve

Group* world = new Group();
//for accessing the next curve to follow
vector<Node*> bezierCurves;

MatrixTransform* xform;

Geode* line;
ControlPoint* point;
//Bezier* bezier;

Matrix4 M = Matrix4();

float angle = 0.0;

int cube;
objloader obj;	//create an instance of the objloader
objloader second; 

void drawSkybox()
{
	    // Enable/Disable features    
    glEnable(GL_TEXTURE_2D);
    // Just in case we set all vertices to white. 
 
    // Render the front quad
    glBindTexture(GL_TEXTURE_2D, _skybox[0]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(  30.0, -30.0, -30.0 );
        glTexCoord2f(1, 0); glVertex3f( -30.0, -30.0, -30.0 );
        glTexCoord2f(1, 1); glVertex3f( -30.0,  30.0, -30.0 );
        glTexCoord2f(0, 1); glVertex3f(  30.0,  30.0, -30.0 );
    glEnd();
 
    // Render the left quad
    glBindTexture(GL_TEXTURE_2D, _skybox[1]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(  30.0, -30.0,  30.0 );
        glTexCoord2f(1, 0); glVertex3f(  30.0, -30.0, -30.0 );
        glTexCoord2f(1, 1); glVertex3f(  30.0,  30.0, -30.0 );
        glTexCoord2f(0, 1); glVertex3f(  30.0,  30.0,  30.0 );
    glEnd();
 
    // Render the back quad
    glBindTexture(GL_TEXTURE_2D, _skybox[2]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f( -30.0, -30.0,  30.0 );
        glTexCoord2f(1, 0); glVertex3f(  30.0, -30.0,  30.0 );
        glTexCoord2f(1, 1); glVertex3f(  30.0,  30.0,  30.0 );
        glTexCoord2f(0, 1); glVertex3f( -30.0,  30.0,  30.0 );
 
    glEnd();
 
    // Render the right quad
    glBindTexture(GL_TEXTURE_2D, _skybox[3]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f( -30.0, -30.0, -30.0 );
        glTexCoord2f(1, 0); glVertex3f( -30.0, -30.0,  30.0 );
        glTexCoord2f(1, 1); glVertex3f( -30.0,  30.0,  30.0 );
        glTexCoord2f(0, 1); glVertex3f( -30.0,  30.0, -30.0 );
    glEnd();
 
    // Render the top quad
    glBindTexture(GL_TEXTURE_2D, _skybox[4]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f( -30.0,  30.0, -30.0 );
        glTexCoord2f(0, 0); glVertex3f( -30.0,  30.0,  30.0 );
        glTexCoord2f(1, 0); glVertex3f(  30.0,  30.0,  30.0 );
        glTexCoord2f(1, 1); glVertex3f(  30.0,  30.0, -30.0 );
    glEnd();
 
    // Render the bottom quad
    glBindTexture(GL_TEXTURE_2D, _skybox[5]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f( -30.0, -30.0, -30.0 );
        glTexCoord2f(0, 1); glVertex3f( -30.0, -30.0,  30.0 );
        glTexCoord2f(1, 1); glVertex3f(  30.0, -30.0,  30.0 );
        glTexCoord2f(1, 0); glVertex3f(  30.0, -30.0, -30.0 );
    glEnd();
}
void billboardCheatSphericalBegin() {
	
	float modelview[16];
	int i,j;

	// save the current modelview matrix
	glPushMatrix();

	// get the current modelview matrix
	glGetFloatv(GL_MODELVIEW_MATRIX , modelview);

	// undo all rotations
	// beware all scaling is lost as well 
	for( i=0; i<3; i++ ) 
	    for( j=0; j<3; j++ ) {
		if ( i==j )
		    modelview[i*4+j] = 1.0;
		else
		    modelview[i*4+j] = 0.0;
	    }

	// set the modelview with no rotations
	glLoadMatrixf(modelview);
}



void billboardEnd() {

	// restore the previously 
	// stored modelview matrix
	glPopMatrix();
}


void init()
{
	Particles a = *(new Particles());
	glClearColor(0.5, 0.5, 0.5, 1.0);	
	glEnable(GL_DEPTH_TEST);
	cube = obj.load("sword.obj");	//load the temple	
	glEnable(GL_LIGHTING);
	
	// Global ambient
	float globalAmbient[] = { 0, 0, 0, 1.0 };
	
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	float pointAmb[] = { 0, 0, 0, 1 };
	float pointSpec[] = {1 ,1 ,1, 1}; 
	float pointDiff[] = { 0, 0, 1, 1}; 
	float pointPos[] = { 0.2, 0.3, 0.2, 1};
	glLightfv(GL_LIGHT0, GL_AMBIENT, pointAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, pointDiff); 
	glLightfv(GL_LIGHT0, GL_SPECULAR, pointSpec);	
	glLightfv(GL_LIGHT0, GL_POSITION, pointPos);

	float col2[] = { 0.8, 0.8, 0.392, 1.0 };
	float col3[] = { 0.8, 0.8, 0.392, 1.0 };
	float position2[] = { 1, 1, 1, 0.0 }; // other lightsource position
	glLightfv(GL_LIGHT1, GL_AMBIENT, col2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, col3); 			
	glLightfv(GL_LIGHT1, GL_SPECULAR, pointSpec);	
	glLightfv(GL_LIGHT1, GL_POSITION, position2);	

	for (int i = 0; i < 300; i++)
	{
		particles.push_back(new Particles());
	}
	a.createParticles(particles, 0, 0.3, 0);
	particleTexture = obj.loadTexture("fire.bmp");
	naviSprite = obj.loadTexture("navi.bmp"); 
	_skybox[0] = obj.loadTexture("ofront7.bmp"); 
	_skybox[1] = obj.loadTexture("oleft7.bmp"); 
	_skybox[2] = obj.loadTexture("oback7.bmp");
	_skybox[3] = obj.loadTexture("oright7.bmp"); 
	_skybox[4] = obj.loadTexture("otop7.bmp"); 
	
}


//----------------------------------------------------------------------------
// Callback method called when window readraw is necessary or
// when glutPostRedisplay() was called.
void displayCallback(void)
{
	if (useShaders) {
		shade->bind();
	}
	else {
		shade->unbind();
	}

	if (useShaders) {
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.05);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.02);
		glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0);
	}
	else {
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0);
		glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0);
	}

	glMatrixMode(GL_MODELVIEW);
	// Generate light source:
	//glLightfv(GL_LIGHT0, GL_POSITION, position);

	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers		
	world->draw(camera.getMatrix().multiply(model));
	glLoadIdentity();
	glScalef(100, 100, 100);		
	Vector3Mike eye = fpsView->getEye();
	float eyeArray[] = { eye.get_x(), eye.get_y(), eye.get_z(), 1 };
	glUniform4fvARB(glslEye, 1, eyeArray);
	fpsView->lookAt();

	glCallList(cube); 	
	shade->unbind(); 
	drawSkybox();
	shade->bind(); 
	 
	/******* PARTICLES *********/
	billboardCheatSphericalBegin();
	glScalef(100, 100, 100);
	shade->unbind();
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
	glDepthMask(false);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, particleTexture);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	for (int i = 0; i < particles.size(); i++)
	{
		//if the particle's distance is greater than a certain 
		//distance from the emit center don't render
		float randDepth = (3 + rand() / (RAND_MAX / (8 - 3 + 1) + 1)) / 100.0;
		if (particles[i]->ypos< (particles[i]->emitY - randDepth))
		{
			particles[i]->lifetime = 0.0;
		}
		if ((particles[i]->active == true) && (particles[i]->lifetime>0.0))
		{
			glColor4f(particles[i]->r, particles[i]->g, particles[i]->b, 0.8);
			glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(particles[i]->xpos + 0.01, particles[i]->ypos + 0.01, particles[i]->zpos + 0.0);     // top    right
			glTexCoord2f(0, 0);
			glVertex3f(particles[i]->xpos - 0.01, particles[i]->ypos + 0.01, particles[i]->zpos + 0.0);     // top    left
			glTexCoord2f(1, 1);
			glVertex3f(particles[i]->xpos + 0.01, particles[i]->ypos - 0.01, particles[i]->zpos + 0.0);     // bottom right
			glTexCoord2f(1, 0);
			glVertex3f(particles[i]->xpos - 0.01, particles[i]->ypos - 0.01, particles[i]->zpos + 0.0);     // bottom left
			glEnd();			
		}
		else
		{
			particles[i]->refreshParticle(particles[i], position[0], position[1], position[2]);
			//particles[i]->refreshParticle(particles[i], 0, 0.3, 0); 
		}
	}	
	glBindTexture(GL_TEXTURE_2D, naviSprite);
	glBegin(GL_TRIANGLE_STRIP); 
		glTexCoord2f(0.0, 1.0);
		glVertex3f(position[0] + 0.1, position[1] + 0.1, position[2] );     // top    right
		glTexCoord2f(0, 0);
		glVertex3f(position[0] - 0, position[1] + 0.1, position[2]);     // top    left
		glTexCoord2f(1, 1);
		glVertex3f(position[0]  + 0.1, position[1] - 0, position[2] );     // bottom right
		glTexCoord2f(1, 0);
		glVertex3f(position[0] - 0, position[1]  - 0, position[2] );     // bottom left
	glEnd();
	particles[0]->evolveParticle(particles);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDepthMask(true);
	glEnable(GL_LIGHTING);
	float pointLight[] = { position[0], position[1], position[2], 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, pointLight);
	/****END PARTICLES *****/
	billboardEnd();
	shade->bind();
	glFlush();
	glutSwapBuffers();


}

void moveAlongCurve(float v)
{

	bezierTime += v;
	// If it's time to move the point or move to the next curve
	if (bezierTime >= 1)
	{

		bezierTime = 0;

		// Follow the curve

		Bezier* c = (Bezier*)bezierCurves[currCurve];
		vector<Point> curvePoints = c->getCurve();

		samples = curvePoints.size();
		// Move the object along the current curve
		if (currSample < samples)
		{
			//M.translate(curvePoints[currSample].getX(), curvePoints[currSample].getY(), curvePoints[currSample].getZ());
			//xform->setM(M);
			position[0] = curvePoints[currSample].getX();
			position[1] = curvePoints[currSample].getY();
			position[2] = curvePoints[currSample].getZ();

			point->setXYZ(curvePoints[currSample].getX(),curvePoints[currSample].getY(),curvePoints[currSample].getZ());
			currSample++;

			//cout << point->getX() << endl;
		}
		else // If object has traversed the full length of a curve
		{
			currSample = 0;
			currCurve++;
			currCurve %= numCurves;

			c = (Bezier*)bezierCurves[currCurve];
			curvePoints = c->getCurve();

			position[0] = curvePoints[currSample].getX();
			position[1] = curvePoints[currSample].getY();
			position[2] = curvePoints[currSample].getZ();

			point->setXYZ(curvePoints[currSample].getX(), curvePoints[currSample].getY(), curvePoints[currSample].getZ());
			currSample++;

		}
	}
	
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void idleCallback(void)
{

	//spin(velocity);     // rotate cube; if it spins too fast try 0.001
	displayCallback();  // call display routine to re-draw cube
	moveAlongCurve(velocity);
	//M.identity();
	//xform->setM(M);
}

//----------------------------------------------------------------------------
// Callback method called when window is resized.
void reshapeCallback(int w, int h)
{
	width = w;
	height = h;
  /*glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 1000.0); // set perspective projection viewing frustum
  glTranslatef(0, 0, -20);
  glMatrixMode(GL_MODELVIEW);*/
	glViewport(0, 0, w, h);  // set new viewport size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float cx = 5;
    float halfWidth = width*0.5f; 
	float aspect = (float)width / (float)height; 
	//glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 1000.0);
	//glFrustum(cx - (halfWidth*aspect), cx + (halfWidth*aspect), -10, 10, 10, 1000);
	gluPerspective(70, (float)width / (float)height, 10, 10000);
	//glTranslatef(0, 0, -20);
	//gluLookAt(0, 0.5, 0.5, 0, 0, 0, 0, 1, 0);
}

void processSpecialKeys(int key, int x, int y) {

}

void processNormalKeys(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		fpsView->walkForward(*map);
		break;
	case 'W':
		fpsView->sprintForward(*map);
		break;
	case 's':
		fpsView->walkBack(*map);
		break;
	case 'S':
		fpsView->sprintBack(*map);
		break;
	case 'a':
		fpsView->walkLeft(*map);
		break;
	case 'A':
		fpsView->sprintLeft(*map);
		break;
	case 'd':
		fpsView->walkRight(*map);
		break;
	case 'D':
		fpsView->sprintRight(*map);
		break;
	case 'm':
		useShaders = !useShaders;
		break;
	case 'l':
		//useTexture = !useTexture;
		//cube->useTexture(useTexture);
		break;
	case 't':
		useToonShading = 1 - useToonShading;
		glUniform1iARB(glslUseToonShading, useToonShading);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void processMouse(int button, int state, int x, int y)
{
	if (state == GLUT_UP) {
		return;
	}

	oldMouseX = x;
	oldMouseY = y;


}

void processMotion(int x, int y)
{
	int changeX = x - oldMouseX;
	int changeY = y - oldMouseY;

	fpsView->changeView(changeX, changeY);

	oldMouseX = x;
	oldMouseY = y;
}

void setupCollisionMap(CollisionMap2D *map) {
	int i;
	int j;
	
	// Walls
	for (i = -100; i < 101; ++i) {
		for (j = -10; j < 11; ++j) {
			map->occupyPoint(i, 100 + j);
			map->occupyPoint(i, -100 + j);
			map->occupyPoint(100 + j, i);
			map->occupyPoint(-100 + j, i);
		}
	}

	// Columns
	for (i = -9; i < 10; ++i) {
		for (j = -9; j < 10; ++j) {
			map->occupyPoint(15 + i, -80 + j);
			map->occupyPoint(15 + i, 80 + j);
		}
	}

	// Sword
	for (i = -10; i < 11; ++i) {
		for (j = -10; j < 11; ++j) {
			map->occupyPoint(50 + i, 5 + j);
		}
	}

}

int main(int argc, char *argv[])
{
	float specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float shininess[] = { 100.0 };

	camera = Camera(e, d, up);
	fpsView = new FPSView(.4, .3, 0,
		-.6, .3, 0,
		0, 1, 0);
	map = new CollisionMap2D(-150, 150, -150, 150);
	setupCollisionMap(map);

	glutInit(&argc, argv);      	      	      // initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
	glutInitWindowSize(width, height);      // set initial window size
	glutCreateWindow("OpenGL Final Project for CSE167");    	      // open window and set window title

	init();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH);            	      // enable depth buffering
	glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
	glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
	glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
	glShadeModel(GL_SMOOTH);             	      // set shading to smooth
	glMatrixMode(GL_PROJECTION);

	glEnable(GL_NORMALIZE);
	model.identity();
	M.identity();

	xform = new MatrixTransform(M);

	//points = bezier->getPoints();
	point = new ControlPoint(.4, .4, 0);
	//point->setDraw(true);

	world->addChild(new Bezier(new ControlPoint(0.4, 0.4, 0.4), new ControlPoint(0.2, 0.2, 0.2),
		new ControlPoint(-0.3, 0.2, 0.2), new ControlPoint(-0.4, 0.4, 0.6)));
	world->addChild(new Bezier(new ControlPoint(-0.4, 0.4, 0.6), new ControlPoint(-0.5, .6, 1.0),
		new ControlPoint(-0.5, 0.8, -0.8), new ControlPoint(-0.4, .7, -0.6)));
	world->addChild(new Bezier(new ControlPoint(-0.4, .7, -0.6), new ControlPoint(-0.3, .6, -0.4),
		new ControlPoint(-0.1, 0.27, -0.3), new ControlPoint(0.2, 0.4, -0.4)));
	world->addChild(new Bezier(new ControlPoint(0.2, 0.4, -0.4), new ControlPoint(0.5, .53, -0.5),
		new ControlPoint(0.5, 0.8, -0.4), new ControlPoint(0.2, 0.8, -0.4)));
	world->addChild(new Bezier(new ControlPoint(0.2, 0.8, -0.4), new ControlPoint(-0.1, 0.8, -0.4),
		new ControlPoint(-0.1, 0.4, -0.4), new ControlPoint(0.2, 0.4, -0.4)));
	world->addChild(new Bezier(new ControlPoint(0.2, 0.4, -0.4), new ControlPoint(0.5, 0.5, -0.4),
		new ControlPoint(0.6, 0.6, 0.6), new ControlPoint(0.4, 0.4, 0.4)));


	bezierCurves = world->getChildren();
	numCurves = bezierCurves.size();
	world->addChild(point);	

	//gluLookAt(0, 10, 10, 0, 0, 0, 0, 1, 0);
	// Install callback functions:
	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback);
	glutIdleFunc(idleCallback);

	// Keyboard and Mouse input processing
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(processNormalKeys);
	glutMouseFunc(processMouse);
	glutMotionFunc(processMotion);

	shade = new Shader("shadingTest.vert", "shadingTest.frag");
	shade->bind();

	glslProg = shade->getPid();
	glslUseToonShading = glGetUniformLocationARB(glslProg, "useToonShading");
	glslEye = glGetUniformLocationARB(glslProg, "eye");

	// Always check that our framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;


	glutMainLoop();
	delete world;
	delete line;
	delete fpsView;
	delete map;
	delete shade;
	//delete bezier;

	return 0;
}

