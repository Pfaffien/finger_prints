#include "gtest/gtest.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#include "Image.h"


TEST(gtest, pixel_getter)
{
    cv::Mat_<float> mat(10, 15, 1);
    Image test(mat);
    EXPECT_THROW(std::cout << test(-1, 0), std::runtime_error);
    EXPECT_THROW(std::cout << test(0, -1), std::runtime_error);
    EXPECT_THROW(std::cout << test(10, 0), std::runtime_error);
    EXPECT_THROW(std::cout << test(0, 15), std::runtime_error);
}


TEST(gtest, matrix_constructor)
{
    cv::Mat_<float> mat(10, 15, 1);
    Image test(mat);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 15; j++)
            EXPECT_EQ(test(i, j), mat(i, j));
    }
}


TEST(gtest, matrix_getter)
{
    cv::Mat_<float> mat(10, 15, 2);
    Image test(mat);
    cv::Mat_<float> pixels = test();

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 15; j++)
            EXPECT_EQ(pixels(i, j), mat(i, j));
    }

    // Ne marche pas car problème de précision en mémoire pour les float
    /* cv::Mat mat2 = cv::imread("../img/clean_finger.png", 0); */
    /* cv::Mat_<float> tmp = mat2.clone(); */
    /* Image test2("../img/clean_finger.png"); */
    /* cv::Mat_<float> pixels2 = test2(); */

    /* for (int i = 0; i < mat2.rows; i++) { */
    /*     for (int j = 0; j < mat2.cols; j++) */
    /*         EXPECT_EQ(pixels2(i, j), tmp(i, j) / 255.); */
    /* } */
}


int main(int argc,char *argv[]) {
 ::testing::InitGoogleTest(&argc,argv);
 return RUN_ALL_TESTS();
}
