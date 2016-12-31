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


/*this Function display only red points*/
void  display_Red_Points()
{       
      if(Red_Points.size()>0)
      {
          float x1,y1;
          //definig iterator for red point 
          vector<setP>::iterator it;
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //clear the screen
          glMatrixMode(GL_MODELVIEW); //switches to drawing perspective
          glLoadIdentity();   //reset the drawing perspective

          glBegin(GL_POINTS);  //begin the process
          glColor3f(1.0f,0.0f,0.0f);  //sets the vertex color (red color)
          glPointSize(1.0f);  //sets the point size
          //draw the red points
          for (it = Red_Points.begin() ; it != Red_Points.end(); ++it)
          {
            /*This draw a bullet dot.FOr this a circle of very small radius is drawn.If you don't like bullet comment the 6 l                               ines uncomment the line 39.YOu can vary the bullet size by varrrying the 0.2 to any value*/
            for(float i=0;i<3.1416*2;i+=0.01)
             {
                 x1=it->x+0.2*cos(i);
                 y1=it->y+0.2*sin(i);
                 glVertex2f(x1*mapx,y1*mapy);  //draw the vertex at coordinates (x1,y1)
             }

           //   glVertex2f(it->x*mapx,it->y*mapy);
         }
         glEnd();  //end the process
         glutSwapBuffers();  //send the 3D scene to screen
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //clears the screen 
         // cout<<"RED POINTS :"<<red_count<<" "<<Red_Points.size()<<endl;  //this one for testing
      }
      else
      {
        cout<<"There is no red points"<<endl;
      }
}           


//This function Display only Blue points
void  display_Blue_Points()
{
       if(Blue_Points.size()>0)
        {
           float x1,y1;
           //Defining iterator
           vector<setP>::iterator it;
           glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   //clears the screen 
           glMatrixMode(GL_MODELVIEW);    //switches to drawing perspective
           glLoadIdentity();       //resets the drawing perspective

           glBegin(GL_POINTS);     //begin the drawing process
           glColor3f(0.0f,1.0f,1.0f);  //sets the color (blue color)
           glPointSize(1.0f);         //sets the point size
           for (it = Blue_Points.begin() ; it != Blue_Points.end(); ++it)
             {
                /*This draw a bullet dot.FOr this a circle of very small radius is drawn.If you don't like bullet comment the 6 l                               ines uncomment the line 71.YOu can vary the bullet size by varrrying the 0.2 to any value*/
                 for(float i=0;i<3.1416*2;i+=0.01)
                    {
                        x1=it->x+0.2*cos(i);
                        y1=it->y+0.2*sin(i);
                        glVertex2f(x1*mapx,y1*mapy);  //draw the vertex
                    }

                 //   glVertex2f(it->x*mapx,it->y*mapy);
             }
          glEnd();
          glutSwapBuffers(); //send the 3D scene to screen
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          //cout<<"BLUE POINTS :"<<blue_count<<" "<<Blue_Points.size()<<endl;
      }
      else
      {
         cout<<"Error: There is no blue points "<<endl;
      }
}

void display_red_result()
{
   int rcount=0;
   vector<setP>::iterator itp;
   for(itp=Red_Points.begin();itp!=Red_Points.end();itp++)
    {
       rcount++;
       file3<<rcount<<"."<<"("<<itp->x<<","<<itp->y<<")"<<"  Group :"<<itp->group<<" cover :"<<itp->cover<<endl;
    }
}

