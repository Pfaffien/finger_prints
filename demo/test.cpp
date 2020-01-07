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
    
    Mat matrix(15, 15, CV_64FC1);
    Image img(matrix);
    img(10,10) = 1.5;

    Image finger(s1);

    std::cout << " Test element img[10,10] = " << img(10,10) << std::endl;
    img.From255ToOne();
    std::cout << " Test element img[10,10] = " << img(10,10) << std::endl;
    img.OneTo255();
    std::cout << " Test element img[10,10] = " << img(10,10) << std::endl;
    finger.display();
    
    Image sym = finger.sym_y();

    sym.display();

    return 0;
}
