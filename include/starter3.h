#ifndef _STARTER3_H
#define _STARTER3_H

/**
 * \file main1.h
 * \brief Usefull functions to answer the part starter 3
 * \author Thomas.B Clara.B
 * \version 0.1
 * \date 01/12/20
 */

#include "Image.h"

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
 * \fn cv::Mat_<float> kernel(cv::Mat_<float> K, float dist, float dist_max)
 * \brief Creates a filter that decreases the energy when the distance to the
    center increases
 * \param K initial kernel
    dist distance to the center
    dist_max maximum distance to the center
 * \return Matrix of the filter
 */
cv::Mat_<float> kernel(cv::Mat_<float>, float, float);


/**
 * \fn cv::Mat_<float> kernel_blurring(cv::Mat_<float> K, float dist, float dist_max)
 * \brief Creates a filter that blurs the image when the distance to the center
    increases
 * \param K initial kernel
    dist distance to the center
    dist_max maximum distance to the center
 * \return Matrix of the filter
 */
cv::Mat_<float> kernel_blurring(cv::Mat_<float>, float, float);


/**
 * \fn double distance_max(cv::Mat_<float> I, int x_c, int y_c)
 * \brief Computes the maximum distance to the center point
 * \param I matrix of the image
    x_c, y_c coordinates of the center
 * \return Maximum distance to the center
 */
double distance_max(cv::Mat_<float>, int, int);


/**
 * \fn cv::Mat_<float> convolution_decrease(cv::Mat_<float> F, cv::Mat_<float> K, int x_c, int y_c)
 * \brief Computes the convolution product of the matrix of the image and a kernel
    which depends of the distance to the center of each point
 * \param F matrix of the image
    K initial kernel
    x_c, y_c coordinates of the center
 * \return Result of the convolution
 */
cv::Mat_<float> convolution_decrease(cv::Mat_<float>, cv::Mat_<float>, int, int);


/**
 * \fn cv::Mat_<float> normalization(cv::Mat_<float> A)
 * \brief Normalizes the sum of the elements of the matrix
 * \param A matrix to normalize
 * \return Normalized matrix
 */
cv::Mat_<float> normalization(cv::Mat_<float>);


cv::Mat_<float> kernel_test(int, float, float);
//pourquoi pas essayer le flou de gauss
#endif
