#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
#include "Image.h"


int main()
{
    cv::String s1( "../img/clean_finger.png" );
    Image finger(s1);

    finger.display("Clean finger", "Clean finger");

    /* Image finger_float(finger); */

    Image res = finger.rectangle(10,10,50,10,0);
    res = res.rectangle(50, 100, 20, 30, 1);
    res.display("Black and white rectangles", "Black and white rectangles");

    res.save("rectangles");
    Image saved("../img/saved/rectangles.png");
    saved.display("Saved image", "Saved image");

    return 0;
}
