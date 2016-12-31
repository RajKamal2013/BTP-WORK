#include<iostream>
#include<cstdio>
#include<vector>
#include<cstdlib>
#include<fstream>
using namespace std;

#define Red 0
#define Blue 1

struct setP
{
  double x;
  double y;
  bool cover;
  int group;
};


struct setV
{
   double x;
   double y;
};


struct setC
{
 int group;
 double x;
 double y;
 vector<setV>set;
};


extern int x_upper_bound;
extern int x_lower_bound;
extern int y_lower_bound;
extern int y_upper_bound;

extern int red_seed;
extern int blue_seed;
extern int cluster_seed;

extern int k;
extern int k_incr;
extern int k1;

extern int rad;
extern float tol;
extern int red_count;
extern int blue_count;
extern int ans;
extern int result;

extern float mapx;
extern float mapy;
extern int frameX;
extern int frameY;
extern int factorX;
extern int factorY;


//extern ofstream file;
//extern vector<setP> Red_Points;
//extern vector<setP> Blue_Points;
//extern vector<setC>cluster;
//vector<setC>actual_Cluster;

extern  int draw;
extern  int generate;
extern  int mainmenu;
extern  int set;
extern  int val;
extern  int main_window;
extern  int display;


extern ofstream file;
extern ofstream file1;
extern ofstream file2;
extern ofstream file3;//statiscal purpose
extern vector<setP> Red_Points;
extern vector<setP> Blue_Points;
extern vector<setC>cluster;
extern vector<setC>actual_Cluster;
extern vector<setC>Blue_cluster;
extern vector<setC>actual_Blue_Cluster;


void create_set(double x,double y,int choice );
void generate_points();
void generate_blue_points();
void generate_red_points();
void generate_cluster();

int feasiblity();
double distance(double x1,double y1,double x2,double y2);
void create_cluster();
void change_median();
void create_actual_cluster();
void create_Blue_cluster();
void create_actual_Blue_cluster();
void cover(double x,double y);
void complete_cluster();
int check();
int count_cover();

void display_points();
void display_point();
void display_cluster();
void display_actual_cluster();
void display_Blue_cluster();
void display_actual_Blue_cluster();
void display_Red_Points();
void display_Blue_Points();

void draw_Red_Points(int x, int y) ;
void draw_Blue_Points(int x, int y) ;
void mouse(int bin, int state , int x , int y) ;
void createMenu();
void menu(int value);



void handleKeypress(unsigned char key,int x, int y);

void refresh();
void init (void);

void option();

