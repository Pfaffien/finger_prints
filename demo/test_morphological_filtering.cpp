/**
 * \file test_morphological_filtering.cpp
 * \brief Test of the implementation of morphological filtering
 * \author Thomas.B Clara.B
 * \version 0.1
 * \date 01/21/20
 */

#include "image.h"
using namespace std;

/**
 * \fn int main()
 * \brief Test of the morphological functions
 * The function tests the binarization, the erosion and dilatation for both binarized and grayscales images
 */
int main()
{
    Image finger("../img/clean_finger.png");
    Image moist("../img/moist_finger.png");
    Image dry("../img/dry_finger.png");    
    finger.display("Original");

    //Binarization
    //naive method
    Image naive = finger.BinarizeNaive(100);
    naive.display("Naive binarization (t = 100)");

    //otsu's method
    Image bin = finger.Binarize();
    bin.display("Binarization with Otsu's method");

    //comparison
    cout << "The error between the two methods is : " << naive.error(bin, 0.001) << "%" << endl;

    //Clear the windows
    cv::destroyAllWindows();


    //Dilatation and erosion binarized image
    cv::Mat_<float> kernel(3, 3, 1);
    Image erosion = finger.ErodeBin(kernel);
    erosion.display("Test erosion binarized");

    Image dilatation = finger.DilateBin(kernel);
    dilatation.display("Test dilataion binarized");

    //Clear the windows
    cv::destroyAllWindows();

    //Dilatation and erosion grayscaled image
    Image test = finger.ErodeGray(kernel);
    test.display("Test erosion grayscale");

    Image test2 = finger.DilateGray(kernel);
    test2.display("Test dilation grayscale");

    //Clear the windows
    cv::destroyAllWindows();


    //Commutation of the operators
    //erosion and dilatation
    Image erosion_dilatation = erosion.DilateBin(kernel);
    erosion_dilatation.display("Erosion and dilatation");

    //dilatation and erosion
    Image dilatation_erosion = dilatation.ErodeBin(kernel);
    dilatation_erosion.display("Dilatation and erosion");

    //difference
    Image diff = erosion_dilatation - dilatation_erosion;
    diff.display("Difference");
    cout << "Pourcentage of difference when commuting the operators : " << erosion_dilatation.error(dilatation_erosion, 0.001) << "%" << endl; 

    //Clear the windows
    cv::destroyAllWindows();


    //Improvements
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

    Image moist_bin = moist.Binarize();
    Image dry_bin = dry.Binarize();

    moist_bin.display("Moist finger binarized");
    dry_bin.display("Dry finger binarized");

    Image erosion_dry = finger.ErodeBin(diamond);
    erosion_dry.display("Approximation of dry");

    return 0;
}
