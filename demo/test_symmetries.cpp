#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "Image.h"


int main()
{
    cv::String s1( "../img/lion.png" );
    Image img(s1);
    img.display("Lion", "Lion");

    Image img2 = img.sym_y();
    img2.display("Symmetry along y", "Symmetry along y");
    img2.save("symmetry_y");

    Image img3 = img.sym_x();
    img3.display("Symmetry along x", "Symmetry along x");
    img3.save("symmetry_x");

    Image img4 = img.sym_xy();
    img4.display("Symmetry along the diagonal", "Symmetry along the diagonal");
    img4.save("symmetry_xy");

    return 0;
}
