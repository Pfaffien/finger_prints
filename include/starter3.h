#ifndef _STARTER3_H
#define _STARTER3_H

#include "Image.h"

// le resultat n'est plus entre 0 et 1
cv::Mat_<float> convolution(cv::Mat_<float>, cv::Mat_<float>);
cv::Mat_<float> convolutionDFT(cv::Mat_<float>, cv::Mat_<float>);

#endif