/*This Function displays all the cluster points and draw a cicle of corresponding radius  around the cluster.*/
void display_cluster()
{
     if(cluster.size()>0)
      {
         float x1,y1;
         //Defining iterators
         vector<setP>::iterator it;   //iterator for red points
         vector<setC>::iterator itc;  //iterator for cluster points
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //Clear information from last draw.Its an opengl Functiona and clears the screen
         glMatrixMode(GL_MODELVIEW);  //its an opengl function and switches to the drawing perspective.
         glLoadIdentity();            //Reset the drawing perspective.
     
         glBegin(GL_POINTS); //It starts the drawing process
         glPointSize(1.0f);   //sets the point size.
         glColor3f(1.0f,1.0f,0.0f);//sets the color of dots (yellow color)
         for(itc=cluster.begin();itc!=cluster.end();itc++) 
         {     
            /*This draw a bullet dot.FOr this a circle of very small radius is drawn.If you don't like bullet comment the 6 lines 
            uncomment the line 104.YOu can vary the bullet size by varrrying the 0.2 to any value*/
            for(float i=0;i<3.1416*2;i+=0.01)
             {
                 x1=itc->x+0.2*cos(i);
                 y1=itc->y+0.2*sin(i);
                 glVertex2f(x1*mapx,y1*mapy);   //it draw the points
             }

               // glVertex2f(itc->x*mapx,itc->y*mapy);
         }
        glEnd(); 
        glutSwapBuffers(); //send the 3D scene to screen

 
        glBegin(GL_POINTS);   //It starts the drawing process
        glPointSize(1.0f);    //sets the point size
        glColor3f(1.0f,1.0f,1.0f); //sets the color (white color)
        int rad1;
        for(itc=cluster.begin();itc!=cluster.end();itc++)
         {
             if(itc->size>0)  //check if cluster is empty
               {
                  rad1=itc->radius;  //radius of the cluster
                  /*this algorithm draws a cicle of radius rad around the cluster point*/
                  for(float i =0; i<3.1416*2; i+= 0.01 )
                   {
                        x1 = itc->x+rad1 * cos(i);
                        y1 = itc->y+rad1 * sin(i);
                        glVertex2f(x1*mapy,y1*mapx); //draw the vertex
                   } 
               }
          }
        glEnd();
        glutSwapBuffers(); //send the 3D scene to screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //clears the screen
   }
   else
   {
      cout<<"Error:There is no cluster created "<<endl;
   }
}

void display_actual_cluster()
{
    if(Red_Points.size()>0)   //checks if there are more or equal than 1 red point 
    {
       if(Blue_Points.size()>0) //checks if there are more or equal than 1 blue point 
        {
          if(actual_cluster.size()>0)  //check if there are more than one actual cluster
           {
                //defining the iterator
                vector<setP>::iterator it;  //iterator for the blue and red points
                vector<setC>::iterator itc;  //iterator for the cluster  
                float x1,y1;
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   //clear the screen
                glMatrixMode(GL_MODELVIEW);      //its an opengl function and switches to the drawing perspective.
                glLoadIdentity();  //reset  the drawing prospective

                glBegin(GL_POINTS);  //starts the proces  of drawing
                glColor3f(1.0f,0.0f,0.0f);  //sets the color (red color)
                glPointSize(3.0f);   //sets the point size.
                //draw the red point 
                for (it = Red_Points.begin() ; it != Red_Points.end(); ++it)
                  {
                     /*This draw a bullet dot.FOr this a circle of very small radius is drawn.If you don't like bullet comment the 6 l                               ines uncomment the line 165.YOu can vary the bullet size by varrrying the 0.2 to any value*/
                      for(float i=0;i<3.1416*2;i+=0.01)
                       {
                            x1=it->x+0.2*cos(i);
                            y1=it->y+0.2*sin(i);
                            glVertex2f(x1*mapx,y1*mapy);  //draw the vertex
                       }

                     //glVertex2f(it->x*mapx,it->y*mapy);//draw the red point
                  }
                glEnd();  //end the process
                glutSwapBuffers();  //send the 3D scene to screen

               
                glBegin(GL_POINTS);  //begin the process
                glColor3f(0.0f,1.0f,1.0f);//sets the color
                glPointSize(1.0f);  //sets the dot size
                //drawing the blue point 
                for (it = Blue_Points.begin() ; it != Blue_Points.end(); ++it)
                {
                    /*This draw a bullet dot.FOr this a circle of very small radius is drawn.If you don't like bullet comment the 6 l                               ines uncomment the line 184.YOu can vary the bullet size by varrrying the 0.2 to any value*/
                     for(float i=0;i<3.1416*2;i+=0.01)
                       {
                             x1=it->x+0.2*cos(i);
                             y1=it->y+0.2*sin(i);
                             glVertex2f(x1*mapx,y1*mapy);  //draw the vertex
                       }

                   // glVertex2f(it->x*mapx,it->y*mapy);  //draw the vertex
                }
                glEnd();  //end the process
                glutSwapBuffers();//send the 3D scene to screen

                glBegin(GL_POINTS); //begin the process
                glPointSize(1.0f);   //sets the point size
                glColor3f(1.0f,1.0f,0.0f); //sets the color (yellow color)
                //draw the cluster
                for(itc=actual_cluster.begin();itc!=actual_cluster.end();itc++)
                 {
                      /*This draw a bullet dot.FOr this a circle of very small radius is drawn.If you don't like bullet comment the 6 lines 
                       uncomment the line 191.YOu can vary the bullet size by varrrying the 0.2 to any value*/
                       for(float i=0;i<3.1416*2;i+=0.01)
                       {
                               x1=itc->x+0.2*cos(i);
                               y1=itc->y+0.2*sin(i);
                               glVertex2f(x1*mapx,y1*mapy);   //it draw the points
                       }

                     //glVertex2f(itc->x*mapx,itc->y*mapy);  //draw the vertex
               //      cout<<"radius :"<<itc->radius<<endl;
                }
                glEnd(); //end the process
                glutSwapBuffers();  //send the 3D scene to Screen

                
                glBegin(GL_POINTS);  //restart the drawing
                glPointSize(1.0f);   //sets the point size
                glColor3f(1.0f,1.0f,1.0f); //sets the color
                double rad1;
                //draw the cluster
                for(itc=actual_cluster.begin();itc!=actual_cluster.end();itc++)
                {
                     //cout<<"Index :"<<itc->group<<"Cluster Radius :"<<itc->radius<<"\t"<<"Cluster Head :"<<"("<<itc->x<<","<<itc->y<<")"<<endl;
                     rad1=itc->radius;
                     //draw the circle around the cluster
                     for(float i =0; i<3.1416*2; i+= 0.01 )
                       {
                           x1 = itc->x+rad1 * cos(i);
                           y1 = itc->y+rad1 * sin(i);
                           glVertex2f(x1*mapy,y1*mapx);  //draw the point
                       }
                }

                glEnd();  //end the process
                glutSwapBuffers();  //send the 3D scene to screen
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //clears the window
           }
        }
   }
}

