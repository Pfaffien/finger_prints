/**
 * \file test_starter3.cpp
 * \brief Test for sections starter1 : rectangle
 * \author Clara.B
 * \version 0.1
 * \date 01/12/20
 */


#include "image.h"


int main()
{
    cv::String s1( "../img/clean_finger.png" );
    Image finger(s1);

    finger.display("Clean finger");

    /* Image finger_float(finger); */

    Image res = finger.rectangle(180,150,70,30,0);
    res = res.rectangle(50, 100, 60, 100, 1);
    res.display("Black and white rectangles");

    res.save("rectangles");

    return 0;
}
