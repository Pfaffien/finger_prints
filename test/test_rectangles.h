#ifndef _TEST_RECTANGLES_
#define _TEST_RECTANGLES_

/**
 * \file test_rectangles.h
 * \brief Unit test for rectangle
 */

#include "image.h"
#include "gtest/gtest.h"


TEST(rectangles, white)
{
    Image finger("../img/clean_finger.png");
    Image res = finger.Rectangle(50, 100, 60, 100, 1);

    for (int i = 100; i < 160; i++) {
        for (int j = 50; j < 150; j++)
            EXPECT_FLOAT_EQ(res(i, j), 1);
    }
}


TEST(rectangles, black)
{
    Image finger("../img/clean_finger.png");
    Image res = finger.Rectangle(180, 150, 70, 30, 0);

    for (int i = 150; i < 220; i++) {
        for (int j = 180; j < 210; j++)
            EXPECT_FLOAT_EQ(res(i, j), 0);
    }
}


#endif