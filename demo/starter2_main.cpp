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
 * The most important class is Image.h which represents the
 * images we are working on.
 */

int main()
{
    //Create instance of image
    cv::String s1( "../img/clean_finger.png" );
    Image finger(s1);

    //Display original image
    finger.Display("Clean finger", "Clean finger");

    //Rotate finger without interpolation
    Image rotate1 = finger.Rotation(0.25*M_PI);
    rotate1.Display("Rotated finger 1", "Rotated finger 1");

    Image rotate2 = finger.Rotation(0.25*M_PI);

    //Rotate finger with first interpolation method
    rotate2.BilinearInterpolation();
    rotate2.Display("Rotated finger 2", "Rotated finger 2");

    //Rotate finger using backward interpolation
    Image rotate3 = finger.BackwardInterpolation(1.75*M_PI);
    rotate3.Display("Rotated finger 3", "Rotated finger 3");

    //Take a look at difference
    Image diff = rotate3.DifferenceMatrix(rotate2);
    diff.Display("Difference", "Difference");
    return 0;
}
