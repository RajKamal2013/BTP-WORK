#include<fstream>
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include"user_def.h"
//#include"globals.h"
using namespace std;

void handleKeypress(unsigned char key,int x, int y)
{
        char message[200];
        switch (key)
        {
                case 27:  //press esc to quit
                       {
                           file.close();    //results
                           file1.close();   //convergence
                           file2.close();  //errror
                           file3.close();   //data;
                           exit(0); 
                           break;
                       }
                case '0':   //show the menu 
                       {
                           option();
                           break;
                       }
                case 'Z': //clear the screen
                      {
                          system("clear");
                          option();
                          break;
                      }
                   
                case '1':  // display the number red points
                     {
                         if(Red_Points.size()>0)
                          {
                               cout<<"#red points :"<<Red_Points.size()<<endl;
                          }
                          else
                          {
                               cout<<"Error :No red point "<<endl;
                               file2<<"Error :No red point "<<endl;
                          }
                          break;
                     }
                case '2':  // display the number of blue points
                     {
                         if(Blue_Points.size()>0)
                          {
                               cout<<"#blue points :"<<Blue_Points.size()<<endl;
                          }
                          else
                          {
                               cout<<"Error :No blue point "<<endl;
                               file<<"Error :No blue point "<<endl;
                          }
                          break;
                     }
                case '3':  // display the number of cluster points
                     {
                         if(cluster.size()>0)
                          {
                               cout<<"#Maximum Cluster points from algoruthm point of view :"<<cluster.size()<<endl;
                          }
                          else
                          {
                               cout<<"Error :No cluster generated "<<endl;
                               file2<<"Error :No cluster generated "<<endl;
                          }
                          break;
                     }
                case '4':  // display the number of actual cluster points
                     {
                         if(actual_Cluster.size()>0)
                          {
                               cout<<"#Actual Cluster points from algoruthm point of view :"<<actual_Cluster.size()<<endl;
                          }
                          else
                          {
                               cout<<"Error :No actual cluster generated "<<endl;
                               file2<<"Error :No actual cluster generated "<<endl;
                          }
                          break;
                     }
                case '5':  // display the number of cluster points
                     {
                         if(actual_Blue_Cluster.size()>0)
                          {
                               cout<<"#actual blue points forming cover :"<<actual_Blue_Cluster.size()<<endl;
                          }
                          else
                          {
                               cout<<"Error :No actual blue cluster generated "<<endl;
                               file2<<"Error :No actual blue cluster generated "<<endl;
                          }
                          break;
                     }
               case '6': //display whole results 
                    {
                        if((Red_Points.size()>0) && (Blue_Points.size()>0) && (actual_Blue_Cluster.size()>0)) 
                         {
                             cout<<"#red points :"<<Red_Points.size()<<endl;
                             cout<<"#blue points :"<<Blue_Points.size()<<endl;
                             cout<<"#cluster size :"<<actual_Blue_Cluster.size()<<endl;
                         }
                        else
                        {
                           cout<<"Either red point ,blue point or actual blue cluster is not generated"<<endl;
                           file2<<"Either red point ,blue point or actual blue cluster is not generated"<<endl;
                        }
                        break;
                    }
               case '7': //get the idea of cover
                    {
                        cout<<"#red points cover :"<<count_cover()<<endl; 
                        break;
                    }
               case 'a'://genrate the points 
                   {
                      cout<<"Enter the red count and red seed :";
                      cin>>red_count>>red_seed;
                      cout<<"Enter the blue count and blue seed :";
                      cin>>blue_count>>blue_seed;
                     
                      generate_red_points();
                      generate_blue_points();
                      display_point();
                      break;
                   }
                case 'b': //generate the blue point
                   {
                      cout<<"Enter the blue count and blue seed :";
                      cin>>blue_count>>blue_seed;
                      generate_blue_points();
                      display_Blue_Points();
                      break;
                   }
                case 'r': //generate the red point
                   {
                      cout<<"Enter the red count and red seed :";
                      cin>>red_count>>red_seed;
                      generate_red_points();
                      display_Red_Points();
                      break;
                   }
                case 'c': //generate cluster 
                  {
                     cout<<"Enter the cluster size :";
                     cin>>k;
                     generate_cluster();
                     display_cluster();
                     break;
                  }
                   
                case 'A':  //display points
                     { 
                           refresh();
                           if(Red_Points.size()>0)
                            {
                              if(Blue_Points.size()>0)
                                {
                                    display_point();
                                }
                            }
                           else
                            {
                               file2<<"Error:Either red point set is empty or blue point set"<<endl;
                               cout<<"Error:Either red point set is empty or blue point set"<<endl;
                            }
                           break;
                     }
                case 'B' :  //display blue points
                     {
                           refresh();
                           if(Blue_Points.size()>0)
                            {
                                 display_Blue_Points();
                            }
                            else
                            {
                                 file2<<"Error: There is no blue points"<<endl;
                                 cout<<"Error: There is no blue points"<<endl;
                            }
                           break;
                     } 
                case 'C':     //display cluster
                      { 
                            refresh();
                            if(cluster.size()>0)
                              {
                                display_cluster();
                              }
                            else
                              {
                                 file2<<"Error : There is no cluster created "<<endl;
                                 cout<<"Error : There is no cluster created "<<endl;
                              }
                            break;
                      }
                case 'D':   //display actual cluster
                     {
                            refresh();
                            if(actual_Cluster.size()>0)
                            {
                                 display_actual_cluster();
                            }
                            else
                            {
                               file2<<"Error : There is no actual cluster created after cluster "<<endl;
                               cout<<"Error : There is no actual cluster created after cluster "<<endl;
                            }
                            break;
                      }
                case 'E':   //display blue cluster
                      {
                          refresh();
                          if(Blue_cluster.size()>0)
                          {
                                display_Blue_cluster();
                          }
                          else
                          {
                              file2<<"Error : There is no blue cluster "<<endl;
                              cout<<"Error :There is no blue clustere "<<endl;
                          }
                          break;
                      }
                case 'G':   //display actual blue cluster
                      {
                          refresh();
                          if(actual_Blue_Cluster.size()>0)
                            {
                                   display_actual_Blue_cluster();
                            }
                          else
                           {
                              file2<<"Error : There is no actual blue cluster creted"<<endl;
                              cout<<"Error : There is no actual blue cluster creted"<<endl;
                           }
                          break;
                      }
                case 'R':   //display red points
                     {
                            refresh();
                            if(Red_Points.size()>0)
                             {
                                   display_Red_Points();
                             }
                            else
                             {
                                  file2<<"Error : There is no Red point in the set "<<endl;
                                  cout<<"Error : There is no Red point in the set "<<endl;
                             }   
                            break;
                     }
                case 'h':   //generate points and cluster and display the result after one covergenece,cover may or may not be possible
                      {
                          refresh();
                          generate_points();
                          generate_cluster();
                          display_points();
                          break;
                      }
                case 'i':  //generate cluster by incrementing cluster size and display result after converging.
                     {
                         refresh();
                         k=k+k_incr;
                         generate_cluster();
                         display_points();
                         break;
                     }
               case 'I': //generate new cluster of  current size and display the result by converging
                     {
                         
                        refresh();
                        generate_cluster();
                        display_points();
                        break;
                     }
                case 'L' :  //increment K and display the result
                     {
                        k++;
                        generate_cluster();
                        display_points();
                        break;
                     }
                case 'K':  //set the k and display the result
                     {
                        cout<<"Enter the value of K "<<endl;
                        cin>>k;
                        generate_cluster();
                        display_points();
                        break;
                     }
                case 'M' :  //decrement the k and display the result
                     {
                        k--;
                        generate_cluster();
                        display_points();
                        break;
                     }
                case 'N' :  //set new radius
                     {
                        cout<<"Set the new radius :";
                        cin>>rad;
                        break;
                     }
                case 't' :   //automatically find the complete cover .
                     {
                        int tempc,temp,tempi,rcover; 
                        tempc=feasiblity();
                        tempi=k_incr; //save the current K_inc value
                        k_incr=0;    //set k_incr to 0
                        int rcount; //for counting cover
                        if(tempc==1)
                        {
                           cout<<"feasible"<<endl;
                           /*this loop finds the minimum k value that covers all the red point*/
                           do
                           {
                               refresh();   //refresh the screen
                               k=k+k_incr;;  //increment the k value
                               generate_cluster();  //generate the cluster, see generator_fun.cpp for detail
                               /*this loop finds the optimal k cluster according to K mean algorithm */ 
                                do
                                  {
                                       create_cluster();  //create cluster around the cluster point,see algo_fun.cpp file
                                       create_actual_cluster(); //creates actual cluster ,see algo_func.cpp file
                                       change_median();   //changes median according to cluster form ,see algo_func.cpp file
                                     
                                  }while(ans!=1);  //checks whether tolerance criteria for algorithm is match
                                temp=check();     //check all red points are covered or not.
                                rcover=count_cover();   //count the cover by algorithm
                                file1<<"status "<<temp<<"\t"<<"#red point"<<red_count<<"#blue point :"<<blue_count<<"  k :"<<k<<" size :"<<actual_Cluster.size()<<"#redpoints cover :"<<rcover<<endl; //(for testing) writing in convergence.txt
                             //  cout<<"status "<<temp<<"\t"<<"k"<<k<<endl;(for testing)
                                 k_incr=tempi;    //change the k_incr to default
                            }while(temp!=1);
                            create_Blue_cluster(); //creates blue cluster ,see algo_func.cpp for further
                            create_actual_Blue_cluster();//creates actual blue cluster,see algo_func.cpp for further      
                            complete_cluster(); //  complete the covering of red points by blue points, see algo_func.cpp for detail
//                          sleep(1);    
//                          display_actual_cluster();   //display the actual cluster by algorithm 
                            sleep(1); 
                            display_actual_Blue_cluster();    //display the actual blue cluster that can cover all red point,see display_func.cpp 
                            file<<"#red_point="<<Red_Points.size()<<" "<<"#blue_point="<<Blue_Points.size()<<" "<<"K="<<k<<" "<<"K1="<<actual_Blue_Cluster.size()<<" radius "<<rad<<endl;   //writing in result.txt
                            file3<<Red_Points.size()<<"\t"<<Blue_Points.size()<<"\t"<<actual_Blue_Cluster.size()<<"\n";   //writing in data.txt                                
                      } 
                      else
                      {
                            cout<<"not feasible "<<endl;
                      }     
                      break;
                  }
                 case 'F':  //check the feasiblity 
                     {
                         int temp;
                         temp=feasiblity();
                         if(temp==1)
                          {
                              cout<<"FEASIBLE "<<endl;
                          }
                          else
                          {
                              cout<<"NOT FEASIBLE "<<endl;
                          }
                          break;
                      }
                 case 'S' : //statiscal analysis of the algorithm.
                      {
                          int arr[]={100,200,500,700,1000};   //you can set your own array for your conveneince and set variable arr_size
                          int attempt,temp,tempk,tempb,arr_size;
                          arr_size=5;   //set the array size
                         // cout<<"Enter the #red points and #blue points :";
                         // cin>>red_count>>blue_count;
                          blue_count=50;
                          k=50;
                          k_incr=100;
                          cout<<"Enter the lower bound and upper bound :";
                          cin>>x_lower_bound>>x_upper_bound;
                          y_upper_bound=x_upper_bound;
                          y_lower_bound=x_lower_bound;
                         // cout<<"Enter the cluster size K and the increment factor :";
                         // cin>>k>>k_incr;
                          tempk=k;
                          tempb=blue_count;
                         // cout<<"Enter the number of times you want to repeat the process :";
                         // cin>>attempt;
                          attempt =10;   //set the number of attempts ,means repeatiton with same content
                          int count =0;
                          int cover;
                          for(int j=0;j<arr_size;j++)
                          {
                           red_count=arr[j]; 
                           for(int i=0;i<attempt;i++)
                           {
                               count=0;
                               red_seed=rand() % 1000;
                               blue_seed=rand() %1000;
                               generate_red_points();
                               k=tempk;
                               blue_count=tempb;
                               int maxcount=10;
                               int rcover;
                               do
                                {
                                        for(int i=0;i<40;i++)
                                         {
                                            generate_blue_points();
                                            cover=feasiblity();
                                            blue_seed=rand()%1000;
                                            if(cover==1)
                                                break;
                                         }
                                         cout<<"Feasiblity :"<<cover<<"#blue_count :"<<blue_count<<endl;  
                                         blue_count+=50;
                                }while(cover!=1);
                                blue_count-=50;
                                do
                                {   
                                        count++;
                                        refresh();   //refresh the screen
                                        if(count > 7)  //for large domain we should keep this value low for fast
                                          {
                                             k=k+k_incr;  //increment the k value
                                             count=0;
                                          }
                                        generate_cluster();  //generate the cluster, see generator_fun.cpp for detail
                                        int r;
                                       /*this loop finds the optimal k cluster according to K mean algorithm */
                                        do
                                        {
                                             create_cluster();  //create cluster around the cluster point,see algo_fun.cpp file
                                             create_actual_cluster(); //creates actual cluster ,see algo_func.cpp file
                                             change_median();   //changes median according to cluster form ,see algo_func.cpp file
                                             display_actual_cluster();
                                             r=count_cover();
                                            /* if(0.95*red_count < r) 
                                              {
                                                 ans=1;
                                              } */    
                                        }while(ans!=1);  //checks whether tolerance criteria for algorithm is match*/
                                       temp=check();     //check all red points are covered or not.
                                       rcover=count_cover();
                                        if(0.95*red_count < rcover)   //set a tolrence of cover. and rest can be search bruteforcely ,for fastly convergence
                                              {
                                                 temp=1;
                                              }
                                      
                                       cout<<"status "<<temp<<"\t"<<"#red point"<<red_count<<"#blue point :"<<blue_count<<"  k :"<<k<<" size :"<<actual_Cluster.size()<<"#redpoints cover :"<<rcover<<endl; //(for testing)
                                       file1<<"status "<<temp<<"\t"<<"#red point"<<red_count<<"#blue point :"<<blue_count<<"  k :"<<k<<" size :"<<actual_Cluster.size()<<"#redpoints cover :"<<rcover<<endl; //(for testing)  writing in convergence.txt
                                 }while(temp!=1);
                                cout<<"DONE "<<endl;
                                file1<<"DONE"<<endl;
                                create_Blue_cluster(); //creates blue cluster ,see algo_func.cpp for further
                                create_actual_Blue_cluster();//creates actual blue cluster,see algo_func.cpp for further      
                                complete_cluster(); //  complete the covering of red points by blue points, see algo_func.cpp for detail
                             // sleep(1);    
//                              display_actual_cluster();   //display the actual cluster by algorithm 
                                display_actual_Blue_cluster();    //display the actual blue cluster that can cover all red point,see display_func.cpp 
                      //          sleep(1);
                                file<<"#red_point="<<Red_Points.size()<<" "<<"#blue_point="<<Blue_Points.size()<<" "<<"K="<<k<<" "<<"K1="<<actual_Blue_Cluster.size()<<" radius "<<rad<<endl;   //writing in results.txt
                                file3<<Red_Points.size()<<"\t"<<Blue_Points.size()<<"\t"<<actual_Blue_Cluster.size()<<"\n";   //wrting in data.rxt                                                          
                          }
                        
                         // cout<<"done"<<endl;
                    }
                
             }
          }
}



