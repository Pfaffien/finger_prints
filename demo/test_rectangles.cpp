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

    Image_float finger_float(finger);

    Image_float res_float = finger_float.rectangle(10,10,50,10,0);
    res_float = res_float.rectangle(50, 100, 20, 30, 255);
    Image res(res_float);
    res.display("Black and white rectangles", "Black and white rectangles");

    res.save("rectangles");
    Image saved("../img/rectangles.png");
    saved.display("Saved image", "Saved image");

    return 0;
}
