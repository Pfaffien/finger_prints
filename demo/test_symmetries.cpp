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

    Image_float img_float(img);

    Image_float img2 = img_float.sym_y();
    Image img22(img2);
    img22.display("Symmetry along y", "Symmetry along y");
    img22.save("symmetry_y");

    Image_float img3 = img_float.sym_x();
    Image img32(img3);
    img32.display("Symmetry along x", "Symmetry along x");
    img32.save("symmetry_x");

    Image_float img4 = img_float.sym_xy();
    Image img42(img4);
    img42.display("Symmetry along the diagonal", "Symmetry along the diagonal");
    img42.save("symmetry_xy");

    return 0;
}
