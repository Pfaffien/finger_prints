/**
 * \file test_starter3.cpp
 * \brief Test for sections starter3 and main3
 * \author Thomas.B Clara.B
 * \version 0.1
 * \date 01/12/20
 */

#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "starter3.h"
#include "Image.h"

using namespace std;


int main(){
    Image finger("../img/clean_finger.png");
    finger.display("initial", "initial");
    // int size = 10;
    // cv::Mat_<float> dec = convolution_complex(finger(), size, finger().cols/2, finger().rows/2);
    // Image dec_img(dec);
    // dec_img.display("energy decreasing", "energy decreasing");
    // dec_img.save("Energy decreasing");
    // // finger.display("initial2", "initial2");
    // cv::Mat_<float> blur = convolution_complex(finger(), size, finger().cols/2, finger().rows/2, false);
    // Image blur_img(blur);
    // blur_img.display("blurring", "blurring");
    // blur_img.save("Blurring");
    cv::Mat_<float> id(3,3, int(0));
    id(1,1) = 1;
    cv::Mat_<float> convDFT = convolutionDFT(finger(), id);
    Image dft(convDFT);
    dft.display("test", "test");

    Image diff = finger - dft;
    diff.display("diff", "diff");

    return 0;
}
