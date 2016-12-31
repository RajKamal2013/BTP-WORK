#include<fstream>
#include<iostream>
#include<cstdio>
#include"user_def.h"
//#include"globals.h"
using namespace std;



void option()
{
  cout<<"1.Press esc to escape "<<"               ";
  cout<<"2.Press Z to clear"<<"             ";
  cout<<"3.Press 0 to Display the menu "<<endl;
  cout<<"4.Press 1 to get number of red points "<<"                                              ";
  cout<<"5.Press 2 to get number of blue points"<<endl;
  cout<<"6.Press 3 to get numner of cluster size"<<"                                             ";
  cout<<"7.Press 4 to get actual cluster according to algorithm"<<endl;
  cout<<"8.Press 5 to get cover size"<<"                                                         ";
  cout<<"9.Press 6 to results"<<endl;
  cout<<"10.Press 7 to get the result about cover"<<"                                            "; 
  cout<<"11.Press a to generate red points and blue points "<<endl;
  cout<<"12.Press b to generata blue points "<<"                                                 ";
  cout<<"13.Press r to generate red points"<<endl;  
  cout<<"14.Press c to generate the cluster"<<"                                                  ";  
  cout<<"15.Press A to display points"<<endl; 
  cout<<"16.Press B to display blue point only"<<"                                               ";
  cout<<"17.Press R to display red point only"<<endl;    
  cout<<"18.Press C to display cluster"<<"                                                       ";
  cout<<"19.Press D to display actual Cluster(not cover)"<<endl;
  cout<<"20.Press E to display to display blue cluster"<<"                                       ";
  cout<<"21.Press G to display to display Cover"<<endl;
  cout<<"22.Press h to regenerate points,cluster and display the result"<<endl;
  cout<<"23.Press i to display result with increamented cluster size"<<endl;
  cout<<"24.Press I to display result with same points and cluster size but with different cluster"<<endl;
  cout<<"25.Press t to get display the result in one step"<<endl;
  cout<<"26.Press S for statistically purspose"<<"                                               ";
  cout<<"27.Press L to increment cluster size and display result"<<endl;
  cout<<"28.Press K to generate new cluster  with any size and display result"<<endl;
  cout<<"29.Press M to decrement cluster size and display result"<<endl;
  cout<<"30.Press F to check the feasilblity"<<"                                                 ";
  cout<<"31.Press N to set new radius"<<endl;
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
