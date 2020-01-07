#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "Image.h"

using namespace cv;

int main()
{
    String s1( "../img/clean_finger_small.png" );
    std::cout << s1 << std::endl;
    Image finger(s1);
    finger.display();
    return 0;
}
