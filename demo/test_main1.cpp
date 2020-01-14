/**
 * \file main1.h
 * \brief Usefull functions to answer the part main 1
 * \author Thomas.B Clara.B
 * \version 0.1
 * \date 01/13/20
 */

#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>

#include "Image.h"
#include "main1.h"

using namespace std;

int main()
{
    Image finger("../img/clean_finger.png");
    finger.display("Finger", "Finger");

    int dist = 50;
    cv::Point center(7*finger().cols/16, 9*finger().rows/16);

    // //White outside a disk
    // cv::Point tmp((int) 0, (int) 0);
    // std::vector<cv::Point> coords = finger.outside_disk(center, dist);
    // Image res = finger.pressure_isotropic(center, coords, 0.02);
    Image ones(cv::Mat_<float>(finger().rows, finger().cols, 1));
    // res.display("White outside disk", "White outside disk");


    //Ellipse
    int a = 60;
    int b = 120;
    std::vector<cv::Point> ell = points_ellipse(center, a, b);
    Image test(finger().clone());

    for (std::vector<cv::Point>::iterator i = ell.begin(); i != ell.end(); i++)
        test((*i).y, (*i).x) = 1;

    // test.display("Ellipse", "Ellipse");

    /* Utilisation d'une fonction quelconque en dehors d'une certaine ellipse */
    Image test2(finger().clone());
    cv::Point tmp3((int) 0, (int) 0);
    /* std::vector<cv::Point> coord = test2.outside_ellipse(center, a, b); */
    std::vector<cv::Point> coord;
    for (int i = 0; i < test().rows; i++) {
        for (int j = 0; j < test().cols; j++)
            coord.push_back(cv::Point(j, i));
    }

    Image diff = ones - finger;
    for (std::vector<cv::Point>::iterator i = coord.begin(); i != coord.end(); i++) {
        /* test2((*i).y, (*i).x) *= (1-c_anisotropic((*i).x, (*i).y, center, 0.0002)); */
        /* test2((*i).y, (*i).x) = 1 - test2((*i).y, (*i).x); */
        cout << c_anisotropic((*i).x, (*i).y, center, 0.1, 0.01, 50) << endl;
        diff((*i).y, (*i).x) *= c_anisotropic((*i).x, (*i).y, center, 0.005, 0.001, 1);
    }

    diff = ones - diff;
    diff.display("Diff", "Diff");
    /* for (std::vector<cv::Point>::iterator i = outside.begin(); i != outside.end(); i++) { */
    /*     test2((*i).y, (*i).x) = 1 - test2((*i).y, (*i).x); */
    /* } */

    // test2.display("White outside ellipse", "White outside ellipse");

    return 0;
}
