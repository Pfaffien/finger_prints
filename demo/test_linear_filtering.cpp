/**
 * \file test_linear_filtering.cpp
 * \brief Test of the implementation of linear filtering
 * \author Thomas.B Clara.B
 * \version 0.1
 * \date 01/12/20
 */

#include "linear_filtering.h"
#include "image.h"

using namespace std;



/**
 * \fn int main()
 * \brief Test of the convolution functions
 * The function tests and compares the naive and DFT convolution, 
 * the energy decreasing convolution and the blurring decreasing function
 */

int main(){
    //Image used for the test
    Image finger("../img/clean_finger.png");
    finger.display("initial");

    //Identity filter    
    //initialization of the filter
    int size = 3;
    cv::Mat_<float> id(size, size, int(0));
    id(size/2, size/2) = 1;

    //processing convolutions
    cv::Mat_<float> conv_id = convolution(finger(), id);
    Image classic_id(conv_id);
    classic_id.display("classic id");
    classic_id.save("classic_id");

    cv::Mat_<float> convDFT_id = convolutionDFT(finger(), id);
    Image dft_id(convDFT_id);
    dft_id.display("DFT id");
    dft_id.save("DFT_id");

    //comparison of the results
    Image diff_id = classic_id - dft_id;
    diff_id.display("diff id");
    diff_id.save("diff_id");
    float err_id = classic_id.error(dft_id, 0.001);
    cout << "Error between the convolutions for identity : " << err_id*100 << "%" << endl;

    //Clear the windows
    cv::destroyAllWindows();


    //Blurring
    finger.display("initial");

    //initialization of the blurring filter
    size = 5;
    cv::Mat_<float> blur(size, size, 1);
    blur /= pow(size, 2);

    //processing convolutions
    cv::Mat_<float> conv_blur = convolution(finger(), blur);
    Image classic_blur(conv_blur);
    classic_blur.display("classic blur");
    classic_blur.save("classic_blur");

    cv::Mat_<float> convDFT_blur = convolutionDFT(finger(), blur);
    Image dft_blur(convDFT_blur);
    dft_blur.display("DFT blur");
    dft_blur.save("DFT_blur");

    //comparison of the result
    Image diff_blur = classic_blur - dft_blur;
    cv::normalize(diff_blur(), diff_blur(), 0, 1, cv::NORM_MINMAX);
    diff_blur.display("diff blur");
    diff_blur.save("diff_blur");
    float err_blur = classic_blur.error(dft_blur, 0.001);
    cout << "Error between the convolutions for blur : " << err_blur*100 << "%" << endl;

    //Using the method
    Image conv_method = finger*blur;
    conv_method.display("Convolution method of Image");

    //Clear the windows
    cv::destroyAllWindows();


    //Energy decreasing
    finger.display("initial");
    size = 10;

    cv::Point center = finger.center();
    cv::Mat_<float> dec = convolution_complex(finger(), size, center.x, center.y);
    Image dec_img(dec);
    dec_img.display("energy decreasing");
    dec_img.save("Energy_decreasing");


    //Blurring decreasing
    size = 21;
    cv::Mat_<float> convblur = convolution_complex(finger(), size,
                                                   center.x,
                                                   center.y, false);
    Image blur_img(convblur);
    blur_img.display("blurring");
    blur_img.save("Blurring");


    //Improvements
    std::vector<cv::Point> pts = blur_img.MatrixToVector();
    Image best = blur_img.Pressure(center, pts, false, 30, 0.0002, 0.0001);
    best.display("Best");
    best.save("best");

    return 0;
}
