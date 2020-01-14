#ifndef _MAIN1_H_
#define _MAIN1_H_


/**
 * \file main1.h
 * \brief Usefull functions to answer the part main 1
 * \author Thomas.B Clara.B
 * \version 0.1
 * \date 01/14/20
 */


#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>

/**
 * \fn float c_isotropic (float r, float param = 1)
 * \brief Definition of an isotropic function
 * \param r distance to the center
 * \param param parameter of the isotropic function
 * \return Result of the isotropic function
 */
float c_isotropic(float, float param = 1, int func = 0);

/**
 * \fn float c_anisotropic (int x, int y, cv::Point center, float param_x = 0.00035, float param_y = 0.000175, float param = 50)
 * \brief Definition of an anisotropic function
 * \param x, y coordinates of the point
 * \param center center of the image
 * \param param_x, param_y weigths of x and y
 * \param param parameter of the function
 * \return Result of the anisotropic function
 */
float c_anisotropic(int, int, cv::Point, float param_x = 0.00035, float param_y = 0.000175, float param = 50);

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
 * \size number of points in the vector
 * \endpoint if false the vector is of size size if not its size is size+1
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


#endif	/* _MAIN1_H_ */
