#ifndef _MAIN1_H_
#define _MAIN1_H_

#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>


float c(float, float param = 1);
std::vector<float> pressure(cv::Point center, std::vector<cv::Point> coords, float param);

#endif	/* _MAIN1_H_ */
