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


/* Première version, simple et pas opti */
cv::Mat_<float> convolutionDFT(cv::Mat_<float> f, cv::Mat_<float> k)
{
    int M, N;
    M = f.rows;
    N = f.cols;
    cv::Mat_<float> conv(M, N);
    cv::Mat_<float> k_hat, f_hat;

    // Padding
    cv::Mat_<float> padded(M, N, (int) 0);
    cv::Mat_<float> clonedK = k.clone();
    for (int i = 0; i < k.rows; i++) {
        for (int j = 0; j < k.cols; j++)
            padded(i, j) = clonedK(i, j);
    }

    // DFT
    cv::dft(padded, k_hat, 0, k.rows);
    cv::dft(f, f_hat, 0, f.rows);

    // Product
    // 0, else it corresponds to M 1D FFT
    cv::mulSpectrums(f_hat, k_hat, conv, 0);
 
    //If we want to try without using muSpectrums
    /* for (int i = 0; i < M; i++) { */
    /*     for (int j = 0; j < N; j++) */
    /*         conv(i, j) = k_hat(i, j) * f_hat(i, j); */
    /* } */

    // Inverse DFT
    cv::idft(conv, conv, cv::DFT_SCALE | cv::DFT_REAL_OUTPUT);

    // Normalization of the result
    cv::normalize(conv, conv, 0, 1, cv::NORM_MINMAX);
    return conv;
}


/* Deuxième version optimisée mais très proche du copier coller */
cv::Mat_<float> cDFT(cv::Mat_<float> A, cv::Mat_<float> B)
{
    // reallocate the output array if needed
    cv::Mat C;
    C.create(cv::abs(A.rows - B.rows)+1, cv::abs(A.cols - B.cols)+1, A.type());
    cv::Size dftSize;

    // calculate the size of DFT transform
    dftSize.width = cv::getOptimalDFTSize(A.cols + B.cols - 1);
    dftSize.height = cv::getOptimalDFTSize(A.rows + B.rows - 1);

    // allocate temporary buffers and initialize them with 0's
    cv::Mat tempA(dftSize, A.type(), cv::Scalar::all(0));
    cv::Mat tempB(dftSize, B.type(), cv::Scalar::all(0));

    // copy A and B to the top-left corners of tempA and tempB, respectively
    cv::Mat roiA(tempA, cv::Rect(0,0,A.cols,A.rows));
    A.copyTo(roiA);
    cv::Mat roiB(tempB, cv::Rect(0,0,B.cols,B.rows));
    B.copyTo(roiB);

    // now transform the padded A & B in-place;
    // use "nonzeroRows" hint for faster processing
    cv::dft(tempA, tempA, 0, A.rows);
    cv::dft(tempB, tempB, 0, B.rows);

    // multiply the spectrums;
    // the function handles packed spectrum representations well
    cv::mulSpectrums(tempA, tempB, tempA, 0);

    // transform the product back from the frequency domain.
    // Even though all the result rows will be non-zero,
    // you need only the first C.rows of them, and thus you
    // pass nonzeroRows == C.rows
    /* dft(tempA, tempA, DFT_INVERSE + DFT_SCALE, C.rows); */
    cv::idft(tempA, tempA, cv::DFT_SCALE | cv::DFT_REAL_OUTPUT, C.rows);
    
    // now copy the result back to C.
    tempA(cv::Rect(0, 0, C.cols, C.rows)).copyTo(C);
    // all the temporary buffers will be deallocated automatically
    cv::normalize(C, C, 0, 1, cv::NORM_MINMAX);

    return cv::Mat_<float>(C);
}
