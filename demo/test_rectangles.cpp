#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "Image.h"


int main()
{
    cv::String s1( "../img/clean_finger.png" );
    Image finger(s1);

    finger.display("Clean finger", "Clean finger");
    Image res = finger.rectangle(10,10,50,10,0);
    res = res.rectangle(50, 100, 20, 30, 255);
    res.display("Black and white rectangles", "Black and white rectangles");

    return 0;
}
