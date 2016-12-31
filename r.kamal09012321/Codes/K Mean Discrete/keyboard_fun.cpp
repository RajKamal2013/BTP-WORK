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
                case 27: //exit
                       {
                           file.close();
                           file2.close();
                           file3.close();
                           file4.close();
                           file5.close();
                           exit(0); 
                           break;
                       }
                case 'A':
                       {
                           system("clear");
                           option();
                           break;
                       }
                case '1': //display number of red points.
                       {
                          if(Red_Points.size()>0)
                          {
                                   cout<<"The Number of red points are :"<<Red_Points.size()<<endl;
                          }
                          else
                          {
                                   cout<<"Error: No red points are present "<<endl;
                          }
                          break;
                       }
                case '2': //display number of blue points.
                       {
                          if(Blue_Points.size()>0)
                          {
                                   cout<<"The Number of blue points are :"<<Blue_Points.size()<<endl;
                          }
                          else
                          {
                                   cout<<"Error: No blue points are present "<<endl;
                          }
                          break;
                       }
                case '3': //display cover result
                       {
                          if(actual_cluster.size()>0)
                          {
                                cout<<"Cover size "<<actual_cluster.size()<<endl;
                          }
                          else
                          {
                               cout<<"Error : No cover found"<<endl;
                          }
                          break;
                      }
                case '4':  //dsiplay all results
                      {
                          cout<<"Results"<<endl;
                          if(Red_Points.size()>0)
                          {
                                   cout<<"The Number of red points are :"<<Red_Points.size()<<endl;
                          }
                          else
                          {
                                   cout<<"Error: No red points are present "<<endl;
                          }
                          if(Blue_Points.size()>0)
                          {
                                   cout<<"The Number of blue points are :"<<Blue_Points.size()<<endl;
                          }
                          else
                          {
                                   cout<<"Error: No blue points are present "<<endl;
                          }
                          if(actual_cluster.size()>0)
                          {
                                cout<<"Cover size "<<actual_cluster.size()<<endl;
                          }
                          else
                          {
                               cout<<"Error : No cover found"<<endl;
                          }
                          break;
                      }
                case 'a': //display points
                     { 
                           refresh();
                           display_point();
                           break;
                     }
                case 'b' :  //display only blue points
                     {
                           refresh();
                           display_Blue_Points();
                           break;
                     } 
                case 'c':  //display only cluster
                      {
                            refresh();
                            display_cluster();
                            break;
                      }
                case 'd':
                     {
                            refresh();
                            display_actual_cluster();
                            break;
                      }
                case 'e':  //statistically analyse using it.
                      {
                          refresh();
                          int arr[]={100,200,500,700,1000,2000,5000};
                          int attempt,temp,tempk,tempb;
                          blue_count=50;
                          k=25;
                          k_incr=15;
                          cout<<"Enter the lower bound and upper bound :";
                          cin>>x_lower_bound>>x_upper_bound;
                          y_upper_bound=x_upper_bound;
                          y_lower_bound=x_lower_bound;
                         
                          //graphics and display purpose
                          factorX=(frameX/(x_upper_bound-x_lower_bound));
                          factorY=factorX;
                          mapx=factorX;
                          mapy=factorY;
                         
                          tempk=k;
                          tempb=blue_count;
                          attempt =20;
                          int count =0;
                          int cover;
                          for(int j=0;j<7;j++)
                            {
                                red_count=arr[j];
                                sleep(1);
                                for(int i=0;i<attempt;i++)
                                  {
                                      sleep(1);
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
                                            display_points();
                                            int r;
                                            r=count_cover();
                                            temp=check();     //check all red points are covered or not.
                                            rcover=count_cover();
                                            cout<<"status "<<temp<<"\t"<<"#red point"<<red_count<<"#blue point :"<<blue_count<<"  k :"<<k<<" size :"<<actual_cluster.size()<<"#redpoints cover :"<<rcover<<endl; //(for testing)
                                      }while(temp!=1);
                                      cout<<"DONE "<<endl;
                                      file<<"#red_point="<<Red_Points.size()<<" "<<"#blue_point="<<Blue_Points.size()<<" "<<"K="<<k<<" "<<"K1="<<actual_cluster.size()<<" radius "<<cur_rad<<endl;
                                 file5<<Red_Points.size()<<"\t"<<Blue_Points.size()<<"\t"<<actual_cluster.size()<<"\n";                     
                            }
                          }
                          option();
                          break;
                         }
              /*  case 'f':
                      {
                          refresh();
                          display_actual_Blue_cluster();
                          break;
                      }*/
                case 'g': //display red points
                     {
                            refresh();
                            display_Red_Points();
                            break;
                     }
                case 'h': //generate points and display points again 
                      {
                          refresh();
                          generate_points();
                          generate_cluster();
                          display_points();
                          sleep(1);
                          display_actual_cluster();
                          option();
                          break;
                      }
                case 'i': //increment the cluster size and display points
                     {
                         refresh();
                         k=k+k_incr;
                         generate_cluster();
                         display_points();
                         sleep(1);
                         display_actual_cluster();
                         option();
                         break;
                     }
                case 'I': //start the process with the same K .same as case 'i' only thing it has no k_inr
                     {
                         refresh();
                         generate_cluster();
                         display_points();
                         sleep(1);
                         display_actual_cluster();
                         option();
                         break;
                     }
                case 'j': //display red points only
                     {
                         refresh();
                         display_Red_Points();
                         break;
                     }
                case 'k' : //increment the cluster size and display points
                     {
                        k++;
                        generate_cluster();
                        display_points();
                        sleep(1);
                        display_actual_cluster();
                        option();
                        break;
                     }
                case 'l': //decrement the cluster size and display points
                     {
                        k--;
                        generate_cluster(); 
                        display_points();
                        sleep(1);
                        display_actual_cluster();
                        option();
                        break;
                     }
                case 'm':
                     {
                        option();
                        break;
                     }
                case 't': //check the feasiblity
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
                          option();
                      }
                case 'r': //increment the cluster size and display points
                     {
                         int temp;
                         temp=feasiblity();
                         if(temp==1)
                         {
                  
                            do
                            {
                                refresh();
                                k=k+k_incr;
                                generate_cluster();
                                display_points();
                            }while(cur_rad > rad);
                            sleep(1);
                            display_actual_cluster();
                            option();
                        }
                        else
                        {
                           cout<<"NOT FEASIBLE "<<endl;
                        }
                        break;
                     }
                case 's':
                     {
                       display_red_result();
                       break;
                     }
                    
                case 'u':
                     {
                        display_points();
                        sleep(1);
                        display_actual_cluster();
                        option();
                        break;
                     }
                
               case 'v':
                     {
                        generate_cluster();
                        display_points();
                        sleep(1);
                        display_actual_cluster();
                        option();
                        break;
                     }
               case 'w':
                     {
                        cout<<"Enter the number of red points and blue points:";
                        cin>>red_count>>blue_count;
                        cout<<"Enter the seed for the red and blue points :";
                        cin>>red_seed>>blue_seed;
                        generate_points();
                        display_Red_Points();
                        display_Blue_Points();
                        break;
                     }
              case 'x':
                     {
                        cout<<"Enter the value of k :";
                        cin>>k;
                        generate_cluster();
                        display_points();
                        sleep(1);
                        display_actual_cluster();
                        option();
                        break;
                     }
             case 'R': //generate only red points.
                     {
                        Red_Points.clear();
                        cout<<"Enter the number of red points :";
                        cin>>red_count;
                        cout<<"Enter the seed for the red points generation :";
                        cin>>red_seed;
                        generate_red_points();
                        display_Red_Points();
                        display_Blue_Points();
                        break;
                     }
             case 'B': //generate only blue points.
                     {
                        Blue_Points.clear();
                        cout<<"Enter the number of blue points :";
                        cin>>blue_count;
                        cout<<"Enter the seed for the red points generation :";
                        cin>>blue_seed;
                        generate_blue_points();
                        display_Red_Points();
                        display_Blue_Points();
                        break;
                     }
            case 'K' : //set new increment factor
                     {
                        cout<<"Enter the new increment factor :";
                        cin>>k_incr;
                        cout<<"The new K : "<<k<<"and new increment factor : "<<k_incr<<endl;
                        break;
                     }
           case 'N' :
                     {
                        cout<<"Enter the new radius :";
                        cin>>rad;
                        cout<<"new radius is  : "<<rad<<endl;
                        break;
                     }
           case 'M' :
                     {
                        display_red_result();
                        break;
                     }
        }
}



