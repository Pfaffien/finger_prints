#include "image.h"


int main()
{
    Image finger("../img/clean_finger.png");
    finger.display("Original");

    Image naive = finger.BinarizeNaive(100);
    naive.display("Naive binarization (t = 100)");
    
    Image bin = finger.Binarize();
    bin.display("Binarization with Otsu's method");

    
    //To test the naive version
    // std::vector<cv::Point> struct_elt(9);
    // struct_elt[0] = cv::Point(-1, -1);
    // struct_elt[1] = cv::Point(0, -1);
    // struct_elt[2] = cv::Point(1, -1);
    // struct_elt[3] = cv::Point(-1, 0);
    // struct_elt[4] = cv::Point(0, 0);
    // struct_elt[5] = cv::Point(1, 0);
    // struct_elt[6] = cv::Point(-1, 1);
    // struct_elt[7] = cv::Point(0, 1);
    // struct_elt[8] = cv::Point(1, 1);

    cv::Mat_<float> kernel(3, 3, 1);

    Image erosion = finger.Erode(kernel);
    erosion.display("Test erosion");

    Image dilatation = finger.Dilate(kernel);
    dilatation.display("Test dilataion");

    //Erosion and dilatation
    Image erosion_dilatation = erosion.Dilate(kernel);
    erosion_dilatation.display("Erosion and dilatation");

    //Dilatation and erosion
    Image dilatation_erosion = dilatation.Erode(kernel);
    dilatation_erosion.display("Dilatation and erosion");

    //Difference
    Image diff = erosion_dilatation - dilatation_erosion;
    diff.display("Difference");

    return 0;
}