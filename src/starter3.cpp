#include <iostream>
#include <cmath>
#include <opencv2/core/types.hpp>
#include "starter3.h"
#include "Image.h"


//a modifier car proche copier coller
cv::Mat_<float> convolution(cv::Mat_<float> f, cv::Mat_<float> k)
{
    //initialization of the result
    cv::Mat_<float> res(f.rows, f.cols);

    //finding the midle of the matrix B
    int middle_x = k.cols/2;
    int middle_y = k.rows/2;
   
    int mm, nn, ii, jj; //initialization of usefull indices
    
    for (int i = 0; i < f.rows; i++){
        for (int j = 0; j < f.cols; j++){
            for (int m = 0; m < k.rows; m++){
                for (int n = 0; n < k.cols; n++){
                    //indices for B
                    mm = k.rows - 1 - m;
                    nn = k.cols - 1 - n;

                    //indices for A
                    ii = i + middle_y - mm;
                    jj = j + middle_x - nn;

                    //Are we at the boundary of the image?
                    if (ii >= 0 && ii < f.rows && jj>=0 && jj < f.cols){
                        res(i,j) += f(ii,jj)*k(mm,nn);
                    }
                    //we use the extension to deal with boundaries
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
    cv::normalize(res, res, 0, 1, cv::NORM_MINMAX);
    
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


//pas opti
double distance_max(cv::Mat_<float> mat, int x_c, int y_c)
{
    cv::Point center(x_c, y_c);
    cv::Point tmp((int) 0, (int) 0);
    cv::Mat_<float> dist(mat.rows, mat.cols, (int) 0);

    for (int i = 0; i < mat.rows; i++){
        tmp.y = i;
        for (int j = 0; j < mat.cols; j++){
            tmp.x = j;
            dist(i,j) = cv::norm(center - tmp);
        }
    }
    
    double min, max;
    minMaxLoc(dist, &min, &max);
    
    return max;
}


/* Vérifier qu'il s'agit bien de ce qu'ils attendent */
cv::Mat_<float> kernel(cv::Mat_<float> initial, float distance, float distance_max)
{

    cv::Mat_<float> k = initial.clone();
    int size = k.rows;
    cv::Mat_<float> id(size, size, (int) 0);
    id(size/2, size/2) = 1;

    k = k * (distance_max - distance) / distance_max;
    
    return k;

}


cv::Mat_<float> kernel_blurring(cv::Mat_<float> initial, float distance, float distance_max)
{
    cv::Mat_<float> k = initial.clone();
    int size = k.rows;
    cv::Mat_<float> id(size, size, (int) 0);
    id(size/2, size/2) = 1;

    k = k * distance/distance_max + id * (distance_max - distance) / distance_max;
    
    return k;
}


cv::Mat_<float> convolution_decrease(cv::Mat_<float> f, cv::Mat_<float> k, int x_c, int y_c)
{
    //initialization of points
    cv::Point center(x_c, y_c);
    cv::Point tmp((int) 0, (int) 0);

    //initialization of the result
    cv::Mat_<float> res(f.rows, f.cols);

    //finding the midle of the matrix k
    int middle_x = k.cols/2;
    int middle_y = k.rows/2;
    
    //initialization of usefull indices
    int mm, nn, ii, jj;
    cv::Mat_<float> kern(k.rows, k.cols, (int) 0);
    float dist;

    double dist_max = distance_max(f, x_c, y_c);

    for (int i = 0; i < f.rows; i++){
        tmp.y = i;
        for (int j = 0; j < f.cols; j++){
            tmp.x = j;
            for (int m = 0; m < k.rows; m++){
                for (int n = 0; n < k.cols; n++){
                    //distance of the center
                    dist = cv::norm(center - tmp);//distance(x_c,y_c,j,i);
                    // std::cout << "distance " << dist_max-dist << std::endl;
                    kern = kernel_blurring(k, dist, dist_max);
                    // std::cout << kern << std::endl;

                    //indices for B
                    mm = k.rows - 1 - m;
                    nn = k.cols - 1 - n;

                    //indices for A
                    ii = i + middle_y - mm;
                    jj = j + middle_x - nn;

                    //Are we at the boundary of the image?
                    if (ii >= 0 && ii < f.rows && jj>=0 && jj < f.cols){
                        res(i,j) += f(ii,jj)*kern(mm,nn);
                    }
                    //we use the extension to deal with boundaries
                    else{
                        if (ii < 0) ii = 0;
                        if (jj < 0) jj = 0;
                        if (ii >= f.rows) ii = f.rows - 1;
                        if (jj >= f.cols) jj = f.cols - 1;
                        res(i,j) += f(ii,jj)*kern(mm,nn);
                    }
                }
            }
        }
    }

    // normalization of the resultat
    cv::normalize(res, res, 0, 1, cv::NORM_MINMAX);

    return res;
}


cv::Mat_<float> normalization(cv::Mat_<float> mat)
{
    float sum = 0;
    for (int i = 0; i < mat.rows; i++){
        for (int j = 0; j < mat.cols; j++){
            sum += mat(i,j);
        }
    }
    cv::Mat_<float> res = mat.clone();
    return res/sum;
}
