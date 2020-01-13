#ifndef _TEST_CONVOLUTION_H_
#define _TEST_CONVOLUTION_H_

#include <iostream>
#include <cmath>
#include <opencv2/core/types.hpp>

#include "gtest/gtest.h"
#include "starter3.h"
#include "Image.h"


TEST(convolution, naive)
{
    cv::Mat_<float> f(3, 3, (int) 0);
    cv::Mat_<float> id(3, 3, (int) 0);
    cv::Mat_<float> k(3, 3, (int) 0);

    // f
    int counter = 1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            f(i, j) = (float) counter / 10;
            counter++;
        }
    }

    // Id filter
    id(1, 1) = 1;

    // Other filter
    k(0, 0) = - (float) 1/10;
    k(0, 2) = - (float) 1/10;
    k(2, 0) = (float) 1/10;
    k(2, 2) = (float) 1/10;
    k(0, 1) = - (float) 2/10;
    k(2, 1) = (float) 2/10;

    // Convolution with Id
    cv::Mat_<float> conv_id = convolution(f, id);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++)
            EXPECT_FLOAT_EQ(conv_id(i, j), f(i, j));
    }

    // Convolution with k
    cv::Mat_<float> conv_k = convolution(f, k);
    cv::Mat_<float> res(3, 3, (int) 0);
    res(0, 0) = - (float) 13/100;
    res(2, 0) = (float) 13/100;
    res(0, 1) = - (float) 20/100;
    res(2, 1) = (float) 20/100;
    res(0, 2) = - (float) 17/100;
    res(2, 2) = (float) 17/100;
    res(1, 0) = - (float) 18/100;
    res(1, 2) = - (float) 18/100;
    res(1, 1) = - (float) 24/100;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++)
            EXPECT_FLOAT_EQ(conv_k(i, j), res(i, j));
    }
}


TEST(convolution, fft)
{
    cv::Mat_<float> f(3, 3, (int) 0);
    cv::Mat_<float> id(3, 3, (int) 0);
    cv::Mat_<float> k(3, 3, (int) 0);

    // f
    int counter = 1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            f(i, j) = (float) counter / 10;;
            counter++;
        }
    }

    // Id filter
    id(1, 1) = 1;

    // Other filter
    k(0, 0) = - (float) 1/10;
    k(0, 2) = - (float) 1/10;
    k(2, 0) = (float) 1/10;
    k(2, 2) = (float) 1/10;
    k(0, 1) = - (float) 2/10;
    k(2, 1) = (float) 2/10;

    cv::Mat_<float> conv_id = convolutionDFT(f, id);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++)
            EXPECT_FLOAT_EQ(conv_id(i, j), f(i, j));
    }
    
    // Convolution with k
    cv::Mat_<float> conv_k = convolutionDFT(f, k);
    cv::Mat_<float> res(3, 3, (int) 0);
    res(0, 0) = - (float) 13/100;
    res(2, 0) = (float) 13/100;
    res(0, 1) = - (float) 20/100;
    res(2, 1) = (float) 20/100;
    res(0, 2) = - (float) 17/100;
    res(2, 2) = (float) 17/100;
    res(1, 0) = - (float) 18/100;
    res(1, 2) = - (float) 18/100;
    res(1, 1) = - (float) 24/100;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++)
            EXPECT_FLOAT_EQ(conv_k(i, j), res(i, j));
    }
}

#endif  /* _TEST_CONVOLUTION_H_ */
