#include "image.h"


int main()
{
    Image finger("../img/clean_finger.png");
    Image moist("../img/moist_finger.png");
    Image dry("../img/dry_finger.png");
    // finger.display("Original");

    Image naive = finger.BinarizeNaive(100);
    // naive.display("Naive binarization (t = 100)");
    
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
    Image test = finger.ErodeGray(kernel);
    test.display("aaa");
    Image test2 = finger.DilateGray(kernel);
    test2.display("bbb");

    Image erosion = finger.ErodeBin(kernel);
    // erosion.display("Test erosion");

    Image dilatation = finger.DilateBin(kernel);
    // dilatation.display("Test dilataion");


    //Try to approximate moist and dry
    int size = 5;
    cv::Mat_<float> diamond(size, size, 1);
    diamond(0, 0) = 0;
    diamond(1, 0) = 0;
    diamond(0, 1) = 0;
    diamond(0, size-1) = 0;
    diamond(0, size-2) = 0;
    diamond(1, size-1) = 0;
    diamond(size-1, 0) = 0;
    diamond(size-2, 0) = 0;
    diamond(size-1, 1) = 0;
    diamond(size-1, size-1) = 0;
    diamond(size-1, size-2) = 0;
    diamond(size-2, size-1) = 0;

    // std::cout << diamond << std::endl;

    Image moist_bin = moist.Binarize();
    Image dry_bin = dry.Binarize();

    moist_bin.display("Moist finger binarized");
    dry_bin.display("Dry finger binarized");

    Image erosion_dry = finger.ErodeBin(diamond);
    erosion_dry.display("Approximation of dry");


    //Commutation of the operators
    //Erosion and dilatation
    Image erosion_dilatation = erosion.DilateBin(kernel);
    erosion_dilatation.display("Erosion and dilatation");

    //Dilatation and erosion
    Image dilatation_erosion = dilatation.ErodeBin(kernel);
    dilatation_erosion.display("Dilatation and erosion");

    //Difference
    Image diff = erosion_dilatation - dilatation_erosion;
    diff.display("Difference");

    return 0;
}