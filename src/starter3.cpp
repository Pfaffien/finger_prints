#include "starter3.h"

cv::Mat_<float> convolution(cv::Mat_<float> A, cv::Mat_<float> B){
  cv::Mat_<float> res(A.rows, A.cols); //initialization of the result
  //finding the midle of the matrix B
  int middle_x = B.cols/2;
  int middle_y = B.rows/2;
  int mm, nn, ii, jj;
  for (int i = 0; i < A.rows; i++){
    for (int j = 0; j < A.cols; j++){
      for (int m = 0; m < B.rows; m++){
        for (int n = 0; n < B.cols; n++){
          //indexes for B
          mm = B.rows - 1 - m;
          nn = B.cols - 1 - n;

          //indexes for A
          ii = i + middle_y - mm;
          jj = j + middle_x - nn;
          //Verification of boundary
          if (ii >= 0 && ii < A.rows && jj>=0 && jj < A.cols){
            res(i,j) += A(ii,jj)*B(mm,nn);
          }
          else{
            //TODO boundary conditions
          }
        }
      }
    }
  }
  return res;
}

cv::Mat_<float> normalization(cv::Mat_<float> img){
  cv::Mat_<float> mat;
  float sum = 0;
  for (int i = 0; i < img.rows; i++){
    for (int j = 0; i < img.cols; j++){
      sum += img(i,j);
    }
  }
  mat = mat/sum;
  return mat;
}
