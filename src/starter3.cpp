/**
 * \file starter3.cpp
 * \brief Usefull functions to answer the part starter 3 and main 3
 * \author Thomas.B Clara.B
 * \version 0.1
 * \date 01/12/20
 */

#include <iostream>
#include <cmath>
#include <opencv2/core/types.hpp>
#include "starter3.h"
#include "Image.h"


cv::Mat_<float> convolution(cv::Mat_<float> f, cv::Mat_<float> k)
{
    //initialization of the result
    cv::Mat_<float> res(f.rows, f.cols);

    //finding the midle of the matrix k
    int middle_x = k.cols/2;
    int middle_y = k.rows/2;

    int mm, nn, ii, jj; //initialization of usefull indices

    for (int i = 0; i < f.rows; i++){
        for (int j = 0; j < f.cols; j++){
            for (int m = 0; m < k.rows; m++){
                for (int n = 0; n < k.cols; n++){
                    //indices for k
                    mm = k.rows - 1 - m;
                    nn = k.cols - 1 - n;

                    //indices for f
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


cv::Mat_<float> convolutionDFT(cv::Mat_<float> f, cv::Mat_<float> k)
{
    std::cout << "r" << f.rows << " c" << f.cols << std::endl;
    int M = f.rows+k.rows-1;
    int N = f.cols+k.cols-1;
    cv::Mat_<float> conv(M, N);
    cv::Mat_<float> res(f.rows, f.cols);

    //padding of f and k
    cv::Mat_<float> paddedk, paddedf;
    cv::copyMakeBorder(k, paddedk, 0, M - k.rows, 0, N - k.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
    cv::copyMakeBorder(f, paddedf, 0, M - f.rows, 0, N - f.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));

    // DFT
    cv::Mat_<float> k_hat, f_hat;
    cv::dft(paddedk, k_hat, 0, k.rows);
    cv::dft(paddedf, f_hat, 0, f.rows);

    // Product
    cv::mulSpectrums(f_hat, k_hat, conv, 0);

    // Inverse DFT
    cv::idft(conv, conv, cv::DFT_SCALE, f.rows+k.cols-1);
    std::cout << "r" << conv.rows << " c" << conv.cols << std::endl;
    res = conv(cv::Rect(k.cols/2, k.rows/2, f.cols, f.rows));

    // Normalization of the result
    cv::normalize(res, res, 0, 1, cv::NORM_MINMAX);
    return res;
}


float distance_max(cv::Mat_<float> mat, int x_c, int y_c)
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

    return (float)max;
}


cv::Mat_<float> kernel_decrease(int size, float distance, float distance_max)
{
    cv::Mat_<float> id(size, size, (int) 0);
    id(size/2, size/2) = 1;

    id = id * (distance_max - distance) / distance_max;

    return id;

}


cv::Mat_<float> kernel_blur(int size, float distance, float distance_max)
{
    cv::Mat_<float> k(size, size, 1);
    k /= pow(size, 2);
    cv::Mat_<float> id(size, size, (int) 0);
    id(size/2, size/2) = 1;
    k = k * distance/distance_max + id * (distance_max - distance) / distance_max;
    return k;
}


cv::Mat_<float> convolution_complex(cv::Mat_<float> f, int size, int x_c, int y_c, bool decrease)
{
    //initialization of points
    cv::Point center(x_c, y_c);
    cv::Point tmp((int) 0, (int) 0);

    //initialization of the result
    cv::Mat_<float> res(f.rows, f.cols);

    //finding the midle for the kernel
    int middle_x = size/2;
    int middle_y = size/2;

    //initialization of usefull indices and values
    int mm, nn, ii, jj;
    cv::Mat_<float> kern(size, size, (int) 0);
    float dist;
    float dist_max = distance_max(f, x_c, y_c);

    for (int i = 0; i < f.rows; i++){
        tmp.y = i;
        for (int j = 0; j < f.cols; j++){
            tmp.x = j;
            //distance of the center
            dist = cv::norm(center - tmp);
            //creation of the kernel
            if (decrease) kern = kernel_decrease(size, dist, dist_max);
            else kern = kernel_blur(size, dist, dist_max);
            for (int m = 0; m < size; m++){
                for (int n = 0; n < size; n++){

                    //indices for the kernel
                    mm = size - 1 - m;
                    nn = size - 1 - n;

                    //indices for F
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


cv::Mat_<float> kernel_test(int size, float dist, float dist_max)
{
    cv::Mat_<float> id(size, size, int(0));
    id(size/2, size/2) = 1;
    // std::cout << id << std::endl;
    cv::Mat_<float> blur_1(size, size, int(0));

    for (int i = size/8; i < size-size/8; i++){
        for (int j = size/8; j < size - size/8; j++){
            blur_1(i,j) = 1;
        }
    }

    blur_1 /= pow(size-2*size/8,2);
    cv::Mat_<float> blur_2(size, size, 1);
    blur_2/=pow(size,2);

    return normalization((dist_max-dist)/dist_max*id + (1-(dist_max-dist)/dist_max)*blur_1 + pow(1-(dist_max-dist)/dist_max,2)*blur_2);
}
