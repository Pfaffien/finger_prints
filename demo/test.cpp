#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "Image.h"

using namespace cv;
using namespace std;

int main()
{
    String s1( "../img/lion.png" );
    
    Image img(s1);

    // std::cout << " Test element img[10,10] = " << img(10,10) << std::endl;
    // img.From255ToOne();
    // std::cout << " Test element img[10,10] = " << img(10,10) << std::endl;
    // img.OneTo255();
    // std::cout << " Test element img[10,10] = " << img(10,10) << std::endl;
    // finger.display();

    // Image sym = finger.sym_y();

    // sym.display();

    /* Image res = finger.rectangle(10,10,5,5,255); */
    img.display();
    Image img2 = img.sym_y();
    img2.display();
    return 0;
}
