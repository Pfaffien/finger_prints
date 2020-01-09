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
   //  cv::String s1( "../img/lion.png" );
   //  Image test(s1);
   //
   //  test.display("Original", "Original");
   //
   //  // Filter definition
   //  int size = 15;
   //  cv::Mat_<float> filter(size, size);
   //  for (int i = 0; i < size; i++) {
   //      for (int j = 0; j < size; j++)
   //          filter(i, j) = 1. / size;
   //  }
   //  //filter /= size;
   //
   //  // Naive convolution
   //  cv::Mat_<float> conv = convolution(test(), filter);
   //  Image res_conv(conv);
   //  res_conv.display("Naive filtering", "Naive filtering");
   //
   // // First DFT convolution
   //  cv::Mat_<float> convDFT = convolutionDFT(test(), filter);
   //  Image res_convDFT(convDFT);
   //  res_convDFT.display("DFT filtering", "DFT filtering");
   //
   //  // Second DFT convolution
   //  cv::Mat_<float> convDFT2 = cDFT(test(), filter);
   //  Image res_convDFT2(convDFT2);
   //  res_convDFT2.display("DFT filtering 2", "DFT filtering 2");
   //
   //  // Difference between naive and first DFT convolution
   //  Image diff = res_conv - res_convDFT;
   //  diff.display("Difference", "Difference");


    // Main
    Image finger("../img/clean_finger.png");
    finger.display("initial", "initial");

    //identity filter
    int taille = 10;
    cv::Mat_<float> id(taille, taille, (int) 0);
    id(taille/2, taille/2) = 1;
    //blur filter
    cv::Mat_<float> blur(taille,taille);
    for (int i = 0; i < taille; i++){
        for (int j = 0; j < taille; j++){
            blur(i,j) = 1;
        }
    }
    blur = blur/(taille*taille);

    cv::Mat_<float> res = convolution_decrease(finger(), blur, finger().cols/2, finger().rows/2);
    Image res_img(res);
    res_img.display("decrease", "decrease");

    return 0;
}
