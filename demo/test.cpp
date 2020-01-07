#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "Image.h"

using namespace cv;
using namespace std;

int main()
{
    String s1( "../img/txy_small_finger.png" );
    
    Image img(s1);

    Image finger(s1);

    img.display();
    Image img2 = img.sym_y();
    img2.display();

    finger.display();
    Image res = finger.rectangle(10,10,50,10,0);
    res = res.rectangle(50, 100, 20, 30, 255);
    res.display();
    finger.display();

    return 0;
}
