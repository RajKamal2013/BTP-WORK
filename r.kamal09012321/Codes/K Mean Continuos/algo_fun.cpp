#include<fstream>  //standard C++ library for the file operations
#include<iostream> //standard C++ library for the input and output functions
#include<cmath>    //standard C++ library for the mathematical functions
#include<cstdio>   //standard C++ library for the C functions 
#include<cstdlib>  //standard C++ library for the exit function
#include<vector>   //standard C++ library for the vector functions 
#include"user_def.h" //include file defining all global variables and functions prototypes
//#include"globals.h"
using namespace std;
 

//function to calculate the eucleadian distance 
double distance(double x1,double y1,double x2,double y2)
 {
    double d,a,b;
    a=(x1-x2)*(x1-x2);
    b=(y1-y2)*(y1-y2);
    d=a*a+b*b;
    d=sqrt(d);   /*sqrt() calcualte the square root ,defined in cmath library*/
    return d;
 }

/*This function check whether all red points are covered or not*/
int check()
{
   int answer=1;
   //setting iterator for red point
   vector<setP> :: iterator itp;   //iterator for red point
   for(itp=Red_Points.begin();itp!=Red_Points.end();itp++)
    {
       if(itp->cover==false)  //check whether a red point is not yet covered
         {
            answer=0;   //set the answer to be 0
            break;      //break the loop
         }
    }
   return answer;       //return the answer
 }


/*This function creates the cluster around the cluster head. For every point in Red_Points vector,it calculates the distance
of the red point with the each cluster head in cluster vector.The cluster head for which distance is minimum ,the red point is
included in the set (set is  a vector defined in cluster structure,see user_def.h for defination ) of that cluster head */ 
void create_cluster()
{
    double min,dist;
    int index;
    int count=0;
    setV vertex;    //setV is structure for maintaining vertex ,defined in user_def.h
    //iterator are used to accesss the vector sequentially ,defined in vector library
    vector<setP> :: iterator itp;  //iterator for the setP(defined in user_def.h) 
    vector<setC> :: iterator itc;  //iterator for the setC(defined in user_def.h)
    //first clear the set attribute of each cluster  
    for(itc=cluster.begin();itc!=cluster.end();itc++)
    {
        itc->set.clear();    //clear the vector
    }

    for(itp=Red_Points.begin();itp!=Red_Points.end();itp++)
    {
            min=10000.0;
            for(itc=cluster.begin();itc!=cluster.end();itc++)
             {
              // dist=distance(itp->x,itp->y,itc->x,itc->y);
              //calculate the eucledian distance
                  dist=(itp->x-itc->x)*(itp->x-itc->x)+(itp->y-itc->y)*(itp->y-itc->y);
                  dist=sqrt(dist);  
                  //find the minimum index i,e the cluster from which distnace is miminum 
                  if(dist<min)
                  {
                       min=dist;
                       index=itc->group;
                  }
             }
             count++;
            //creates the set vertex
             vertex.x=itp->x;
             vertex.y=itp->y;
             //put the set in the cluster at the end
            (cluster.at(index)).set.push_back(vertex);  //at(int index) is defined in vector library to access the element at index
     } 
}

/*This function finds the average of the coordinates and changes the cluster head.It first finds out the average of
X-coordinates and Y-coordinates of the red points in the vector set (defined in cluster vector for maintaining closest
red vertices to the cluster head .see user_def.h) .The averaged X and Y coordinates are then assigned the new cluster head.
The distance between the new and old cluster head is calculated for all cluster head.If the max distance is found is found to
be below Tolerance (tol defined in user_def.h) then we assigned global variable ans =1 otherwise ans=0.ans=1 specify the alorithm
has converged according to the limit set(tol)*/
void change_median()
{
   int count,index;
   double sum_x,sum_y,old_x,old_y,diff;
   //defining iterators for vector of type setC and vectors of type setV.This is defined in vector library.
   vector<setC>::iterator itc;
   vector<setV>::iterator itv;
   double maxdiff=0.0;
   for(itc=cluster.begin();itc!=cluster.end();itc++)
    {
       old_x=itc->x;
       old_y=itc->y;
       count=0;
       sum_x=0;
       sum_y=0;
       //calulating average  
       for(itv=itc->set.begin();itv!=itc->set.end();itv++)
        {
             sum_x+=itv->x;
             sum_y+=itv->y;
             count++;
        }
       //changing the cluster head
       if(count>0)
        {
             itc->x=sum_x/count;
             itc->y=sum_y/count;
        }
       //calculating the difference between old and new coordinates of cluster head
        diff=(itc->x - old_x)*(itc->x - old_x)+(itc->y - old_y)*(itc->y - old_y);
        diff=sqrt(diff);
       //calculaing the maximum differnce and keep updating
        if(maxdiff<diff)
         {
                maxdiff=diff;
         }
    }
   //checking whether convergence is acheived or not and correspong global variable ans is set
   if(maxdiff < tol)
    {
         ans=1;
    }
   else
    {
         ans=0;
    }    

}

