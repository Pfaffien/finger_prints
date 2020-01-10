#ifndef _STARTER3_H
#define _STARTER3_H

#include "Image.h"

cv::Mat_<float> convolution(cv::Mat_<float>, cv::Mat_<float>);
cv::Mat_<float> convolutionDFT(cv::Mat_<float>, cv::Mat_<float>);
cv::Mat_<float> cDFT(cv::Mat_<float> A, cv::Mat_<float> B);
cv::Mat_<float> kernel(cv::Mat_<float>, float, float);
cv::Mat_<float> kernel_blurring(cv::Mat_<float>, float, float);
double distance_max(cv::Mat_<float>, int, int);
cv::Mat_<float> convolution_decrease(cv::Mat_<float>, cv::Mat_<float>, int, int);
cv::Mat_<float> normalization(cv::Mat_<float>);
cv::Mat_<float> kernel_test(int, float, float);
//pourqoi pas essayer le flou de gauss
#endif
