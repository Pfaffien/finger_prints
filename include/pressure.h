#ifndef _PRESSURE_H_
#define _PRESSURE_H_

/**
 * \file pressure.h
 * \brief Useful functions to answer the part main 1
 * \author Thomas.B Clara.B
 * \version 0.1
 * \date 01/14/20
 */


#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <cmath>

#define PI 3.14159265359


void cartesian_to_polar(cv::Point, cv::Point, float &, float &);


/**
 * \fn float c_isotropic (float r, float param = 1, int func = 0)
 * \brief Definition of an isotropic function
 * The function contains 3 functions (selected function, exponential and inverse)
 * \param r distance to the center
 * \param param parameter of the isotropic function
 * \param func parameter which decide which function to use (0 = selected function, 1 = exponential function, 2 = inverse function)
 * \return Result of the isotropic function
 */
float c_isotropic(float, float param = 1, int func = 0);


/**
 * \fn float c_anisotropic (int x, int y, cv::Point center, float param_x = 0.00035, float param_y = 0.000175, float param = 50)
 * \brief Definition of an anisotropic function
 * The anisotropic function corresponds to the isotropic selected function adapted to ba anisotropic
 * \param x, y coordinates of the point
 * \param center center of the image
 * \param param_x, param_y weigths of x and y
 * \param param parameter of the function
 * \return Result of the anisotropic function
 */
float c_anisotropic(int, int, cv::Point, float param_x = 0.00035, float param_y = 0.000175, float param = 50);


float c_anisotropic_polar(float, float, cv::Point, float param_x = 0.00035, float param_y = 0.000175, float param = 50);


/**
 * \fn std::vector<float> coeffs(cv::Point center, std::vector<cv::Point> coords, float param_x = 0.00035, float param_y = 0.000175, float param = 50, bool iso = false)
 * \brief Computes the new values of the pixels of coefficients coeffs
 * \param center center of the image
 * \param coords points to modify the value
 * \param param_x, param_y weigths of x and y
 * \param param parameter of the function
 * \param iso if true use an isotropic function if false an anisotropic function
 * \return Returns the list of modified coefficients
 */
std::vector<float> coeffs(cv::Point center, std::vector<cv::Point> coords, float param_x = 0.00035, float param_y = 0.000175, float param = 50, bool iso = false);


/**
 * \fn std::vector<float> linspace(float a, float b, int size, bool endpoint = false)
 * \brief Creates a vector of floats between a and b
 * \param a value of the first point
 * \param b value of the last point
 * \param size number of points in the vector
 * \param endpoint if false the vector is of size size if not its size is size+1
 * \return Returns the vector of points
*/
std::vector<float> linspace(float, float, int, bool endpoint = false);


/**
 * \fn std::vector<cv::Point> points_ellipse(cv::Point center, float a, float b)
 * \brief Calculates the points that are in the border of the ellipse of center center and of semi axes a and b
 * \param center center of the ellipse
 * \param a,b semi axes of the ellipse
 * \return Returns the vector of Points
*/
std::vector<cv::Point> points_ellipse(cv::Point, float, float);


#endif	/* _PRESSURE_H_ */