/*Function creates actual_cluster vector which is similar to cluster vector.Each cluster head in 
 actual_cluster covers only those Red_Points whose distance from cluster head is within the radius
set.That's the actual covering according to our requirement .A variable state is defined that is set
initially false if the distance between the cluster head and red point comes out to be less than rad 
then the cluster head of the cluster vector is copied to the actual_Cluster vector*/
void create_actual_cluster()
{
     setC tempc;
     vector<setV> tempv;
     //defining iterators for the vectors
     vector<setC>::iterator itc;
     vector<setV>::iterator itv;
     vector<setP>::iterator itp;
     actual_Cluster.clear();
     double x,y,dist,mindist;
    // int count=0;
     bool state=false;
     for(itp=Red_Points.begin();itp!=Red_Points.end();itp++)
     {
          itp->cover=false;
     }
     for(itc=cluster.begin();itc!=cluster.end();itc++)
     {
        
        tempv=itc->set;
        mindist=10000.0;
        x=itc->x;
        y=itc->y;
        state=false;
        for(itp=Red_Points.begin();itp!=Red_Points.end();itp++)
        {
            if(itp->cover==false)
             {
                 //dist=distance(x,y,itp->x,itp->y);
                 //calculating the distance between the cluster head and red point 
                 dist=(x-itp->x)*(x-itp->x)+(y-itp->y)*(y-itp->y);
                 dist=sqrt(dist);
                 if(dist<=rad)
                  {
                    state=true;
                    itp->cover=true;
                  }
             }
        }
        //if the state is true then the cluster head of the cluster vector is copied to the cluster head of the actual_cluster vector
        if(state==true)
         {
             tempc.x=x;
             tempc.y=y;
             tempc.group=itc->group;
             tempc.set=tempv;
             actual_Cluster.push_back(tempc);
         }
     }
 }


/*This function is similar to the create_cluster() function.Once the  cluster vector is created,this finds out
the minimum distance blue point to each cluster head in cluster vector.Then those blue points are used to create another 
cluster ,naming blue_cluster, which  will modify in further functions.This is like mapping of blue point set to the 
cluster set */
void create_Blue_cluster()
{
   int index;
 //defining iterators for the vectors
  vector<setC>::iterator itc;
  vector<setP>::iterator itp;
  setV tempv,vertex;
  setC tempc;
  Blue_cluster.clear();   //clearing the Blue_cluster vector
  double x,y,min_dist,dist;
  double tempx,tempy;
  int tempgroup;
  
  
  for(itc=cluster.begin();itc!=cluster.end();itc++)
  {
        itc->set.clear();    //clear the vector
  }
  //for each cluster head in cluster vector we find the nearest blue point from Blue_point set
  for(itc=cluster.begin();itc!=cluster.end();itc++)
   {
     x=itc->x;
     y=itc->y;
     min_dist=100000.0;
     //cheacking the distance of the each blue point with the cluster head
     for(itp=Blue_Points.begin();itp!=Blue_Points.end();itp++)
     {
        dist=(itp->x-x)*(itp->x-x)+(itp->y-y)*(itp->y-y);  
        dist=sqrt(dist);
        if(min_dist > dist)
         {
            min_dist = dist;
            tempx  = itp->x;
            tempy  = itp->y;
            tempgroup = itc->group;
         }
     }
     //pushing the nearest blue point in the Blue_cluster vector
     tempc.x=tempx;
     tempc.y=tempy;
     tempc.group=tempgroup;
     Blue_cluster.push_back(tempc);
    }  

   // cout<<"SIze of blue cluster "<<Blue_cluster.size()<<endl;
   
    for(itc=Blue_cluster.begin();itc!=Blue_cluster.end();itc++)
    {
        itc->set.clear();
    }
    //For each red point we calculate the minimum distance with the cluster head of the blue_cluster
    //vector and the nearest cluster head is identified.In the set attribute of that head we add the red point
    for(itp=Red_Points.begin();itp!=Red_Points.end();itp++)
    {
        min_dist=100000.0;
        for(itc=Blue_cluster.begin();itc!=Blue_cluster.end();itc++)
         {
           // dist=distance(itp->x,itp->y,itc->x,itc->y);
              dist=(itp->x-itc->x)*(itp->x-itc->x)+(itp->y-itc->y)*(itp->y-itc->y);
              dist=sqrt(dist);
              if(dist<min_dist)
               {
                      min_dist=dist;
                      index=itc->group;
               }
          }
        //  count++;
          vertex.x=itp->x;
          vertex.y=itp->y;
          (Blue_cluster.at(index)).set.push_back(vertex);   
     }
    // cout<<"count :"<<count<<" "<<Red_Points.size()<<endl;
}


/*This function calculates the actual_Blue_cluster.It means it capture only those blue points
 from which the minimum disance between red point is less than radius
 Function creates actual_Blue_cluster vector which is similar to Blue_cluster vector.Each cluster head in 
 actual_Blue_cluster covers only those Red_Points whose distance from cluster head is within the radius
 set.That's the actual covering according to our requirement .A variable state is defined that is set
 initially false if the distance between the cluster head and red point comes out to be less than rad 
 then the cluster head of the cluster vector is copied to the actual_Blue_cluster vector*/
