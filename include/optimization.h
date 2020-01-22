#ifndef _OPTIMIZATION_H
#define _OPTIMIZATION_H

#include "image.h"

float l_tx(Image, Image, int);
int argmin_tx(Image, Image);

float l_txy(Image, Image, int, int);
void argmin_txy(Image, Image, int &, int &);


#endif