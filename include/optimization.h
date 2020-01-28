#ifndef _OPTIMIZATION_H
#define _OPTIMIZATION_H

#include "image.h"

float l(Image, Image, int px = 0, int py = 0, double theta = 0);
double argmin(Image, Image, int arg);
void argmin_txy(Image, Image, int &, int &, int number = 10);
void argmin_rtxy(Image, Image, int&, int&, double&, int number = 10);

float l_n(Image, Image, int px = 0, int py = 0);
int argmin_n(Image, Image, int arg);
void argmin_txy_n(Image, Image, int&, int&, int number = 5);
double improvement(Image , Image , int , int);
void improvement_xy(Image , Image , double&, double &, int number = 5);
double descent_x(Image , Image , double p0 = 10, double alpha = 0.1);
double descent_y(Image , Image , double p0 = 10, double alpha = 0.1);
void descent_xy(Image f, Image g, double& px, double& py, double p0x = 10, double p0y = 10, 
                double alphax = 0.1, double alphay = 0.1, int number = 5);



#endif