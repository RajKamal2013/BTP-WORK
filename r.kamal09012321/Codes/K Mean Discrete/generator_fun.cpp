#include<fstream>   /*standard C++ library for file operations */
#include<iostream>  /*standard C++ library for input and output*/
#include<cmath>     /*stnadard C++ library for math function*/
#include<cstdio>    /*standard C++ library for c standard function library */
#include<cstdlib>   /*standard C++ library for exit function*/
#include<vector>    /*standard C++ library for implementing vector*/
#include"user_def.h"/*include file created for all listing all functions and variable */
//#include"globals.h"
using namespace std;


/*This function takes input x and y coordinates as input.It then creates a structure setP.Based on choice variable 
it add to the vector (dynamic array) of red or blue point (push_back function is standard function of vector library )*/ 
void create_set(double x,double y,int choice )
{
   setP temp;     //setP is defined in file user_def.h
   temp.x=x;
   temp.y=y;
   temp.group=0;
   if(choice == Red)
    {
       temp.cover=false; 
       Red_Points.push_back(temp);  //push_back() adds at the last in vector(dynamic array).It is defined in vector library
    }
   if(choice == Blue)
    {
       Blue_Points.push_back(temp);  //push_back() adds at the last in the vector(dynamic array).It is defined in vector library
    }
}

/*This function generates random x and y coordinates and create red and blue points .First is generates 
red points and then generates blue points.It passes the random generated coordinates to function create_set 
which then creates structure setP adds the structure to the vector (dynamic array) of red or blue points correspondingly*/ 
void generate_points()
{
  Red_Points.clear();           //clear() is defined in vector library and it clears(empty) the vector(dynamic array)
  Blue_Points.clear();          //clear() is defined in vector library and it clears(empty) the vector(dynamic array)
  float x,y;
  srand(red_seed);              //srand () function causes rand() function to generate random value based on seed value
  for(int i=0;i<red_count;i++)
   {
     x=rand() % x_upper_bound + x_lower_bound;   //rand() is standard function for generating random numbers
     y=rand() % y_upper_bound + y_lower_bound;   //rand() is standard function for generating random numbers
     create_set(x,y,Red);                        
   }
  srand(blue_seed);             //srand() causes rand() to generate random numbers based on seed value
  for(int i=0;i<blue_count;i++)
   {
     x=rand() % x_upper_bound+x_lower_bound;  //rand() generates random numbers
     y=rand() % y_upper_bound+y_lower_bound;  //rand() generates random numbers
     create_set(x,y,Blue);
   }
 }



/*similar to generate_point function only difference it regenerates all red points removing previously
generated red points without affecting blue points */
void generate_red_points()
{
  float x,y;
  Red_Points.clear(); //clear() function clears(empty) the vector(dynamic array),defined in vector library.
  srand(red_seed);    //srand() causes rand() to generate random numbers based on seed value   
  for(int i=0;i<red_count;i++)
   {
     x=rand() % x_upper_bound+x_lower_bound;  //rand() generates random number
     y=rand() % y_upper_bound+y_lower_bound;  //rand() generates random number
     create_set(x,y,Red);
   }
}

/*similar to generate_point function only difference it regenerates all blue points removing previously
generated blue points without affecting blue points */
void generate_blue_points()
{
  float x,y;
  Blue_Points.clear();    //clear the vector
  srand(blue_seed);       //causes rand() to generate random points based on seed value
  for(int i=0;i<blue_count;i++)
   {
     x=rand() % x_upper_bound+x_lower_bound;   //rand() generates random numbers
     y=rand() % y_upper_bound+y_lower_bound;   //rand() generates random number
     create_set(x,y,Blue);
   }
}


/*This function generates initial cluster.It generates random cluster by picking arbit points from
vector of blue point.THen it adds those arbit blue points to the vector cluster */
void generate_cluster()
{
   cluster.clear();    //clear the vector.(empty the set cluster)
   int psize,temp;
   psize=Blue_Points.size();  //size() returns the size of vector
   setC c;                    //setC is defined in user_def.h file
   setP p;                    //setP is defined in uset_def.h file 
   cluster_seed=rand()%psize; //rand() generates random numbers
   srand(cluster_seed);
   if(k>0)         //checking if the k value go to negative due to negative k_incr factor
   {
      for(int i=0;i<k;i++)
      {
         temp=rand() % psize;
         p=Blue_Points.at(temp);   //at(int index) is defined in vector library ,returns vector at the index.
         c.x=p.x;
         c.y=p.y;
         c.group=i;
         cluster.push_back(c);    //push_back() is defined in vector that adds at the last.
      }
   }
   else        //checking if the k value go to negative due to negative k_incr factor
   {
      file2<<"The K value is negative due to k_inc"<<endl;
      cout<<"K value is gone negative due to negative increment factor(error is written in error.txt file"<<endl;
      cout<<"Enter the k value and the increment factor :";
      cin>>k>>k_incr;
      for(int i=0;i<k;i++)
      {
         temp=rand() % psize;
         p=Blue_Points.at(temp);   //at(int index) is defined in vector library ,returns vector at the index.
         c.x=p.x;
         c.y=p.y;
         c.group=i;
         cluster.push_back(c);    //push_back() is defined in vector that adds at the last.
      }
   }
}

