#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "starter3.h"
#include "Image.h"

int main(){
  cv::String s1( "../img/clean_finger.png" );
  Image finger(s1);

  finger.display("Clean finger", "Clean finger");
  cv::Mat_<float> mat_rien(3,3);
  mat_rien(2,2) = 1;
  Image rien(mat_rien);

  Image res = convolution(finger, rien);
  res.display();
  return 0;
}
