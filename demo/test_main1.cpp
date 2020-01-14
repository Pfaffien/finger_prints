/**
 * \file main1.h
 * \brief Usefull functions to answer the part main 1
 * \author Thomas.B Clara.B
 * \version 0.1
 * \date 01/14/20
 */

#include "Image.h"
#include "main1.h"

using namespace std;

int main()
{
    Image finger("../img/clean_finger.png");
    finger.display("Finger", "Finger");
    cv::Point center(7*finger().cols/16, 9*finger().rows/16);

    // Test of radial functions
    int size = 300;
    cv::Point center_test(size/2, size/2);
    cv::Mat_<float> ones(size, size, 1);
    Image img_ones(ones);
    Image copy = img_ones().clone();
    std::vector<Image> vect;

    img_ones.display("White image", "White image");
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++)
                copy(k, j) = c_isotropic(cv::norm(center_test - cv::Point(j, k)), 0.005, i);
        }
        vect.push_back(copy);
        copy = Image(img_ones().clone());
    }

    vect[0].display("Selected class of function", "Selected class of function");
    vect[0].save("selected_function.png");
    vect[1].display("Exponential", "Exponential");
    vect[1].save("exponential_solution.png");
    vect[2].display("Inverse", "Inverse");
    vect[2].save("inverse_solution.png");

    
    // Test of the selected class of function
    vector<cv::Point> points = finger.matrix2vector();

    Image iso = finger.pressure(center, points, false, 50, 0.00035, 0.00035);
    Image aniso = finger.pressure(center, points);

    iso.display("Isotropic", "Isotropic");
    iso.save("isotropic.png");
    aniso.display("Anisotropic", "Anisotropic");
    aniso.save("anisotropic.png");

    return 0;
}
