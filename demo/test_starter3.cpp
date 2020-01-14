/**
 * \file test_starter3.cpp
 * \brief Test for sections starter3 and main3
 * \author Thomas.B Clara.B
 * \version 0.1
 * \date 01/12/20
 */


#include "starter3.h"
#include "Image.h"

using namespace std;


int main(){
    Image finger("../img/clean_finger.png");
    finger.display("initial");

    //starter3
    //Id
    int size = 3;
    cv::Mat_<float> id(size, size, int(0));
    id(size/2, size/2) = 1;

    cv::Mat_<float> conv_id = convolution(finger(), id);
    Image classic_id(conv_id);
    classic_id.display("classic id");
    classic_id.save("classic id");

    cv::Mat_<float> convDFT_id = convolutionDFT(finger(), id);
    Image dft_id(convDFT_id);
    dft_id.display("DFT id");
    dft_id.save("DFT id");

    //Diff
    Image diff_id = classic_id - dft_id;
    diff_id.display("diff id");
    diff_id.save("diff id");

    cv::destroyAllWindows();

    //Blurring
    finger.display("initial");
    size = 21;
    cv::Mat_<float> blur(size, size, 1);
    blur /= pow(size, 2);

    cv::Mat_<float> conv_blur = convolution(finger(), blur);
    Image classic_blur(conv_blur);
    classic_blur.display("classic blur");
    classic_blur.save("classic blur");

    cv::Mat_<float> convDFT_blur = convolutionDFT(finger(), blur);
    Image dft_blur(convDFT_blur);
    dft_blur.display("DFT blur");
    dft_blur.save("DFT blur");

    Image diff_blur = classic_blur - dft_blur;
    diff_blur.display("diff blur");
    diff_blur.save("diff blur");

    cv::destroyAllWindows();

    //main3
    finger.display("initial");
    size = 21;

    cv::Mat_<float> dec = convolution_complex(finger(), size, finger().cols/2, finger().rows/2);
    Image dec_img(dec);
    dec_img.display("energy decreasing");
    dec_img.save("Energy decreasing");

    cv::Mat_<float> convblur = convolution_complex(finger(), size, finger().cols/2, finger().rows/2, false);
    Image blur_img(convblur);
    blur_img.display("blurring");
    blur_img.save("Blurring");

    //Using main1
    cv::Point center(blur_img().cols/2, blur_img().rows/2);
    std::vector<cv::Point> pts = blur_img.matrix2vector();
    Image best = blur_img.pressure(center, pts, false, 30, 0.0002, 0.0001);
    best.display("Best");
    best.save("best.png");

    return 0;
}
