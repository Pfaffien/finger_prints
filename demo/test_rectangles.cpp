/**
 * \file test_starter3.cpp
 * \brief Test for sections starter1 : rectangle
 * \author Clara.B
 * \version 0.1
 * \date 01/12/20
 */


#include "Image.h"


int main()
{
    cv::String s1( "../img/clean_finger.png" );
    Image finger(s1);

    finger.display("Clean finger");

    /* Image finger_float(finger); */

    Image res = finger.rectangle(10,10,50,10,0);
    res = res.rectangle(50, 100, 20, 30, 1);
    res.display("Black and white rectangles");

    res.save("rectangles");

    return 0;
}
