#ifndef _TEST_DIFFERENCE_
#define _TEST_DIFFERENCE_

/**
 * \file test_difference.h
 * \brief Unit test for difference
 */


#include "image.h"
#include "gtest/gtest.h"


TEST(overloading, swap_intensity)
{
    Image img(cv::Mat_<float>(10, 15, 0.3));
    Image test(cv::Mat_<float>(10, 15, 0.7));

    Image swapped = -img;

    EXPECT_TRUE(swapped == test);
}


TEST(overloading, subtraction)
{
    Image img(cv::Mat_<float>(10, 15, 0.5));
    Image img2(cv::Mat_<float>(10, 15, 0.2));
    Image diff = img - img2;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 15; j++)
            EXPECT_FLOAT_EQ(diff(i, j), 0.3);
    }
}

#endif  /* _TEST_DIFFERENCE_ */
