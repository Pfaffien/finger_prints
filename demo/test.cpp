#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "Image.h"

using namespace cv;
using namespace std;

int main()
{
    String s1( "../img/clean_finger_small.png" );

    Mat matrix(15, 15, CV_64FC1);
    Image img(matrix);
    // img(10,10) = 1.5;

    Image finger(s1);
    

    // std::cout << " Test element img[10,10] = " << img(10,10) << std::endl;
    // img.From255ToOne();
    // std::cout << " Test element img[10,10] = " << img(10,10) << std::endl;
    // img.OneTo255();
    // std::cout << " Test element img[10,10] = " << img(10,10) << std::endl;
    // finger.display();

    // Image sym = finger.sym_y();

    // sym.display();

    Image res = finger.rectangle(10,10,5,5,255);
    res.display();
    return 0;
}
