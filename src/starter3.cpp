#include "starter3.h"

cv::Mat_<float> convolution(cv::Mat_<float> f, cv::Mat_<float> k){
  cv::Mat_<float> res(f.rows, f.cols); //initialization of the result
  //finding the midle of the matrix B
  int middle_x = k.cols/2;
  int middle_y = k.rows/2;
  int mm, nn, ii, jj;
  for (int i = 0; i < f.rows; i++){
    for (int j = 0; j < f.cols; j++){
      for (int m = 0; m < k.rows; m++){
        for (int n = 0; n < k.cols; n++){
          //indexes for B
          mm = k.rows - 1 - m;
          nn = k.cols - 1 - n;

          //indexes for A
          ii = i + middle_y - mm;
          jj = j + middle_x - nn;

          //Verification of boundary
          if (ii >= 0 && ii < f.rows && jj>=0 && jj < f.cols){
            res(i,j) += f(ii,jj)*k(mm,nn);
          }
          //we use the extension
          else{
            if (ii < 0) ii = 0;
            if (jj < 0) jj = 0;
            if (ii >= f.rows) ii = f.rows - 1;
            if (jj >= f.cols) jj = f.cols - 1;
            res(i,j) += f(ii,jj)*k(mm,nn);
          }
        }
      }
    }
  }
  // normalization of the resultat
  double min, max;
  minMaxLoc(res, &min, &max);
  res = res/max;
  return res;
}

cv::Mat_<float> convolutionDFT(cv::Mat_<float> f, cv::Mat_<float> k){
    int M, N;
    M = f.rows;
    N = f.cols;
    cv::Mat_<float> conv(M, N);
    cv::Mat_<float> padded(M, N);
    cv::Mat_<float> k_hat, f_hat;

    //Pas opti (cf. padded et getOptimalDFTSize)
    cv::dft(k, k_hat);
    cv::dft(f, f_hat);

    for (int i = 0; i < k_hat.rows; i++) {
        for (int j = 0; j < k_hat.cols; j++)
            padded(i, j) = k_hat(i, j);
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            conv(i, j) = padded(i, j) * f_hat(i, j);
    }

    cv::idft(conv, conv);

    return conv;
}
