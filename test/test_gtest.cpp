#include "gtest/gtest.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#include "Image.h"

TEST(gtest, test1)
{
    cv::Mat_<float> mat(10, 15);
    Image test(mat);
    EXPECT_EQ(test().rows, 10);
    EXPECT_EQ(test().cols, 15);
}

int main(int argc,char *argv[]) {
 ::testing::InitGoogleTest(&argc,argv);
 return RUN_ALL_TESTS();
}
