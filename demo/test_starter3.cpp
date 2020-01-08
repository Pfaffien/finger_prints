#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "starter3.h"
#include "Image.h"

using namespace std;

int main(){
  cv::String s1( "../img/clean_finger.png" );
  Image finger(s1);

  finger.display("Clean finger", "Clean finger");

  cv::Mat_<float> kernel (3,3);
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 4; j++){
      kernel(i,j) = -1;
    }
  }
  kernel(1,1) = 8;

  cv::Mat_<float> res = convolution(finger(), kernel);
  Image res_img(res);

  res_img.display("res convol", "res convol");
  return 0;
}
