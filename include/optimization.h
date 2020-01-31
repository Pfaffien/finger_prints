#ifndef _OPTIMIZATION_H
#define _OPTIMIZATION_H

#include "image.h"

/**
 * \fn l(Image f, Image g, int px = 0, int py = 0, double theta = 0)
 * \brief Computes the loss function
 * \param f, g two images
 * \param px, py, theta parameters of the warp function
 * \return value of the loss function
 */
float l(Image, Image, int px = 0, int py = 0, double theta = 0);


/**
 * \fn argmin(Image f, Image g, int arg)
 * \brief find the parameter that minimize the loss function
 * \param f image to approximate
 * \param g initial image
 * \param arg if 0 evaluate px, if 1 evaluate py, if 2 evaluate theta
 * \return parameter that minimize the loss function
 */
double argmin(Image, Image, int arg);


/**
 * \fn argmin_txy(Image f, Image, g int& px, int& py, int number = 5)
 * \brief find the arguments px and py that minimize the loss function
 * \param f image to approximate
 * \param g initial image
 * \param[out] px 
 * \param[out] py
 * \param number number of time that we want to iterate
 */
void argmin_txy(Image, Image, int &, int &, int number = 5);


/**
 * \fn argmin_rtxy(Image f, Image, g int& px, int& py, double &theta, int number = 10)
 * \brief find the arguments px, py and theta that minimize the loss function
 * \param f image to approximate
 * \param g initial image
 * \param[out] px 
 * \param[out] py
 * \param[out] theta
 * \param number number of time that we want to iterate
 * 
 */
void argmin_rtxy(Image, Image, int&, int&, double&, int number = 10);



double improvement(Image , Image , int , int);
void improvement_xy(Image , Image , double&, double &, int number = 5);

double descent(Image , Image , double p0 = 10, double alpha = 0.1, int arg = 0);
void descent_xy(Image f, Image g, double& px, double& py, double p0x, double p0y, 
                double alphax, double alphay, int number = 10);

/*
float l_n(Image, Image, int px = 0, int py = 0);
int argmin_n(Image, Image, int arg);
void argmin_txy_n(Image, Image, int&, int&, int number = 5);
*/

#endif