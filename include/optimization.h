#ifndef _OPTIMIZATION_H
#define _OPTIMIZATION_H

/**
 * \file optimization.h
 * \brief Definition of the functions used in optimization method
 * \author Clara B
 * \version 0.1
 * \date 01/20/20
 */

#include "image.h"

/**
 * \fn l(Image f, Image g, int px = 0, int py = 0, double theta = 0)
 * \brief Compute the loss function
 * \param f is the image to approximate
 * \param g is the initial image
 * \param px, py, theta are the parameters of the warp function
 * \return Value of the loss function
 */
float l(Image, Image, int px = 0, int py = 0, double theta = 0);


/**
 * \fn argmin(Image f, Image g, int arg)
 * \brief Find the parameter that minimize the loss function
 * \param f is the image to approximate
 * \param g is the initial image
 * \param arg if 0 evaluate px, if 1 evaluate py, if 2 evaluate theta
 * \return Parameter that minimize the loss function
 */
double argmin(Image, Image, int arg);


/**
 * \fn argmin_txy(Image f, Image, g int& px, int& py, int number = 5)
 * \brief Find the arguments px and py that minimize the loss function
 * \param f is the image to approximate
 * \param g is the initial image
 * \param[out] px, oy are the parameters that minimize the loss function
 * \param number is the number of time that we want to iterate
 */
void argmin_txy(Image, Image, int &, int &, int number = 5);


/**
 * \fn argmin_rtxy(Image f, Image, g int& px, int& py, double &theta, int number = 10)
 * \brief Find the arguments px, py and theta that minimize the loss function
 * \param f is the image to approximate
 * \param g is the initial image
 * \param[out] px, py, theta are the parameters that minimize the loss function
 * \param number is the number of time that we want to iterate
 * 
 */
void argmin_rtxy(Image, Image, int&, int&, double&, int number = 10);


/**
 * \fn improvement(Image f, Image g, int arg)
 * \brief Find the parameter that minimize the loss function
 * \param f is the image to approximate
 * \param g is the initial image
 * \param arg if 0 evaluate px, if 1 evaluate py, if 2 evaluate theta
 * \return Parameter that minimize the loss function (double value)
 */
double improvement(Image , Image , int , int);


/**
 * \fn improvement_xy(Image f, Image, g int& px, int& py, int number = 10)
 * \brief Find the arguments px and py that minimize the loss function
 * \param f is the image to approximate
 * \param g is the initial image
 * \param[out] px, py are the parameters that minimize the loss function (double value)
 * \param number is the number of time that we want to iterate
 */
void improvement_xy(Image , Image , double&, double &, int number = 5);

/**
 * \fn descent(Image f, Image g, double p0, double alpha, int arg)
 * \brief Find the argument px or py that minimize the loss function using the coordinate descent
 * \param f is the image to approximate
 * \param g is the initial image
 * \param p0 is the initial value of the argmin
 * \param alpha is the pourcentage used in the coordinate descent
 * \param arg if 0 the function evaluates px else py
 * \return Value that minimize the loss function
 */ 
double descent(Image , Image , double, double, int);

/**
 * \fn descent_xy(Image f, Image, g double& px, double& py, double p0x, double p0y, double alphax, double alpha y, int number = 10)
 * \brief Find the arguments px and py that minimize the loss function using the coordinate descent
 * \param f is the image to approximate
 * \param g is the initial image
 * \param[out] px, py are the parameters that minimize the loss function
 * \param p0x is the initial value of px
 * \param p0y is the initial value of py
 * \param alphax is the pourcentage for px
 * \param alphay is the pourcentage for py
 * \param number is the number of time that we want to iterate
 */
void descent_xy(Image, Image, double&, double&, double, double, double, double, int number = 10);

#endif