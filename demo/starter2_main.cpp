#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "Starter2.h"


int main()
{
    cv::String s1( "../img/clean_finger.png" );
    Image finger(s1);

    finger.display("Clean finger", "Clean finger");

    Image rotate = finger.rotate(45.);
    std::cerr << "rotation done \n";
    rotate.display("Rotated finger", "Rotated finger");

    return 0;
}
