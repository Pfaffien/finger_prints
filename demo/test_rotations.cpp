/*! \file test_starter2.cpp
 * \brief Main function for Starter 2
 * 
 * In this file, the functions that where implemented for Starter 2 are tested and the resulting images are displayed. The functions used can be found in \ref image.h.
 */

#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "image.h"

/*! \mainpage
 * This is the fingerprint programming project of Thomas Bauer,
 * Clara Bourgoin, Carole Bellet and Svenja Bünder.
 * The project consists of several files and classes and this
 * documentation should help to navigate through the code.
 * The most important class is \ref image.h which represents the
 * images we are working on.
 */

int main()
{
    //Create instance of image
    cv::String s1( "../img/clean_finger.png" );
    Image finger(s1);

    //Display original image
    finger.display("Clean finger");

    //Rotate finger without interpolation
    Image rotate1 = finger.Rotation(0.25*M_PI);
    rotate1.display("Rotated finger 1");

    Image rotate2 = finger.Rotation(0.25*M_PI);

    //Rotate finger with first interpolation method
    rotate2.BilinearInterpolation();
    rotate2.display("Rotated finger 2");

    //Rotate finger using backward interpolation
    Image rotate3 = finger.InverseRotation(0.25*M_PI);
    rotate3.display("Rotated finger 3");
    rotate3.save("second_rotate");

    //Take a look at difference
    Image diff = rotate3 - rotate2;
    diff.display("Difference");
    diff.save("diff_rotation_methods");
    
    //Rotate back to original position
    Image rotate_back = rotate3.InverseRotation(1.75*M_PI);
    rotate_back.display("Back and forth rotation with 2nd method");
    
    //Compute difference to original image
    Image diff2 = rotate_back - finger;
    diff2.save("diff_original_2nd_rotation");
    
    return 0;
}
