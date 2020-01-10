#ifndef _MAIN1_H_
#define _MAIN1_H_

#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>


float c_isotropic(float, float param = 1);
float c_anisotropic();
//param = 1: white by default
//iso = 0: anisotropic by default
std::vector<float> pressure(cv::Point center, std::vector<cv::Point> coords, float param = 1, bool iso = 0);

#endif	/* _MAIN1_H_ */
