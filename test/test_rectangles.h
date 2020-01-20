#ifndef _TEST_RECTANGLES_
#define _TEST_RECTANGLES_

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#include "image.h"
#include "gtest/gtest.h"


TEST(rectangles, white)
{
    Image finger("../img/clean_finger.png");
    Image res = finger.rectangle(50, 100, 60, 100, 1);

    for (int i = 100; i < 160; i++) {
        for (int j = 50; j < 150; j++)
            EXPECT_FLOAT_EQ(res(i, j), 1);
    }
}


TEST(rectangles, black)
{
    Image finger("../img/clean_finger.png");
    Image res = finger.rectangle(180, 150, 70, 30, 0);

    for (int i = 150; i < 220; i++) {
        for (int j = 180; j < 210; j++)
            EXPECT_FLOAT_EQ(res(i, j), 0);
    }
}


#endif