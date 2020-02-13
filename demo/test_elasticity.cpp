/**
 * \file test_elasticity.cpp
 * \brief Test of the implementation of elasticity
 * \author Svenja.B Carole.B
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
    
    
    //Rotate warp_finger with interpolation on small part
    Image small_rotate = warp_finger.InverseScaledRotation(0.02*M_PI, 90, 0.8, 0.5);
    small_rotate.display("Small centered rotation");
    
    
    //Rotate small_rotation with interpolation
    Image whole_rotate = small_rotate.InverseScaledRotation(0.07*M_PI, 200, 0.7, 0.5);
    whole_rotate.display("Rotation on whole warp_finger 3");
    
    
    //Printing the image difference
    Image Diff_0 = warp_finger-whole_rotate;
    Diff_0.display("Diff initial and whole rotation");
    
    
    //Clear the windows
    cv::destroyAllWindows();

    //Rotate warp_finger without interpolation, then interpolate
    Image rotate1 = warp_finger.ScaledRotation(0.2*M_PI, 90, 0.8, 0.5);
    rotate1.BilinearInterpolation();
    rotate1.display("Scaled Rotated warp");
    
    //Rotate rotated image with inverse rotation
    Image rot1 = rotate1.InverseScaledRotation(-0.2*M_PI, 90,0.8, 0.5);
    rot1.display("Inverse Scaled Rotated warp_finger 1");
    
    //Compute and display the difference between both methods
    Image Diff_1 = rot1-warp_finger;
    Diff_1.display("Diff: rot, inverse rot");
    
    
    //Rotate warp_finger with inverse rotation
    Image rot2 = warp_finger.InverseScaledRotation(-0.2*M_PI, 90,0.8, 0.5);
    rot2.display("Warp invere rot");
    //Rotate rotated image without interpolation, then interpolate
    Image rotate2 = rot2.ScaledRotation(0.2*M_PI, 90, 0.8, 0.5);
    rotate2.BilinearInterpolation();
    rotate2.display("Inverse Scaled Rot warp");
    
    //Compute and display the difference between both methods
    Image Diff_2 = rotate2-warp_finger;
    Diff_2.display("Diff: inverse rot, rot");;
    
    
    //Clear the windows
    cv::destroyAllWindows();
    
    //Display original image
    clean_finger.display("Initial clean finger");

    //Squeeze finger inside a given rectangle
    Image squeeze1 = clean_finger.RectangleSqueezing(220,128, 65, 65,1.);
    squeeze1.display("Squeezed finger rectangle");
    
    //Squeeze finger inside a circle for different input weights
    Image squeeze2 = clean_finger.CircleSqueezing(200,128,80,1.);
    squeeze2.display("Squeezed finger circle, weight = 1");
    
    Image squeeze3 = clean_finger.CircleSqueezing(200,128,80,1.5);
    squeeze3.display("Squeezed finger circle, weight = 1.5");
    
    Image squeeze4 = clean_finger.CircleSqueezing(200,128,80,2);
    squeeze4.display("Squeezed finger circle, weight = 2");
    
    
    return 0;
}

