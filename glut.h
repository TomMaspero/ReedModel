#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef __APPLE__
	#include "OpenGL/gl.h"
	#include "OpenGL/glu.h"
	#include <GLUT/glut.h>
#else
#ifdef WIN32
	#include <windows.h>
#endif
	#include <GL/gl.h>
	#include <GL/glext.h>
	#include <GL/glu.h>
	#include <GL/freeglut.h>
#endif

#define SLEEP_TICKS 32  //este define relaciona un nombre con un numero, entonces cuando pongo sleep_ticks lo interpreta como el numero 32
                        //ir probando con distintos numeros
#ifndef GLUT_H
#define GLUT_H

void display();

void timercall(int value);

void initGL(void);

void glutStuff(int argc, const char *argv[]);

void callGlut();

void saveScreenshotToFile(char *filename, int windowWidth, int windowHeight);

void drawCircle(float cx, float cy, float r, int num_segments);

#endif
