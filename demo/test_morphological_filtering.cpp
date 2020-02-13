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
    bin.save("binarized");


    //Clear the windows
    cv::destroyAllWindows();


    //Dilatation and erosion binarized image
    Image kernel("../img/filters/ones_3x3.png");
    Image erosion = finger.ErodeBin(kernel());
    erosion.display("Test erosion binarized");
    erosion.save("erosion_bin");


    Image dilatation = finger.DilateBin(kernel());
    dilatation.display("Test dilataion binarized");
    dilatation.save("dilatation_bin");

    //Clear the windows
    cv::destroyAllWindows();

    //Dilatation and erosion grayscaled image
    Image test = finger.ErodeGray(kernel());
    test.display("Test erosion grayscale");
    test.save("erosion_gray");

    Image test2 = finger.DilateGray(kernel());
    test2.display("Test dilation grayscale");
    test2.save("dilatation_gray");

    //Clear the windows
    cv::destroyAllWindows();


    //Commutation of the operators
    //erosion and dilatation
    Image erosion_dilatation = erosion.DilateBin(kernel());
    erosion_dilatation.display("Erosion and dilatation");

    //dilatation and erosion
    Image dilatation_erosion = dilatation.ErodeBin(kernel());
    dilatation_erosion.display("Dilatation and erosion");

    //difference
    Image diff = erosion_dilatation - dilatation_erosion;
    diff.display("Difference");
    cout << "Pourcentage of difference when commuting the operators : " << erosion_dilatation.error(dilatation_erosion, 0.001) << "%" << endl; 

    //Clear the windows
    cv::destroyAllWindows();


    //Improvements
    //Try to approximate moist and dry
    Image diamond("../img/filters/diamond_5x5.png");
    Image moist_bin = moist.Binarize();
    Image dry_bin = dry.Binarize();

    moist_bin.display("Moist finger binarized");
    dry_bin.display("Dry finger binarized");

    Image erosion_dry = finger.ErodeBin(diamond());
    erosion_dry.display("Approximation of dry");

    cv::destroyAllWindows();

    //Using a complex erosion
    Image filter("../img/filters/cross_3x3.png");
    Image dry_complex = finger.Erode(filter(), "complex");
    dry_complex.display("Dry complex");
    dry_complex.save("dry_complex");

    Image dry_diamond = finger.ErodeGray(filter());
    dry_diamond.display("Dry gray");

    Image diff_complex = dry_complex - dry_diamond;
    diff_complex.display("Diff");

    cv::destroyAllWindows();

    Image small_finger("../img/clean_finger_small.png");
    Image skeleton = small_finger.Skeletonize();
    skeleton.display("Partial skeleton");

    return 0;
}
