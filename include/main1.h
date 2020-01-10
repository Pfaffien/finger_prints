#ifndef _MAIN1_H_
#define _MAIN1_H_

#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>


float c_isotropic(float, float param = 1);
float c_anisotropic(int, int, cv::Point, float);

//param = 1: white by default
//iso = 0: anisotropic by default
std::vector<float> pressure(cv::Point center, std::vector<cv::Point> coords, float param = 1, bool iso = 0);

// N points par defaut, N+1 si endpoint = true
std::vector<float> linspace(float, float, int, bool endpoint = false);
std::vector<cv::Point> points_ellipse(cv::Point, float, float);


#endif	/* _MAIN1_H_ */
