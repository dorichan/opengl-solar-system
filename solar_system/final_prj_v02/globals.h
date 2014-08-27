#include <stdio.h>
#include <stdlib.h>
#include <GL\glut.h>

#define FALSE 0
#define TRUE 1
#define SUN 4
#define MERCURY 5
#define VENUS 6
#define EARTH 7
#define MARS 8
#define JUPITER 9
#define SATURN 10
#define URANUS 11
#define NEPTUNE 12
#define POINT 13
#define SOLID 14
#define WIRE 15
#define SHININESS 16
#define DIFFUSE 17
#define SPECULAR 18

char rotate = FALSE;

float speed = 0.4;
float zoomSpeed = 0.02;

float vectorX = 0.0;
float vectorY = 0.0;
float vectorZ = -1.0;
float eyeX = 0.0;
float eyeY = 0.0;
float eyeZ = 0.0;
float angle = 45.0;
float spin = 45.0;
float theta = 0.0;
float phi = 0.0;

float R = 1.0;
float G = 1.0;
float B = 1.0;

int oldX, oldY;

float deltaAngle = 0.0;
float xOrigin = -1.0;

static int rotateFlag;
static int zoomFlag;
static int sunFlag = 0;
static int merFlag = 0;
static int venFlag = 0;
static int earthFlag = 0;
static int marsFlag = 0;
static int jupiterFlag = 0;
static int saturnFlag = 0;
static int uranusFlag = 0;
static int neptuneFlag = 0;
static int lightFlag = 1;
static int pointFlag = 0;
static int solidFlag = 1;
static int wireFlag = 0;
static int texFlag = 1;
static int spinFlag = 1;
static int objFlag = 0;
static int rotateCamFlag = 0;
static int spaceStationMove = 0;
static int growFlag = 0;

static int sToggle = 0;
static int dToggle = 1;
static int shToggle = 0;

int width = 1024;
int height = 720;
int i = 0;
int j = 0;

GLuint texture[12];
GLUquadricObj * sphere = NULL;

float merSpinX = -1.5;
float merSpinY = 0.0;
float merSpin = 0.0;
float venSpinX = -2.0;
float venSpinY = 0.0;
float venusSpin = 0.0;
float earthSpinX = -3.0;
float earthSpinY = 0.0;
float earthSpin = 0.0;	
float moonSpinX = 0.0;
float moonSpinY = 0.0;
float marsSpinX = -4.0;
float marsSpinY = 0.0;
float marsSpin = 0.0;
float jupiterSpinX = -5.5;
float jupiterSpinY = 0.0;
float jupiterSpin = 0.0;
float saturnSpinX = -7.0;
float saturnSpinY = 0.0;
float saturnSpin = 0.0;
float uranusSpinX = -8.5;
float uranusSpinY = 0.0;
float uranusSpin = 0.0;
float neptuneSpinX = -11.0;
float neptuneSpinY = 0.0;
float neptuneSpin = 0.0;
float plutoX = -12.0;
float plutoY = 0.0;
float plutoZ = -10.0;
float plutoSpin = 0.0;

float spaceStationSpin = 0.0;
float spaceStationX = 3.3;
float spaceStationY = 3.3;
float spaceStationZ = -10.0;

const GLfloat grow = 0.0;

GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[] = {0.7, 0.7, 0.7, 1.0 }; 
GLfloat mat_ambient_color[] = {1.0, 1.0, 1.0, 1.0 };
GLfloat mat_diffuse[] = {0.1, 0.5, 0.8, 0.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat no_shininess[] = { 0.0 };
GLfloat low_shininess[] = { 5.0 };
GLfloat high_shininess[] = { 100.0 };
GLfloat mat_shininess[] = { 50.0 };
GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 1.0 };

GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat position[] = { 0.0, 5.0, -5.0, 50.0 };

float acceleration = 0.0;
char isSphere = FALSE;