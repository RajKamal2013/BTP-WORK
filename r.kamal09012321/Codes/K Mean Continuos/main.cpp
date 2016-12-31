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
using namespace std;



int red_seed=13;
int blue_seed=12;
int cluster_seed=23;
int k=10;
int k_incr=5;
int rad=10;
float tol=0.15;
int red_count=50;
int blue_count=200;
int ans=0;
int result=0;
int k1;
//fix upper bound and lower bound and framex and frameY then map and factor=frame/(upper bound-lower bound)

float mapx=7.0; //7.0
float mapy=7.0; //7.0
int x_upper_bound=100;
int x_lower_bound=0;
int y_lower_bound=0;
int y_upper_bound=100;
int frameX=700;
int frameY=700;
int factorX=7;
int factorY=7;

int draw=0;
int generate=0;
int mainmenu=0;
int set=0;
int val=0;
int main_window;
int display=0;

ofstream file;
ofstream file1;
ofstream file2;
ofstream file3;
vector<setP> Red_Points;
vector<setP> Blue_Points;
vector<setC>cluster;
vector<setC>actual_Cluster;
vector<setC>Blue_cluster;
vector<setC>actual_Blue_Cluster;







void createMenu()
{
    generate=glutCreateMenu(menu);
    glutAddMenuEntry("red",1);
    glutAddMenuEntry("blue",2);
    glutAddMenuEntry("cluster",3);
    
    


    display=glutCreateMenu(menu);
    glutAddMenuEntry("Red Points",4);
    glutAddMenuEntry("Blue Points",5);
    glutAddMenuEntry("points",6);
    glutAddMenuEntry("cluster",7);
    glutAddMenuEntry("Actual_Cluster",8);
    glutAddMenuEntry("Blue Cluster",9);
    glutAddMenuEntry("Actual Blue Cluster",10);
    glutAddMenuEntry("K",11);

    set=glutCreateMenu(menu);
    glutAddMenuEntry("K++",12);
    glutAddMenuEntry("K--",13);
    glutAddMenuEntry("Increment factor K",14);
    glutAddMenuEntry("set K ",15);
    glutAddMenuEntry("Radius ",16);
    glutAddMenuEntry("Tolerance",17);
    glutAddMenuEntry("Bounds",18);
  
    mainmenu=glutCreateMenu(menu);
    glutAddSubMenu("Generate",generate);
    glutAddSubMenu("Display ",display);
    glutAddSubMenu("set",set);
 
    glutAddMenuEntry("EXIT",0);
   // glutAddMenuEntry("Keyboeard Functions",18);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void menu(int value)
 {
   switch(value)
   {
     case 0 :
     {
          glutDestroyWindow(main_window);
          file.close();
          file2.close();
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
          display_points();
          break;
     }
     case 2:
     {
          cout<<"# blue points:";
          cin>>blue_count;
          cout<<"enter the seed for blue point generation:";
          cin>>blue_seed;
          generate_blue_points();
          display_points();
          break;
     }
     case 3:
     {
          cout<<"# Cluster:";
          cin>>k;
          cout<<"Enter the seed for the cluster: ";
          cin>>cluster_seed;
          generate_cluster();
          display_point();
          sleep(1);
          display_points();
          break;
     }
     case 4:
     {
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          display_Red_Points();
          break;
     }
     case 5:
     {
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          display_Blue_Points();
          break;
     }
     case 6:
     {
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          display_point();
          break;
     }
     case 7:
     {
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          display_cluster();
          break;    
     }
     case 8:
     {
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          display_actual_cluster();
          break;    
     }
     case 9:
     {
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          display_Blue_cluster();
          break;    
     }
     case 10:
     {
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          display_actual_Blue_cluster();
          break;    
     }
     case 11:
     {
         cout<<"K :"<<k;
         break;
     }
     case 12:
     {
         k++;
         cout<<"Increamenting the value of K by 1"<<"\tK="<<k<<endl;
         display_points();
         break;
     }
     case 13:
     {
         k--;
         cout<<"Decreamenting the value of K by 1"<<"\tK="<<k<<endl;
         display_points();
         break;
     }
     case 14:
     {
          cout<<"Enter the increment factor  ";
          cin>>k_incr;
          k=k+k_incr;
          if(k>0)
          {
           display_points();
          }
          else
          {
              file2<<"Invalid K value: "<<k<<endl;
              file.close();
              file2.close();
              exit(0);
          }
          break;
     }
    case 15:
     {
          cout<<"Enter the value of K: ";
          cin>>k;
          if(k>0)
           {
             display_points();
           }
          else
           {
              file2<<"Invalid K value: "<<k<<endl;
              file.close();
              file2.close();
              exit(0);
           }
     }
    case 16:
     {
          cout<<"Set the radius =";
          cin>>rad;
          if(rad>0)
          {
             display_points();
          }
          else
          {
             file2<<"Invalid Radius(only positive value): "<<rad<<endl;
             file.close();
             file2.close();
             exit(0);
          }
          break;
     }
    case 17:
     {   
          cout<<"Set the tolerance =";
          cin>>tol;
          if(tol>0)
          {
             display_points();
          }
          else
          {
             file2<<"invalid Tolerance(only positive value) :"<<tol<<endl;
             file.close();
             file1.close();
             file2.close();
             file3.close();
             exit(0);
          }
          break;
     }
    case 18:
     {
          cout<<"Set positive or zero bounds"<<endl;
          cout<<"Set the upper and lower bound for the x: ";
          cin>>x_upper_bound>>x_lower_bound;
          cout<<"Set the upper and lower bound for the y: ";
          cin>>y_upper_bound>>y_lower_bound;
          if(x_upper_bound>0 && x_lower_bound>0 && y_upper_bound>0 && y_lower_bound >0)
           {
              cout<<"Press h to restart the process with new bounds"<<endl;
           }
          //generate_points();
          //generate_cluster();
          //display_points();
           else
            {
                file2<<"Wrong bounds :"<<x_upper_bound<<","<< x_lower_bound <<","<< y_upper_bound<<"," << y_lower_bound<<endl;
                file.close();
                file2.close();
                exit(0);
            } 
          break;
     }
    case 19:
     {
          option();
          break;
     }
  }
}

int main (int argc,char** argv)
{
        char message[200];
//        input();
        file.open("results.txt");
        file1.open("convergence.txt");
        file2.open("error.txt");
        file3.open("data.txt");
 //       generate_points();
   //     generate_cluster();
        option();
 
	glutInit(&argc,argv);
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
	glutInitWindowSize(frameX,frameY);
        glutInitWindowPosition(0,0);
        sprintf(message,"Kmean Algorithm starting with k=10 and increment %d on every refresh",k_incr);
	main_window=glutCreateWindow(message);
        createMenu();
        init();
	glutDisplayFunc(display_points);
	glutMouseFunc(mouse);
        glutKeyboardFunc(handleKeypress);
        glutMainLoop();
 
}
