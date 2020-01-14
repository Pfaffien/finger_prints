#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "Starter2.h"

/*! \mainpage
 * This is the fingerprint programming project of Thomas Bauer, Clara Bourgoin, Carol Bellet and Svenja Bünder.
 * The project consists of several files and classes and this documentation should help to navigate through the code.
 * The most important class is Image.h which represents the images we are working on.
 */

int main()
{
    cv::String s1( "../img/clean_finger.png" );
    Image finger(s1);

    finger.Display("Clean finger", "Clean finger");

    Image rotate = finger.BackwardInterpolation(1.75*M_PI);
    //finger.Interpolation();
    std::cerr << "rotation done \n";
    rotate.Display("Rotated finger", "Rotated finger");
    Image rotate_back = rotate.BackwardInterpolation(0.25*M_PI);
    
    Image rotate_back_3 = rotate_back.BackwardInterpolation(0.25*M_PI);
    rotate_back_3 = rotate_back_3.BackwardInterpolation(1.75*M_PI);
    rotate_back_3 = rotate_back_3.BackwardInterpolation(0.25*M_PI);
    rotate_back_3 = rotate_back_3.BackwardInterpolation(1.75*M_PI);
    
    
    
    //Image diff = finger.DifferenceMatrix(rotate_back);
    Image diff = rotate_back_3.DifferenceMatrix(rotate_back);
    diff.Display("Difference","Difference");
    return 0;
}
