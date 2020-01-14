/**
 * \file main1.h
 * \brief Usefull functions to answer the part main 1
 * \author Thomas.B Clara.B
 * \version 0.1
 * \date 01/14/20
 */

#include "Image.h"
#include "main1.h"

using namespace std;

int main()
{
    Image finger("../img/clean_finger.png");
    finger.display("Finger", "Finger");

    cv::Point center(7*finger().cols/16, 9*finger().rows/16);

    vector<cv::Point> points = finger.matrix2vector();
    Image res = finger.pressure(center, points);

    res.display("res", "res");

    return 0;
}
