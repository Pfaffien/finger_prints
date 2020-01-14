#ifndef _MAIN1_H_
#define _MAIN1_H_


/**
 * \file main1.h
 * \brief Usefull functions to answer the part main 1
 * \author Thomas.B Clara.B
 * \version 0.1
 * \date 01/12/20
 */


#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>

/**
 * \fn float c_isotropic (float, float param = 1)
 * \brief Definition of an isotropic function
 * \param
 * \return Result of the isotropic function
 */
float c_isotropic(float, float param = 1);

/**
 * \fn float c_anisotropic (int, int, cv::Point, float)
 * \brief Definition of an anisotropic function
 * \param
 * \return Result of the anisotropic function
 */
float c_anisotropic(int, int, cv::Point, float param_x = 0.00035, float param_y = 0.00035/2, float param = 50);

//param = 1: white by default
//iso = 0: anisotropic by default
std::vector<float> pressure(cv::Point center, std::vector<cv::Point> coords, float param = 1, bool iso = 0);

// N points par defaut, N+1 si endpoint = true
std::vector<float> linspace(float, float, int, bool endpoint = false);
std::vector<cv::Point> points_ellipse(cv::Point, float, float);


#endif	/* _MAIN1_H_ */
