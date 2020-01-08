#ifndef _STARTER3_H
#define _STARTER3_H

#include "Image.h"

cv::Mat_<float> convolution(cv::Mat_<float>, cv::Mat_<float>);
cv::Mat_<float> normalization(cv::Mat_<float>);
cv::Mat_<float> convolutionDFT(cv::Mat_<float>, cv::Mat_<float>);

#endif
