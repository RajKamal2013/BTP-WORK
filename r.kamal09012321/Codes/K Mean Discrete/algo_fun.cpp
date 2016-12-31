#include<fstream>  //standard C++ library for the file operations
#include<iostream> //standard C++ library for the input and output functions
#include<cmath>    //standard C++ library for the mathematical functions
#include<cstdio>   //standard C++ library for the C functions 
#include<cstdlib>  //standard C++ library for the exit function
#include<vector>   //standard C++ library for the vector functions 
#include"user_def.h" //include file defining all global variables and functions prototypes
using namespace std;


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


/*This checks how many red points are covered*/    
int count_cover()
{
   int count=0;
   //defining iterator
   vector<setP>::iterator itp;  //iterator for red points
   for(itp=Red_Points.begin();itp!=Red_Points.end();itp++)
    {
        if(itp->cover==true)    //those which are covered
         {
           count++;
         }
    }
   return count;
}

/*This sets the radius of the cluster */
void set_radius()
{
   vector<setC>::iterator itc;
   vector<setV>::iterator itv;
   double max_dist=0;
   double dist;
   int rcount=0;  //to check the cluster size.rcount=cluster.size
   int tcount=0; //to check whether all red point are covered .tcount=red_count
   for(itc=cluster.begin();itc!=cluster.end();itc++)
   {
      max_dist=0;
      rcount=0;
      for(itv=itc->set.begin();itv!=itc->set.end();itv++)
        {
           tcount++;
           rcount++;
           dist=(itc->x-itv->x)*(itc->x-itv->x)+(itc->y-itv->y)*(itc->y-itv->y);
           dist=sqrt(dist);
           if(dist>max_dist)
               {
                    max_dist=dist;
               }
         }
      itc->radius=max_dist;
      //cout<<"Radius "<<itc->radius<<endl;
      file3<<"Cluster size :"<<k<<" Process of clustering resulted into the following "<<endl;
      file3<<"Group :"<<itc->group<<" Cluster size :"<<rcount<<"max radius :"<<max_dist<<" Radius :"<<itc->radius<<endl;
    }
    file3<<endl<<endl;
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

    for(itc=cluster.begin();itc!=cluster.end();itc++)
    {
         itc->size=0;
         itc->radius=0;
    }
   
    for(itp=Red_Points.begin();itp!=Red_Points.end();itp++)
    {
            min=10000.0;
            for(itc=cluster.begin();itc!=cluster.end();itc++)
             {
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
             //put the set in the cluster at the end and increse the size of cluster
            (cluster.at(index)).size++;
            (cluster.at(index)).set.push_back(vertex);  //at(int index) is defined in vector library to access the element at index
            if(min<=rad)
             {
                 itp->cover=true;
             }
            else
             {
                 itp->cover=false;
             }
            itp->group=index;
     } 
   set_radius();  //sets the radius of the cluster.
}

void create_actual_cluster()
{
  actual_cluster.clear();
  vector<setC>::iterator itc;
  vector<setC>::iterator itc1;
  setC tempC;
  setV tempV; 
 
  for(itc=cluster.begin();itc!=cluster.end();itc++)
   {
       if(itc->size>0)
        {
           tempC.x=itc->x;
           tempC.y=itc->y;
           tempC.group=itc->group;
           tempC.size=itc->size;
           tempC.radius=itc->radius;
           tempC.set=itc->set;
           actual_cluster.push_back(tempC);
        }
   }
}  


void set_cur_radius()
{
  vector<setC> :: iterator itc;
  double max=0;
  for(itc=cluster.begin();itc!=cluster.end();itc++)
   {
      if(itc->radius > max)
         {
            max=itc->radius;
         }
   }
   cur_rad=max;
}

void change_cluster_head()
{
   vector<setP>:: iterator itp; 
   vector<setC>:: iterator itc;
   vector<setV>:: iterator itv;
   double x,y,old_x,old_y,old_rad,dist,max_dist,min_rad,temp_x,temp_y,temp_rad,diff,max_diff;
   int state;
   max_diff=10000;
   for(itc=cluster.begin();itc!=cluster.end();itc++)
   {
       if(itc->radius>0)
        {
             old_x=itc->x;
             old_y=itc->y;
             old_rad=itc->radius;
             min_rad=10000;  
             max_diff=0;
             state=0;  //for checking change in current state
             for(itp=Blue_Points.begin();itp!=Blue_Points.end();itp++)
             {
                  max_dist=0;
                  for(itv=itc->set.begin();itv!=itc->set.end();itv++)
                   {
                           dist=(itp->x-itv->x)*(itp->x-itv->x)+(itp->y-itv->y)*(itp->y-itv->y);
                           dist=sqrt(dist);
                           if(dist>old_rad)
                           {
                                    max_dist=dist;
                                    break;
                           }
                          else
                          {
                                    if(dist > max_dist)
                                      {
                                           max_dist=dist;
                                      }
                          }
                   }
                 if(max_dist<old_rad)
                   {
                          if(max_dist < min_rad)
                           {
                                     state=1;
                                     min_rad=max_dist;
                                     temp_x=itp->x;
                                     temp_y=itp->y;
                                     temp_rad=min_rad;
                            }
                   }
             }
             if(state==1)
              {
                  diff=(old_x-temp_x)*(old_x-temp_x)+(old_y-temp_y)*(old_y-temp_y);
                  diff=sqrt(diff);
                  if(max_diff<diff)
                   {
                           max_diff=diff;
                   }
                   itc->x=temp_x;
                   itc->y=temp_y;
                   itc->radius=temp_rad;
                 //  cout<<"itc->radius :"<<itc->radius<<endl;
              }
         }
    }
  if(max_diff<tol)
   {
      ans=1;
   }
  else
   {
     ans=0;
   }
}


