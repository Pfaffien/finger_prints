#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "starter3.h"
#include "Image.h"


int main()
{
    cv::String s1( "../img/lion.png" );
    Image test(s1);

    test.display("Original", "Original");

    // Filter definition
    int size = 15;
    cv::Mat_<float> filter(size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            filter(i, j) = 1. / size;
    }
    //filter /= size;

    // Naive convolution
    cv::Mat_<float> conv = convolution(test(), filter);
    Image res_conv(conv);
    res_conv.display("Naive filtering", "Naive filtering");

   // First DFT convolution
    cv::Mat_<float> convDFT = convolutionDFT(test(), filter);
    Image res_convDFT(convDFT);
    res_convDFT.display("DFT filtering", "DFT filtering");

    // Second DFT convolution
    cv::Mat_<float> convDFT2 = cDFT(test(), filter);
    Image res_convDFT2(convDFT2);
    res_convDFT2.display("DFT filtering 2", "DFT filtering 2");

    // Difference between naive and first DFT convolution
    Image diff = res_conv - res_convDFT;
    diff.display("Difference", "Difference");
}
