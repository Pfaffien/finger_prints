#ifndef _OPTIMIZATION_H
#define _OPTIMIZATION_H

#include "image.h"

float l_tx(Image, Image, int);
int argmin_tx(Image, Image);
float l_ty(Image, Image, int);
int argmin_ty(Image, Image);

float l_txy(Image, Image, int, int);
void argmin_txy(Image, Image, int &, int &, int number = 5);

float l_txn(Image, Image, int);
float l_tyn(Image, Image, int);
int argmin_txn(Image, Image);
int argmin_tyn(Image, Image);
void argmin_txyn(Image, Image, int &, int &, int number = 3);

#endif