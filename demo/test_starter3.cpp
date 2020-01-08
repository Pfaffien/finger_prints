#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "starter3.h"
#include "Image.h"

using namespace std;

#include "opencv2/highgui/highgui.hpp"
#include <iostream>
 
 
int main()
{
    // Read image from file
    // Make sure that the image is in grayscale
    cv::Mat img = cv::imread("../img/lion.png",0);
     
    cv::Mat planes[] = {cv::Mat_<float>(img), cv::Mat::zeros(img.size(), CV_32F)};
    cv::Mat complexI;    //Complex plane to contain the DFT coefficients {[0]-Real,[1]-Img}
    cv::merge(planes, 2, complexI);
    cv::dft(complexI, complexI);  // Applying DFT
 
    // Reconstructing original imae from the DFT coefficients
    cv::Mat invDFT, invDFTcvt;
    cv::idft(complexI, invDFT, cv::DFT_SCALE | cv::DFT_REAL_OUTPUT );
    // Applying IDFT
    invDFT.convertTo(invDFTcvt, CV_8U); 
    //cv::imshow("Output", invDFTcvt);
 
    //show the image
    //cv::imshow("Original Image", img);
     
    // Wait until user press some key
    //cv::waitKey(0);

    // TEST DE LA CONVOLUTION
    int taille = 15;
    cv::Mat_<float> blur(taille,taille);

    for (int i = 0; i < taille; i++){
        for (int j = 0; j < taille; j++){
            blur(i,j) = 1;
        }
    }

    blur = blur/taille;
    
    cv::Mat_<float> img2 = img.clone();
    cv::Mat_<float> pix = convolveDFT(img2, blur);
    /* std::cout << pix << std::endl; */
    Image img3(pix);
    img3.display("Not working", "Not working");

    cv::Mat_<float> pix2 = convolution(img2, blur);
    Image img4(pix2);
    img4.display("Working", "Working");

    Image diff = img3 - img4;
    diff.display("Diff", "Diff");

    return 0;
}

/* int main(){ */
/*   cv::String s1( "../img/lion.png" ); */
/*   Image finger(s1); */

/*   finger.display("Clean finger", "Clean finger"); */

/*   // cv::Mat_<float> kernel(3,3); */
/*   // for (int i = 0; i < 3; i++){ */
/*   //   for (int j = 0; j < 3; j++){ */
/*   //     kernel(i,j) = -1; */
/*   //   } */
/*   // } */
/*   // kernel(1,1) = 8; */
/*   // */
/*   // cv::Mat_<float> res = convolution(finger(), kernel); */
/*   // Image res_img(res); */
/*   // */
/*   // res_img.display("res convol", "res convol"); */
  /* int taille = 3; */
  /* cv::Mat_<float> blur(taille,taille); */

  /* for (int i = 0; i < taille; i++){ */
  /*   for (int j = 0; j < taille; j++){ */
  /*     blur(i,j) = 1; */
  /*   } */
  /* } */

  /* blur = blur/taille; */
/*   cv::Mat_<float> blurred = convolution(finger(), blur); */
/*   // cout << blurred << endl; */
/*   Image res_blur(blurred); */
/*   res_blur.display("blur", "blur"); */
/*   // Image diff = finger - res_blur; */
/*   // diff.display("Diff", "Diff"); */

/*   return 0; */
/* } */
