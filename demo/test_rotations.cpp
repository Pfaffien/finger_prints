/**
 * \file test_rotations.cpp
 * \brief Test for the rotations
 * \author Carole.B, Svenja.B
 * \version 0.1
 * \date 01/18/20
 */


#include "image.h"

/**
 * \fn int main()
 * \brief Test of the rotation functions functions
 * TODO
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