void create_actual_Blue_cluster()
{
     setC tempc;
     vector<setV> tempv;
     vector<setC>::iterator itc;
     vector<setV>::iterator itv;
     vector<setP>::iterator itp;
     actual_Blue_Cluster.clear();
     double x,y,dist,mindist;
     int count=0;
     bool state=false;
     
     for(itp=Red_Points.begin();itp!=Red_Points.end();itp++)
     {
          itp->cover=false;
     }
     for(itc=Blue_cluster.begin();itc!=Blue_cluster.end();itc++)
     {

        tempv=itc->set;
        mindist=100000.0;
        x=itc->x;
        y=itc->y;
        state=false;
        //itp->cover field is used to eliminate the redundant cluster head.One only blue_point will be able to cover a particular 
        //red point.
        for(itp=Red_Points.begin();itp!=Red_Points.end();itp++)
        {
            if(itp->cover==false)
            {
            //dist=distance(x,y,itp->x,itp->y);
              dist=(x-itp->x)*(x-itp->x)+(y-itp->y)*(y-itp->y);
              dist=sqrt(dist);
              if(dist<=rad)
               {
                   itp->cover=true;
                   state=true;
               }
            }
        }
        if(state==true)
         {
               tempc.x=x;
               tempc.y=y;
               tempc.group=itc->group;
               tempc.set=tempv;
               actual_Blue_Cluster.push_back(tempc);
         }
     }
 //  cout<<"count="<<Red_Points.size()<<" "<<count<<endl;
 }

/*There may be the cases that some red point may remain uncovered ,for that purpose we search for those red point and 
add a blue point that cover it.Afer adding that blue point we assign all other uncovered red point covered which 
can be covered by this blue point.The below functions void cover() and void complete_cluster() do these things*/
void cover(double x,double y)
{
   //defining iterator.
   vector<setP>::iterator itp;
   double dist;
   for(itp=Red_Points.begin();itp!=Red_Points.end();itp++)
    {
        if(itp->cover==false)  /*those red point which are not yet cover*/
         {
            dist=(itp->x-x)*(itp->x-x)+(itp->y-y)*(itp->y-y);
            dist=sqrt(dist);
            if(dist<=rad)        
            {
               itp->cover=true;  /*uncovcered red point that can be covered by the blue point are marked coloured*/
            }
        }
   }
}  
/*Manually searching for the uncovered red point*/
void complete_cluster()
{
  //Defining Iterator 
  vector<setP>::iterator itp;
  vector<setP>::iterator itp1;
  double dist,max_dist;
  setC tempc;
  for(itp=Red_Points.begin();itp!=Red_Points.end();itp++)
   {
      if(itp->cover==false)  /*those red point which are not yet covered*/
       {
          for(itp1=Blue_Points.begin();itp1!=Blue_Points.end();itp1++) /*Check for blue point that can cover the uncovered red point*/
            {
                dist=(itp1->x-itp->x)*(itp1->x-itp->x)+(itp1->y-itp->y)*(itp1->y-itp->y);
                dist=sqrt(dist);
                if(dist<=rad) 
                  {
                      itp->cover=true;  //make the uncover red point covered
                      tempc.x=itp1->x;
                      tempc.y=itp1->y;    
                      actual_Blue_Cluster.push_back(tempc); /*blue point that cover that uncovered red point is push into array of cluster*/
                      cover(tempc.x,tempc.y);        /*this cover all other uncovered red point that can be cover by added new blue_point*/
                      break; /*break the for loop to avoid repeatition */
                  }
            }
       }
  }
//file<<"After the complete cover\n";
//file<<"#red_point="<<Red_Points.size()<<" "<<"#blue_point="<<Blue_Points.size()<<" "<<"K="<<k<<" "<<"K1="<<actual_Blue_Cluster.size()<<" radius "<<rad<<endl;
}


/*This function check the feasiblity of the red and blue points*/
int feasiblity()
{
   int temp=0;
   //defining iterators
   vector<setP>::iterator itpr;  //iterator for red point
   vector<setP>::iterator itpb;  //iterator for blue point 
   int dist;
   for(itpr=Red_Points.begin();itpr!=Red_Points.end();itpr++)
    {
       temp=0;
       for(itpb=Blue_Points.begin();itpb!=Blue_Points.end();itpb++)
          {
             dist=(itpr->x-itpb->x)*(itpr->x-itpb->x)+(itpr->y-itpb->y)*(itpr->y-itpb->y);
             dist=sqrt(dist);
             if(dist<rad)
              {
                  temp=1;
                  break;
              }
          }
        if(temp==0)
          break;
    }
   return temp;
 } 
    
int count_cover()
{
   int count=0;
   vector<setP>::iterator itp;
   for(itp=Red_Points.begin();itp!=Red_Points.end();itp++)
    {
        if(itp->cover==true)
         {
           count++;
         }
    }
   return count;
}

   

