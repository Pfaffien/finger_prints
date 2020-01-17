#ifndef _TEST_EQUALITY_H_
#define _TEST_EQUALITY_H_

#include "image.h"
#include "gtest/gtest.h"


TEST(overloading, equality)
{
    int size = 15;
    cv::Mat_<float> test(size, size, 0.7);
    test(size/2, size/2) = 0.5;
    Image test_img(test);

    EXPECT_TRUE(test_img == test_img);
    EXPECT_FALSE(test_img == Image(cv::Mat_<float>(size, size, 0.3)));
    EXPECT_THROW(test_img == Image(cv::Mat_<float>(size+1, size)), std::runtime_error);
    EXPECT_THROW(test_img == Image(cv::Mat_<float>(size, size-1)), std::runtime_error);
}


#endif  /* _TEST_EQUALITY_H_ */