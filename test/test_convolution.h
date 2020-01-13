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
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            f(i, j) = counter;
            counter++;
        }
    }

    // Id filter
    id(1, 1) = 1;

    // Other filter
    k(0, 0) = - 1;
    k(0, 2) = - 1;
    k(2, 0) = 1;
    k(2, 2) = 1;
    k(0, 1) = 2;
    k(2, 1) = 2;

    // Convolution with Id
    cv::Mat_<float> conv_id = convolution(f, id);
    cv::normalize(f, f, 0, 1, cv::NORM_MINMAX);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            EXPECT_FLOAT_EQ(conv_id(i, j), f(i, j));
    }
    

    // Convolution with k
    cv::Mat_<float> conv_k = convolution(f, k);
    cv::Mat_<float> res(3, 3, (int) 0);
    res(0, 0) = - 13;
    res(2, 0) = 13;
    res(0, 1) = - 20;
    res(2, 1) = 20;
    res(0, 2) = - 17;
    res(2, 2) = 17;
    res(1, 0) = - 18;
    res(1, 2) = - 18;
    res(1, 1) = - 24;
    cv::normalize(res, res, 0, 1, cv::NORM_MINMAX);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            EXPECT_NEAR(conv_k(i, j), res(i, j), 0.001);
    }
}


TEST(convolution, fft)
{
    /* cv::Mat_<float> f(3, 3, (int) 0); */
    /* cv::Mat_<float> id(3, 3, (int) 0); */
    /* cv::Mat_<float> k(3, 3, (int) 0); */

    /* // f */
    /* int counter = 1; */
    /* for (int i = 0; i < 3; i++) { */
    /*     for (int j = 0; j < 3; j++) { */
    /*         f(i, j) = counter; */
    /*         counter++; */
    /*     } */
    /* } */
    
    /* // Id filter */
    /* id(1, 1) = 1; */

    /* // Other filter */
    /* /1* k(0, 0) = - (float) 1/10; *1/ */
    /* /1* k(0, 2) = - (float) 1/10; *1/ */
    /* /1* k(2, 0) = (float) 1/10; *1/ */
    /* /1* k(2, 2) = (float) 1/10; *1/ */
    /* /1* k(0, 1) = - (float) 2/10; *1/ */
    /* /1* k(2, 1) = (float) 2/10; *1/ */

    /* cv::Mat_<float> conv_id = convolutionDFT(f, id); */
    /* cv::normalize(f, f, 0, 1, cv::NORM_MINMAX); */

    /* for (int i = 0; i < 3; i++) { */
    /*     for (int j = 0; j < 3; j++) */
    /*         EXPECT_NEAR(conv_id(i, j), f(i, j), 0.001); */
    /* } */
    /* std::cout << conv_id << std::endl; */
    /* std::cout << f << std::endl; */
    
    // Convolution with k
    /* cv::Mat_<float> conv_k = convolutionDFT(f, k); */
    /* cv::Mat_<float> res(3, 3, (int) 0); */
    /* res(0, 0) = - (float) 13/100; */
    /* res(2, 0) = (float) 13/100; */
    /* res(0, 1) = - (float) 20/100; */
    /* res(2, 1) = (float) 20/100; */
    /* res(0, 2) = - (float) 17/100; */
    /* res(2, 2) = (float) 17/100; */
    /* res(1, 0) = - (float) 18/100; */
    /* res(1, 2) = - (float) 18/100; */
    /* res(1, 1) = - (float) 24/100; */

    /* for (int i = 0; i < 4; i++) { */
    /*     for (int j = 0; j < 5; j++) */
    /*         EXPECT_FLOAT_EQ(conv_k(i, j), res(i, j)); */
    /* } */
}

#endif  /* _TEST_CONVOLUTION_H_ */
