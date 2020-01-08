#ifndef _STARTER3_H
#define _STARTER3_H

#include "Image.h"

cv::Mat_<float> convolution(cv::Mat_<float>, cv::Mat_<float>);
cv::Mat_<float> convolutionDFT(cv::Mat_<float>, cv::Mat_<float>);
cv::Mat_<float> convolveDFT(cv::Mat_<float> f, cv::Mat_<float> k);

#endif
