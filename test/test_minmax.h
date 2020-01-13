#ifndef _TEST_MINMAX_
#define _TEST_MINMAX_

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#include "Image.h"
#include "gtest/gtest.h"


TEST(minmax, min)
{
    cv::Mat_<float> mat(5, 5, 0.5);
    Image img(mat);

    img(1, 3) = 0.3;

    EXPECT_FLOAT_EQ(img.min(), 0.3);
}


TEST(minmax, max)
{
    cv::Mat_<float> mat(5, 5, 0.5);
    Image img(mat);

    img(4, 2) = 0.9;

    EXPECT_FLOAT_EQ(img.max(), 0.9);
}

#endif /* _TEST_MINMAX_ */
