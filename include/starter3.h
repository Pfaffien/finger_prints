#ifndef _STARTER3_H
#define _STARTER3_H

/**
 * \file starter3.h
 * \brief Usefull functions to answer the part starter 3 and main 3
 * \author Thomas.B Clara.B
 * \version 0.1
 * \date 01/12/20
 */

#include "image.h"

/**
 * \fn cv::Mat_<float> convolution(cv::Mat_<float> A, cv::Mat_<float> B)
 * \brief Performs the convolution of the two matrices using the naive method
 * \param A, B matrices to convolve
 * \return Result of the convolution
 */
cv::Mat_<float> convolution(cv::Mat_<float>, cv::Mat_<float>);


/**
 * \fn cv::Mat_<float> convolutionDFT(cv::Mat_<float> A, cv::Mat_<float> B)
 * \brief Performs the convolution of the two matrices using the DFT method
 * \param A, B matrices to convolve
 * \return Result of the convolution
 */
cv::Mat_<float> convolutionDFT(cv::Mat_<float>, cv::Mat_<float>);


/**
 * \fn cv::Mat_<float> kernel_decrease(int size, float dist, float dist_max)
 * \brief Creates a filter that decreases the energy when the distance to the
    center increases
 * \param size size of the kernel
 * \param dist distance to the center
 * \param dist_max maximum distance to the center
 * \return Matrix of the filter
 */
cv::Mat_<float> kernel_decrease(int, float, float);


/**
 * \fn cv::Mat_<float> kernel_blur(int size, float dist, float dist_max)
 * \brief Creates a filter that blurs the image when the distance to the center
    increases
 * \param size size of the kernel
 * \param dist distance to the center
 * \param dist_max maximum distance to the center
 * \return Matrix of the filter
 */
cv::Mat_<float> kernel_blur(int , float, float);


/**
 * \fn float distance_max(int size, int x_c, int y_c)
 * \brief Computes the maximum distance to the center point
 * \param size size of the filter
 * \param x_c, y_c coordinates of the center
 * \return Maximum distance to the center
 */
float distance_max(cv::Mat_<float>, int, int);


/**
 * \fn cv::Mat_<float> convolution_complex(cv::Mat_<float> F, int size, int x_c, int y_c, bool decrease)
 * \brief Computes the convolution product of the matrix of the image and a kernel
    which depends of the distance to the center of each point
 * \param F matrix of the image
 * \param size size of the kernel
 * \param x_c, y_c coordinates of the center
 * \param decrease perform a decreasing of the energy is true a blurring if false
 * \return Result of the convolution
 */
cv::Mat_<float> convolution_complex(cv::Mat_<float>, int, int, int, bool decrease = true);


/**
 * \fn cv::Mat_<float> normalization(cv::Mat_<float> A)
 * \brief Normalizes the sum of the elements of the matrix
 * \param A matrix to normalize
 * \return Normalized matrix
 */
cv::Mat_<float> normalization(cv::Mat_<float>);

/**
 * \fn cv::Mat_<float> kernel_test(int size, float dist, float dist_max)
 * \brief Creates a filter that blurs the image when the distance to the center
    increases : other method
 * \param size size of the kernel
 * \param dist distance to the center
 * \param dist_max maximum distance to the center
 * \return Matrix of the filter
 */
cv::Mat_<float> kernel_test(int, float, float);
//pourquoi pas essayer le flou de gauss

#endif
