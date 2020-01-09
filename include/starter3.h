#ifndef _STARTER3_H
#define _STARTER3_H

#include "Image.h"

cv::Mat_<float> convolution(cv::Mat_<float>, cv::Mat_<float>);
cv::Mat_<float> convolutionDFT(cv::Mat_<float>, cv::Mat_<float>);
cv::Mat_<float> cDFT(cv::Mat_<float> A, cv::Mat_<float> B);

#endif