/*This function display red point, blue point,cluster point and a draw a cicle of radius cluster radius around the head.*/
void  display_points()
{
   if(Red_Points.size()>0)   //checks if there are more or equal than 1 red point 
    {
       if(Blue_Points.size()>0) //checks if there are more or equal than 1 blue point 
        {
           //  generate_cluster();      //generate cluster according to cluster size.check about it in algo_fun.cpp file
      //       create_cluster();        //create cluster as defined in algo_fun.cpp
             //defining the iterator
             vector<setP>::iterator it;  //iterator for the blue and red points
             vector<setC>::iterator itc;  //iterator for the cluster  
             float x1,y1;
             int ccount=0;//convergence count
             int rcount;  //red count;
             cout<<"\n K :"<<k<<endl;
             file4<<"\n K :"<<k<<endl;
                 //uncomment to see how algorithm works.
             do
              {    
                ccount++;
                create_cluster();
                change_cluster_head();
                set_cur_radius();
                
                
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   //clear the screen
                glMatrixMode(GL_MODELVIEW);      //its an opengl function and switches to the drawing perspective.
                glLoadIdentity();  //reset  the drawing prospective
        
                glBegin(GL_POINTS);  //starts the proces  of drawing
                glColor3f(1.0f,0.0f,0.0f);  //sets the color (red color)
                glPointSize(1.0f);   //sets the point size.
                //draw the red point 
                for (it = Red_Points.begin() ; it != Red_Points.end(); ++it)
                  {
                     /*This draw a bullet dot.FOr this a circle of very small radius is drawn.If you don't like bullet comment the 6 l                               ines uncomment the line 165.YOu can vary the bullet size by varrrying the 0.2 to any value*/
                      for(float i=0;i<3.1416*2;i+=0.01)
                       {
                            x1=it->x+0.2*cos(i);
                            y1=it->y+0.2*sin(i);
                            glVertex2f(x1*mapx,y1*mapy);  //draw the vertex
                       }

                     //glVertex2f(it->x*mapx,it->y*mapy);//draw the red point
                  }
                glEnd();  //end the process
                glutSwapBuffers();  //send the 3D scene to screen

                glBegin(GL_POINTS);  //begin the process
                glColor3f(0.0f,1.0f,1.0f);//sets the color
                glPointSize(1.0f);  //sets the dot size
                //drawing the blue point 
                for (it = Blue_Points.begin() ; it != Blue_Points.end(); ++it)
                {
                    /*This draw a bullet dot.FOr this a circle of very small radius is drawn.If you don't like bullet comment the 6 l                               ines uncomment the line 184.YOu can vary the bullet size by varrrying the 0.2 to any value*/
                     for(float i=0;i<3.1416*2;i+=0.01)
                       {
                             x1=it->x+0.2*cos(i);
                             y1=it->y+0.2*sin(i);
                             glVertex2f(x1*mapx,y1*mapy);  //draw the vertex
                       }

                   // glVertex2f(it->x*mapx,it->y*mapy);  //draw the vertex
                }  
                glEnd();  //end the process
                glutSwapBuffers();//send the 3D scene to screen


                glBegin(GL_POINTS); //begin the process
                glPointSize(1.0f);   //sets the point size
                glColor3f(1.0f,1.0f,0.0f); //sets the color (yellow color)
                //draw the cluster
                for(itc=cluster.begin();itc!=cluster.end();itc++)
                 {
                      /*This draw a bullet dot.FOr this a circle of very small radius is drawn.If you don't like bullet comment the 6 lines 
                       uncomment the line 191.YOu can vary the bullet size by varrrying the 0.2 to any value*/
                       for(float i=0;i<3.1416*2;i+=0.01)
                       {
                               x1=itc->x+0.2*cos(i);
                               y1=itc->y+0.2*sin(i);
                               glVertex2f(x1*mapx,y1*mapy);   //it draw the points
                       }

                     //glVertex2f(itc->x*mapx,itc->y*mapy);  //draw the vertex
               //      cout<<"radius :"<<itc->radius<<endl;
                }
                glEnd(); //end the process
                glutSwapBuffers();  //send the 3D scene to Screen

 
                glBegin(GL_POINTS);  //restart the drawing
                glPointSize(1.0f);   //sets the point size
                glColor3f(1.0f,1.0f,1.0f); //sets the color
                double rad1;
                //draw the cluster
                for(itc=cluster.begin();itc!=cluster.end();itc++)
                {
                     //cout<<"Index :"<<itc->group<<"Cluster Radius :"<<itc->radius<<"\t"<<"Cluster Head :"<<"("<<itc->x<<","<<itc->y<<")"<<endl;
                     rad1=itc->radius;
                     //draw the circle around the cluster
                     for(float i =0; i<3.1416*2; i+= 0.01 )
                       {
                           x1 = itc->x+rad1 * cos(i);
                           y1 = itc->y+rad1 * sin(i);
                           glVertex2f(x1*mapy,y1*mapx);  //draw the point
                       }
                }
                
                glEnd();  //end the process
                glutSwapBuffers();  //send the 3D scene to screen
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //clears the window 
                
                rcount=count_cover();
            
                cout<<"Current radius :"<<cur_rad<<" #red point covered :"<<rcount<<endl;
                file4<<"Current radius :"<<cur_rad<<" #red Point covered :"<<rcount<<endl;
             }while(ans!=1);       
             create_actual_cluster();
      //       sleep(1);
        //     display_actual_cluster();
             cout<<"#red point cover :"<<rcount<<" convergence count :"<<ccount<<" Converged with Actual Cluster size "<<actual_cluster.size()<<endl<<endl; 
             file4<<"#red point cover :"<<rcount<<" convergence count :"<<ccount<<" Converged with Acual Cluster size "<<actual_cluster.size()<<endl<<endl; 
           // cout<<"Current radius :"<<cur_rad<<endl;
             file<<"#Red Points :"<<Red_Points.size()<<" #Blue Points :"<<Blue_Points.size()<<" CLuster Size :"<<k<<"Actual Cluster size :"<<actual_cluster.size()<<" Radius :"<<cur_rad<<endl;
        }
   }
}


