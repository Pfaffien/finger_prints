#ifndef _OPTIMIZATION_H
#define _OPTIMIZATION_H

#include "image.h"

float l(Image, Image, int px = 0, int py = 0);
int argmin(Image, Image, int arg);
void argmin_txy(Image, Image, int &, int &, int number = 10);

float l_n(Image, Image, int px = 0, int py = 0);
int argmin_n(Image, Image, int arg);
void argmin_txy_n(Image, Image, int&, int&, int number = 5);

#endif