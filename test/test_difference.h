#ifndef _TEST_DIFFERENCE_
#define _TEST_DIFFERENCE_

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#include "Image.h"
#include "gtest/gtest.h"


TEST(difference, overloading)
{
    cv::Mat_<float> mat(10, 15, 0.5);
    cv::Mat_<float> mat2(10, 15, 0.2);
    Image img(mat);
    Image img2(mat2);
    Image diff = img - img2;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 15; j++)
            EXPECT_FLOAT_EQ(diff(i, j), 0.3);
    }
}

#endif  /* _TEST_DIFFERENCE_ */
