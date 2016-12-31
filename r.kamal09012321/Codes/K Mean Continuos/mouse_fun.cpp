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

void draw_Red_Points(int x, int y) 
{
        //display_points();
	y=frameY-y;
        red_count++;
        if((x/factorX>= x_lower_bound && x/factorX <=x_upper_bound)&&(y/factorY>= y_lower_bound && y/factorY <=y_upper_bound))
         {
            create_set(x/factorX,y/factorY,Red);
 	    glPointSize(1.0f);
	    glColor3f(1.0f, 1.0f, 0.0f);
	    glBegin(GL_POINTS);
            float x1,y1;
            for(float i=0;i<3.141816*2;i+=0.2)
             {
                x1=x+0.2*cos(i);
                y1=y+0.2*sin(i);
                glVertex2f(x1*mapx,y1*mapy);
            }
	      // glVertex2f(x*mapx , y*mapy);
            glEnd();
	    glutSwapBuffers();
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            display_point();
         }
        else
         {
           cout<<"Pointer does not satisfy the upper and lower bound"<<endl;
         }
}


void draw_Blue_Points(int x, int y) 
{
       if((x/factorX>= x_lower_bound && x/factorX <=x_upper_bound)&&(y/factorY>= y_lower_bound && y/factorY <=y_upper_bound))
        {
//        display_points();
	   y=frameY-y;
           blue_count++;
           create_set(x/factorX,y/factorY,Blue);
 	   glPointSize(1.0f);
	   glColor3f(1.0f, 1.0f, 0.0f);
	   glBegin(GL_POINTS);
	   glVertex2f(x*mapx , y*mapy);
           glEnd();
	   glutSwapBuffers();
	   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
           display_point();
        }
}



void mouse(int bin, int state , int x , int y) 
{
	if(bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
         {
              draw_Red_Points(x,y);
         }
        if(bin == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
         {
              draw_Blue_Points(x,y);
         }    
}


/*void createMenu()
{
    seed=glutCreateMenu(menu);
    glutAddMenuEntry("seedred",1);
    glutAddMenuEntry("seedblue",2);


    display=glutCreateMenu(menu);
    glutAddMenuEntry("Red Points",3);
    glutAddMenuEntry("Blue Points",4);
    glutAddMenuEntry("Circle",5);
    glutAddMenuEntry("K",6);

    K=glutCreateMenu(menu);
    glutAddMenuEntry("+1",7);
    glutAddMenuEntry("-1",8);
    glutAddMenuEntry("arbit value",9);
  
    mainmenu=glutCreateMenu(menu);
    glutAddSubMenu("Seed",seed);
    glutAddSubMenu("Display ",display);
    glutAddSubMenu("K",K);
 
    glutAddMenuEntry("EXIT",0);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void menu(int value)
 {
   switch(value)
   {
     case 0 :
     {
          glutDestroyWindow(main_window);
          exit(0);
          break;
     }
     case 1:
     {
          cout<<"# red points:";
          cin>>red_count;
          cout<<"enter the seed for red point generation:";
          cin>>red_seed;
          generate_red_points();
          display_point();
          break;
     }
     case 2:
     {
          cout<<"# blue points:";
          cin>>blue_count;
          cout<<"enter the seed for blue point generation:";
          cin>>blue_seed;
          generate_blue_points();
          display_point();
          break;
     }
     case 3:
     {
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          display_Red_Points();
          break;
     }
     case 4:
     {
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          display_Blue_Points();
          break;
     }
     case 5:
     {
     }
     case 6:
     {
         cout<<"K :"<<k;
         break;
     }
     case 7:
     {
         k++;
         cout<<"Increamenting the value of K by 1"<<"\tK="<<k<<endl;
         break;
     }
     case 8:
     {
         k--;
         cout<<"Decreamenting the value of K by 1"<<"\tK="<<k<<endl;
         break;
     }
     case 9:
     {
          cout<<"Enter the value for K  ";
          cin>>k;
     }
  }
}*/