void  display_point()
{
   if(Red_Points.size()>0)   //checks if there are more or equal than 1 red point 
    {
       if(Blue_Points.size()>0) //checks if there are more or equal than 1 blue point 
        {
               // generate_cluster();      //generate cluster according to cluster size.check about it in algo_fun.cpp file
                //defining the iterator
                vector<setP>::iterator it;  //iterator for the blue and red points
                vector<setC>::iterator itc;  //iterator for the cluster  
     
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   //clear the screen
                glMatrixMode(GL_MODELVIEW);      //its an opengl function and switches to the drawing perspective.
                glLoadIdentity();  //reset  the drawing prospective
        
                glBegin(GL_POINTS);  //starts the proces  of drawing
                glColor3f(1.0f,0.0f,0.0f);  //sets the color (red color)
                glPointSize(1.0f);   //sets the point size.
                //draw the red point 
                float x1,y1;
                for (it = Red_Points.begin() ; it != Red_Points.end(); ++it)
                  {
                       /*This draw a bullet dot.FOr this a circle of very small radius is drawn.If you don't like bullet comment the 6 lines 
                       uncomment the line 191.YOu can vary the bullet size by varrrying the 0.2 to any value*/
                       for(float i=0;i<3.1416*2;i+=0.01)
                       {
                               x1=it->x+0.3*cos(i);
                               y1=it->y+0.3*sin(i);
                               glVertex2f(x1*mapx,y1*mapy);   //it draw the points
                       }

                    // glVertex2f(it->x*mapx,it->y*mapy);//draw the red point
                  }
                glEnd();  //end the process
                glutSwapBuffers();  //send the 3D scene to screen

                glBegin(GL_POINTS);  //begin the process
                glColor3f(0.0f,1.0f,1.0f);//sets the color
                glPointSize(1.0f);  //sets the dot size
                //drawing the blue point 
                for (it = Blue_Points.begin() ; it != Blue_Points.end(); ++it)
                {
                      /*This draw a bullet dot.FOr this a circle of very small radius is drawn.If you don't like bullet comment the 6 lines 
                       uncomment the line 191.YOu can vary the bullet size by varrrying the 0.2 to any value*/
                       for(float i=0;i<3.1416*2;i+=0.01)
                       {
                               x1=it->x+0.3*cos(i);
                               y1=it->y+0.3*sin(i);
                               glVertex2f(x1*mapx,y1*mapy);   //it draw the points
                       }

                 //   glVertex2f(it->x*mapx,it->y*mapy);  //draw the vertex
                }  
                glEnd();  //end the process
                glutSwapBuffers();//send the 3D scene to screen


               // float x1,y1; 
                glBegin(GL_POINTS); //begin the process
                glPointSize(1.0f);   //sets the point size
                glColor3f(1.0f,1.0f,0.0f); //sets the color (yellow color)
                //draw the cluster
                for(itc=cluster.begin();itc!=cluster.end();itc++)
                 {
                      /*This draw a bullet dot.FOr this a circle of very small radius is drawn.If you don't like bullet comment the 6 lines 
                       uncomment the line 191.YOu can vary the bullet size by varrrying the 0.2 to any value*/
                       for(float i=0;i<3.1416*2;i+=0.01)
                       {
                               x1=itc->x+0.2*cos(i);
                               y1=itc->y+0.2*sin(i);
                               glVertex2f(x1*mapx,y1*mapy);   //it draw the points
                       }

                     //glVertex2f(itc->x*mapx,itc->y*mapy);  //draw the vertex
                }
                glEnd(); //end the process
                glutSwapBuffers();  //send the 3D scene to Screen

 
                glBegin(GL_POINTS);  //restart the drawing
                glPointSize(1.0f);   //sets the point size
                glColor3f(1.0f,1.0f,1.0f); //sets the color
                int rad1;
                //draw the cluster
                for(itc=cluster.begin();itc!=cluster.end();itc++)
                {
                     rad1=itc->radius;
                     //draw the circle around the cluster
                     for(float i =0; i<3.1416*2; i+= 0.01 )
                       {
                           x1 = itc->x+rad1 * cos(i);
                           y1 = itc->y+rad1 * sin(i);
                           glVertex2f(x1*mapx,y1*mapy);  //draw the point
                       }
                }
                glEnd();  //end the process
                glutSwapBuffers();  //send the 3D scene to screen
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //clears the window         
        }
   }
}


