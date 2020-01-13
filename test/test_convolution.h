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
    // Id filter
    // f
    cv::Mat_<float> f(3, 3, (int) 0);
    int counter = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            f(i, j) = counter;
            counter++;
        }
    }

    cv::Mat_<float> id(3, 3, (int) 0);
    id(1, 1) = 1;

    // Convolution
    cv::Mat_<float> conv_id = convolution(f, id);
    cv::normalize(f, f, 0, 1, cv::NORM_MINMAX);

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++)
      EXPECT_FLOAT_EQ(conv_id(i, j), f(i, j));
    }

    // Other filter
    //f
    cv::Mat_<float> f2(5, 5, 100);
    f2(2,2) = 150;

    cv::Mat_<float> k(3, 3, (int) 0);
    k(0,1) = -1;
    k(1,0) = -1;
    k(2,1) = -1;
    k(1,2) = -1;
    k(1,1) = 5;

    // Convolution
    cv::Mat_<float> conv_k = convolution(f2, k);
    cv::Mat_<float> res(5, 5, 100);
    res(2,1) = 50;
    res(1,2) = 50;
    res(2,2) = 350;
    res(2,3) = 50;
    res(3,2) = 50;
    cv::normalize(res, res, 0, 1, cv::NORM_MINMAX);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            EXPECT_NEAR(conv_k(i, j), res(i, j), 0.001);
    }
}


TEST(convolution, fft)
{
  // Id filter
  // f
  cv::Mat_<float> f(3, 3, (int) 0);
  int counter = 1;
  for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
          f(i, j) = counter;
          counter++;
      }
  }

  cv::Mat_<float> id(3, 3, (int) 0);
  id(1, 1) = 1;

  // Convolution
  cv::Mat_<float> conv_id = convolutionDFT(f, id);
  cv::normalize(f, f, 0, 1, cv::NORM_MINMAX);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++)
    EXPECT_FLOAT_EQ(conv_id(i, j), f(i, j));
  }

  // Other filter
  //f
  cv::Mat_<float> f2(5, 5, 100);
  f2(2,2) = 150;

  cv::Mat_<float> k(3, 3, (int) 0);
  k(0,1) = -1;
  k(1,0) = -1;
  k(2,1) = -1;
  k(1,2) = -1;
  k(1,1) = 5;

  // Convolution
  cv::Mat_<float> conv_k = convolutionDFT(f2, k);
  std::cout << conv_k << std::endl;
  cv::Mat_<float> res(5, 5, 100);
  res(2,1) = 50;
  res(1,2) = 50;
  res(2,2) = 350;
  res(2,3) = 50;
  res(3,2) = 50;
  cv::normalize(res, res, 0, 1, cv::NORM_MINMAX);
  std::cout << res << std::endl;

  for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++)
          EXPECT_NEAR(conv_k(i, j), res(i, j), 0.001);
  }
}

#endif  /* _TEST_CONVOLUTION_H_ */
