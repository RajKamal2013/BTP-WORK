#include<fstream>
#include<iostream>
#include<cstdio>
#include"user_def.h"
//#include"globals.h"
using namespace std;



void option()
{
  cout<<"\n \n MENU ================>"<<endl;
  cout<<"1.Press esc to escape "<<"                                                      ";
  cout<<"2.Press to clear the screen and diplay the menu "<<endl;
  cout<<"3.Press 1 to display number of red points"<<"                                   ";
  cout<<"4.Press 2 to display number of blue points"<<endl;
  cout<<"5.Press 3 to display number of cover"<<"                                        ";
  cout<<"6.Press 4 to display the resutls"<<endl;
  cout<<"7.Press a to display points"<<"                                                 ";
  cout<<"8.Press b to display blue points only"<<endl;
  cout<<"9.Press B to create new Blue point set with new information "<<"                ";
  cout<<"10.Press R to create new Red point set with new information "<<endl;
  cout<<"11.Press K to enter the new increament factor"<<"                               ";
  cout<<"12.Press c to display cluster points"<<endl;
  cout<<"13.Press d to display actual_cluster points"<<"                                 ";
  cout<<"14.Press e for statistical purpose"<<endl;                                    
//  cout<<"Press f to display actual Blue Cluster Point"<<endl;
  cout<<"15.Press g to display Red Points"<<endl;
  cout<<"16.Press h to restart the process with new but same number of red,blue point and cluster "<<endl;
  cout<<"17.Press i to increment the cluster point "<<"                                   ";
  cout<<"18.press I to display the result of algoritm with the present K"<<endl;
  cout<<"19.Press j to display red point only "<<"                                        ";  
  cout<<"20.Press k to increment cluster size k "<<endl;  
  cout<<"21.Press l to decrement cluster size k "<<"                                      ";  
  cout<<"22.Press m to display menu again "<<endl;  
  cout<<"23.Press r to get result in one step"<<"                                         ";
  cout<<"24.Press s to get the red point status in file "<<endl;
  cout<<"25.Press t to check feasilblity "<<"                                             ";
  cout<<"26.Press u to get result maintaining same cluster and cluster size "<<endl;
  cout<<"27.Press v to get result maintaining same cluster size not same cluster."<<"     ";
  cout<<"28.Press w to generate new red and blue points."<<endl;
  cout<<"29.Press x to generate the new cluster with the new cluster size "<<"            ";
  cout<<"30.Press M to get cover information of red point is file "<<endl;
  cout<<"31.Press N to enter the new radius ";
  cout<<endl<<endl;
}



void input()
{
   cout<<"Enter the seed and count for red point:  ";
   cin>>red_seed>>red_count;
   cout<<"Enter the seed and count for blue point: ";
   cin>>blue_seed>>blue_count;
   cout<<"Enter the value of k and the increment factor of k: ";
   cin>>k>>k_incr;
   cout<<"Enter the Cluster seed: ";
   cin>>cluster_seed;
} 
