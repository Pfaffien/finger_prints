#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>

#include "Image.h"
#include "main1.h"

int main()
{
    Image finger("../img/clean_finger.png");
    finger.display("Finger", "Finger");

    int dist = 50;
    cv::Point center(finger().cols/2, finger().rows/2);

    //White outside a disk
    cv::Point tmp((int) 0, (int) 0);
    std::vector<cv::Point> coords = finger.outside_disk(center, dist);
    Image res = finger.pressure_isotropic(center, coords, 0.02);
    res.display("White outside disk", "White outside disk");


    //Ellipse
    int a = 40;
    int b = 80;
    std::vector<cv::Point> ell = points_ellipse(center, a, b);
    Image test(finger().clone());
    
    for (std::vector<cv::Point>::iterator i = ell.begin(); i != ell.end(); i++)
        test((*i).y, (*i).x) = 1;

    test.display("Ellipse", "Ellipse");
    
    /* Utilisation d'une fonction quelconque en dehors d'une certaine ellipse */
    Image test2(finger().clone());
    cv::Point tmp3((int) 0, (int) 0);
    std::vector<cv::Point> coord = test2.outside_ellipse(center, a, b);

    for (std::vector<cv::Point>::iterator i = coord.begin(); i != coord.end(); i++)
        test2((*i).y, (*i).x) = c_anisotropic((*i).x, (*i).y, center, 0.002);
    
    test2.display("White outside ellipse", "White outside ellipse");

    return 0;
}
