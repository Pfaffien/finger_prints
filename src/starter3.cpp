#include <iostream>

#include "starter3.h"
#include "Image.h"

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
    std::cout << M << std::endl;
    std::cout << N << std::endl;
    cv::Mat_<float> conv(M, N);
    cv::Mat_<float> k_hat, f_hat;
    //Pas opti (cf. padded et getOptimalDFTSize)
    cv::dft(k, k_hat);
    cv::dft(f, f_hat);
    std::cout << f_hat << std::endl;

    cv::Mat_<float> padded(M, N);
    for (int i = 0; i < k_hat.rows; i++) {
        for (int j = 0; j < k_hat.cols; j++)
            padded(i, j) = k_hat(i, j);
    }
    // std::cout << padded << std::endl;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            conv(i, j) = padded(i, j) * f_hat(i, j);
    }
    // std::cout << conv << std::endl;
    cv::idft(conv, conv);

    // normalization of the resultat
    double min, max;
    minMaxLoc(conv, &min, &max);
    conv = conv/max;
    return conv;
}

cv::Mat_<float> convolveDFT(cv::Mat_<float> f, cv::Mat_<float> k){
    int M, N;
    M = f.rows;
    N = f.cols;

    cv::Mat planesF[] = {cv::Mat_<float>(f), cv::Mat::zeros(f.size(), CV_32F)};
    cv::Mat planesK[] = {cv::Mat_<float>(k), cv::Mat::zeros(k.size(), CV_32F)};

    cv::Mat complexF, complexK, complexPad;

    cv::Mat_<float> pad(M, N, (int) 0);
    cv::Mat_<float> clonedK = k.clone();
    /* std::cout << complexK << std::endl; */
    /* std::cout << cloned << std::endl; */
    for (int i = 0; i < k.rows; i++) {
        for (int j = 0; j < k.cols; j++)
            pad(i, j) = clonedK(i, j);
    }
    /* std::cout << pad << std::endl; */
    cv::Mat planesPad[] = {pad, cv::Mat::zeros(pad.size(), CV_32F)};
     
    cv::merge(planesF, 2, complexF);
    /* cv::merge(planesK, 2, complexK); */
    cv::merge(planesPad, 2, complexPad);
    
    cv::dft(complexF, complexF);
    /* cv::dft(complexK, complexK); */
    cv::dft(complexPad, complexPad);

    cv::Mat_<float> conv(M, N);
    /* cv::Mat_<float> padded(M, N); */
    /* cv::Mat_<float> clonedK = complexK.clone(); */
    /* /1* std::cout << cloned << std::endl; *1/ */
    /* for (int i = 0; i < complexK.rows; i++) { */
    /*     for (int j = 0; j < complexK.cols; j++) */
    /*         padded(i, j) = clonedK(i, j); */
    /* } */
    /* std::cout << padded << std::endl; */

    cv::Mat_<float> clonedF = complexF.clone();
    cv::Mat_<float> clonedPad = complexPad.clone();
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            conv(i, j) = clonedPad(i, j) * clonedF(i, j);
    }
    /* std::cout << conv << std::endl; */

    cv::idft(conv, conv, cv::DFT_SCALE | cv::DFT_REAL_OUTPUT);
    cv::normalize(conv, conv, 0, 1, cv::NORM_MINMAX);
    /* std::cout << conv << std::endl; */
    
    return conv;
}
