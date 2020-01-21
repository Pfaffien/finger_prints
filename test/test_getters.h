#ifndef _TEST_GETTERS_
#define _TEST_GETTERS_

/**
 * \file test_getters.h
 * \brief Unit test for getters
 */


#include "image.h"
#include "gtest/gtest.h"


TEST(getter, pixel)
{
    cv::Mat_<float> mat(10, 15, 1);
    Image test(mat);
    EXPECT_THROW(std::cout << test(-1, 0), std::runtime_error);
    EXPECT_THROW(std::cout << test(0, -1), std::runtime_error);
    EXPECT_THROW(std::cout << test(10, 0), std::runtime_error);
    EXPECT_THROW(std::cout << test(0, 15), std::runtime_error);
}


TEST(getter, matrix)
{
    cv::String s = "../img/clean_finger.png";
    cv::Mat mat = cv::imread(s, 0);
    cv::Mat_<uchar> tmp = mat.clone();
    Image test(s);
    cv::Mat_<float> pixels = test();

    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++)
            EXPECT_EQ((int) (pixels(i, j)*255), tmp(i, j));
    }
}

#endif  /* _TEST_GETTERS_ */
