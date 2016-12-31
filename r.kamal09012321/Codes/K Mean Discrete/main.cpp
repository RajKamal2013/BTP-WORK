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
int k_incr=2;
int rad=10;
double cur_rad=0;
float tol=0.0001;
int red_count=50;
int blue_count=200;
int ans=0;
int result=0;
int k1;
float mapx=10.0; //7.0
float mapy=10.0; //7.0
int factorX=10;
int factorY=10;
int x_upper_bound=100;
int x_lower_bound=0;
int y_lower_bound=0;
int y_upper_bound=100;
int frameX=1000;
int frameY=1000;

int draw=0;
int generate=0;
int mainmenu=0;
int set=0;
int val=0;
int main_window;
int display=0;

ofstream file;
ofstream file2;
ofstream file3;
ofstream file4;
ofstream file5;
vector<setP> Red_Points;
vector<setP> Blue_Points;
vector<setC>cluster;
vector<setC>actual_cluster;
//vector<setC>Blue_cluster;
//vector<setC>actual_Blue_Cluster;







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
     case 0 ://exit the code
     {
          glutDestroyWindow(main_window);
          file.close();
          file2.close();
          exit(0);
          break;
     }
     case 1: //take the input and generate the red points
     {
          cout<<"# red points:";
          cin>>red_count;
          cout<<"enter the seed for red point generation:";
          cin>>red_seed;
          generate_red_points();
          display_points();
          break;
     }
     case 2: //take the input and generate the blue points
     {
          cout<<"# blue points:";
          cin>>blue_count;
          cout<<"enter the seed for blue point generation:";
          cin>>blue_seed;
          generate_blue_points();
          display_points();
          break;
     }
     case 3: //take the input and generate the cluster
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
     case 4: //display the red points
     {
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          display_Red_Points();
          break;
     }
     case 5: //display the blue points
     {
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          display_Blue_Points();
          break;
     }
     case 6://displays the points
     {
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          display_point();
          break;
     }
     case 7://display the cluster
     {
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          display_cluster();
          break;    
     }
     case 8:
     {
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          //display_actual_cluster();
          break;    
     }
     case 9:
     {
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          //display_Blue_cluster();
          break;    
     }
     case 10:
     {
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          //display_actual_Blue_cluster();
          break;    
     }
     case 11: //display the value of k
     {
         cout<<"K :"<<k;
         break;
     }
     case 12: //increment the cluster size and display the points
     {
         k++;
         cout<<"Increamenting the value of K by 1"<<"\tK="<<k<<endl;
         display_points();
         break;
     }
     case 13://decrement the cluster size and display the points
     {
         k--;
         cout<<"Decreamenting the value of K by 1"<<"\tK="<<k<<endl;
         display_points();
         break;
     }
     case 14: //increment the cluster size based on input and display the points
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
    case 15:  //take the cluster size as input and display the points
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
    case 16: //set the radius  and the display accordingly
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
    case 17: //set the tolerance and display the points
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
             file2.close();
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
        file2.open("error.txt");
        file3.open("data.txt");
        file4.open("convergence.txt");
        file5.open("Statical.txt");
       // generate_points();
       // generate_cluster();
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
