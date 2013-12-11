#include "shader.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//#include <time.h>
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

#undef main
/*#include "Cone.h"
#include "Cube.h"
#include "Sphere.h"*/

using namespace std;

static Camera camera;
static FPSView *fpsView;
static CollisionMap2D *map;

static bool useShaders = true;

static Shader *shade;
static unsigned int glslProg;
static int glslUseToonShading;

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
float velocity = 0.005;

// For bezier curve

float bezierTime = 0;

// For objreader
/*int nVerts;
float *vertices;
float *normals;
float *texcoords;
int nIndices;
int *indices;*/

// Switch Case flags
/*bool cull = false;
bool f1 = true;
bool f2 = false;
bool f3 = false;
bool f4 = false;
bool f5 = false;
bool f6 = false;
bool f8f9 = true;
bool mousePress = false;
bool first = true;
bool lock = false;
bool shaderOn = true;
bool textureOn = true;*/

int width = 512;   // set window width in pixels here
int height = 512;   // set window height in pixels here

// For mouse, motion, and trackball rotation
/*static int mouseButton = 0;
static int mouseState = 0;
static int fromX = width / 2;
static int fromY = height / 2;
static int toX = fromX;
static int toY = fromY;
static int prevX = 0;
static int prevY = 0;
static int frames = 0;
static int total = 0;
static float angle;*/

// For surface of revolution
static float revolutionAngle;
static vector<ControlPoint*> points;
static int numCurves = 4;
static int currCurve = 0;
static int samples = 20;
static int currSample = 0;
// This data structure defines a simple house
//nVerts = 42;    your vertex array needs to have this many entries

Vector4 e = Vector4(0, 10, 10, 1);
Vector4 d = Vector4(0, 0, 0, 1);
Vector4 up = Vector4(0, 1, 0, 0);

float position[] = { 0.3, 0.6, 0, 0.0}; // other lightsource position

Group* world = new Group();
//for accessing the next curve to follow
vector<Node*> bezierCurves;

MatrixTransform* xform;

/*MatrixTransform* xform1;
MatrixTransform* xform2;
MatrixTransform* xform3;
MatrixTransform* xform4;
MatrixTransform* xform5;

MatrixTransform* xform11;
MatrixTransform* xform22;
MatrixTransform* xform111;
MatrixTransform* xform222;
MatrixTransform* xform33;
MatrixTransform* xform44;
MatrixTransform* xform55;
*/

Geode* line;
ControlPoint* point;
//Bezier* bezier;

Matrix4 M = Matrix4();

float angle = 0.0;

int cube;
objloader obj;	//create an instance of the objloader
void init()
{
	glClearColor(0.5, 0.5, 0.5, 1.0);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(45, 640.0 / 480.0, 1.0, 500.0);
	//glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	cube = obj.load("temple.obj");	//load it
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float col[] = { .5, .5, .5, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, col);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, col); 
	glLightfv(GL_LIGHT1, GL_DIFFUSE, col);
	float position1[] = { .4, 1, 0, 1.0, 0 };
	float position2[] = { 0.3, 0.6, 0, 0.0 }; // other lightsource position
	glLightfv(GL_LIGHT0, GL_POSITION, position1);
	glLightfv(GL_LIGHT1, GL_POSITION, position2);
	//glEnable(GL_LIGHT1);
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
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1);
		glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, .5);
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
	//glMatrixMode(GL_MODELVIEW);
	//glLoadMatrixd(camera.getMatrix().multiply(model).getPointer());
	//glLineWidth(2.5);

	//world->draw(camera.getMatrix().multiply(model));
	glLoadIdentity();
	glScalef(100, 100, 100);
	fpsView->lookAt();
	glCallList(cube); 
	//glutSolidCube(1); 
	glFlush();
	glutSwapBuffers();

	/*t = clock() - t;
	frames++;
	total += t;
	if (((float)total) / CLOCKS_PER_SEC > 1.0)
	{
		cout << frames << "fps" << endl;
		frames = 0;
		total = 0;
	}*/
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
	//moveAlongCurve(velocity);
	//M.identity();
	//xform->setM(M);
}

//----------------------------------------------------------------------------
// Callback method called when window is resized.
void reshapeCallback(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, w, h);  // set new viewport size
  /*glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 1000.0); // set perspective projection viewing frustum
  glTranslatef(0, 0, -20);
  glMatrixMode(GL_MODELVIEW);*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 1000.0);
	glTranslatef(0, 0, -20);
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

int main(int argc, char *argv[])
{
	float specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float shininess[] = { 100.0 };
	//float position[] = { .4, .2, 0, 1.0 };

	//camera = Camera(e, d, up);
	fpsView = new FPSView(.4, .2, 0,
		-.6, .2, 0,
		0, 1, 0);
	map = new CollisionMap2D(-100, 100, -100, 100);



	glutInit(&argc, argv);      	      	      // initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
	glutInitWindowSize(width, height);      // set initial window size
	glutCreateWindow("OpenGL SurfaceofRevolution for CSE167");    	      // open window and set window title

	init();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH);            	      // enable depth buffering
	glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
	glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
	glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
	glShadeModel(GL_SMOOTH);             	      // set shading to smooth
	glMatrixMode(GL_PROJECTION);

	// Generate material properties:
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	//glEnable(GL_COLOR_MATERIAL);

	// Round points
	glEnable(GL_POINT_SMOOTH);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_NORMALIZE);
	model.identity();
	M.identity();

	xform = new MatrixTransform(M);

	//points = bezier->getPoints();
	point = new ControlPoint(2, 10, 1);
	point->setDraw(true);

	world->addChild(new Bezier(new ControlPoint(2, 8, 1), new ControlPoint(1, 7, 1),
							   new ControlPoint(5, 5, -1),new ControlPoint(6, 6, -2)));
	world->addChild(new Bezier(new ControlPoint(6, 6, -2), new ControlPoint(7, 7, 0),
		new ControlPoint(2, -8, 0), new ControlPoint(0, -10, 0)));
	world->addChild(new Bezier(new ControlPoint(0, -10, 0), new ControlPoint(-2, -12, 0),
		new ControlPoint(-7, -7, -3), new ControlPoint(-6, -6, -2)));
	world->addChild(new Bezier(new ControlPoint(-6, -6, -2), new ControlPoint(-5, -5, -1),
		new ControlPoint(3, 9, 1), new ControlPoint(2, 8, 1)));


	bezierCurves = world->getChildren();
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

