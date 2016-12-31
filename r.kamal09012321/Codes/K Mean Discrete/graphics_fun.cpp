#include<GL/glu.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include<GL/glui.h>
#include<fstream>
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include"user_def.h"
//#include"globals.h"
using namespace std;


void refresh()
{

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glutSwapBuffers();
}


void init (void)
{
	/* select clearing (background) color */
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
 
	glViewport( 0,0, 700, 700 );
	glMatrixMode( GL_PROJECTION );
	glOrtho( 0.0, frameX, 0.0, frameY, 1.0, -1.0 );
 
	/* initialize viewing values */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

