/**
 * \file test_elasticity.cpp
 * \brief Test of the implementation of elasticity
 * \author Svenja.B Carolle.B
 * \version 0.1
 * \date 01/20/20
 */

#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "image.h"



int main()
{
    //Create instance of image
    cv::String s1( "../img/warp2_finger.png" );
    Image warp_finger(s1);
    
    
    cv::String s2( "../img/clean_finger.png" );
    Image clean_finger(s2);
    
    //Display original image
    warp_finger.display("Warp 2 finger");

    
    //Rotate warp_finger without interpolation
    Image rotate2 = warp_finger.InverseScaledRotation(0.0*M_PI, 90, 0.8, 0.5);
    rotate2.BilinearInterpolation();
    rotate2.display("Rotate 2 ");
    
    
    //Rotate warp_finger without interpolation
    Image rotate3 = rotate2.InverseScaledRotation(0.07*M_PI, 200, 0.7, 0.5);
    

    //Rotate warp_finger with first interpolation method
    rotate3.display("Rotated warp_finger 3");
    
    rotate3.save("scaled_rot_warp");
    
    //Printing the image difference
    Image Diff_2 = warp_finger-rotate3;
    Diff_2.display("Difference Matrix 2");
    
    Diff_2.save("diff_scaled_rot");
    
    return 0;
}


/* ScaledRotatin and inverse scaled InverseScaledRotation
 * 
 * //Rotate warp_finger without interpolation
    Image rotate1 = warp_finger.InverseScaledRotation(0.13*M_PI, 90, 0.8, 0.5);
    rotate1.display("Inverse Scaled Rotated warp_finger 1");
    
    Image rot1 = rotate1.InverseScaledRotation(-0.13*M_PI, 90,0.8, 0.5);
    Image Diff_4 = rot1.DifferenceMatrix(warp_finger);
    Diff_4.display("Difference Matrix 4");
    
    
    */

/* Differences
 * 
 * //Computing and printing the difference in percentage between warp finger and rotate 1
    float diff_1 = rotate1.error(warp_finger, 0);
    std::cout<<"Difference between rotate 1 and warp warp_finger is : "<<diff_1<<std::endl;
    
    //Computing and printing the difference in percentage between warp finger and rotate 3
    float diff_2 = warp_finger.error(rotate3, 0);
    std::cout<<"Difference between warp_finger and rotate 3 is : "<<diff_2<<std::endl;
    
    //Printing the image difference
    Image Diff_1 = warp_finger.DifferenceMatrix(rotate1);
    //Diff_1.display("Difference Matrix 1");
    
    //Printing the image difference
    Image Diff_2 = warp_finger.DifferenceMatrix(rotate3);
    //Diff_2.display("Difference Matrix 2");
    
    */
