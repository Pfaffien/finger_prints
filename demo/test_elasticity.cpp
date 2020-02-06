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
    //Create instance of image warp 2 finger
    cv::String s1( "../img/warp2_finger.png" );
    Image warp_finger(s1);
    
    //Display original image
    warp_finger.display("Initial warp 2 finger");
    
    cv::String s2( "../img/clean_finger.png" );
    Image clean_finger(s2);
    
    
    //Rotate warp_finger with interpolation
    Image small_rotate = warp_finger.InverseScaledRotation(0.0*M_PI, 90, 0.8, 0.5);
    small_rotate.display("Small centered rotation");
    
    
    //Rotate small_rotation with interpolation
    Image whole_rotate = small_rotate.InverseScaledRotation(0.07*M_PI, 200, 0.7, 0.5);
    whole_rotate.display("Rotation on whole warp_finger 3");
    
    
    //Printing the image difference
    Image Diff_2 = warp_finger-whole_rotate;
    Diff_2.display("Difference between initial and whole rotation");
    
    
    //Clear the windows
    cv::destroyAllWindows();

    //ScaledRotatin and inverse scaled InverseScaledRotation
    
    //Rotate warp_finger without interpolation
    Image rotate1 = warp_finger.ScaledRotation(0.2*M_PI, 90, 0.8, 0.5);
    rotate1.BilinearInterpolation();
    rotate1.display("Inverse Scaled Rotated warp_finger 1");
    
    Image rot1 = rotate1.InverseScaledRotation(-0.2*M_PI, 90,0.8, 0.5);
    Image Diff_4 = rot1-warp_finger;
    Diff_4.display("Difference Matrix 4");
    
    
     //Clear the windows
    //cv::destroyAllWindows();

    //ScaledRotatin and inverse scaled InverseScaledRotation
    
    Image rot2 = warp_finger.InverseScaledRotation(-0.2*M_PI, 90,0.8, 0.5);
    
    
    
    //Rotate warp_finger without interpolation
    Image rotate2 = rot2.ScaledRotation(0.2*M_PI, 90, 0.8, 0.5);
    rotate2.BilinearInterpolation();
    rotate2.display("Inverse Scaled Rotated warp_finger 2");
    
    
    Image Diff_5 = rotate2-warp_finger;
    Diff_5.display("Difference Matrix 5");
    
    return 0;
}



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
