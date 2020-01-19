#include "image.h"


int main()
{
    Image finger("../img/clean_finger.png");
    finger.display("Original");

    Image naive = finger.BinarizeNaive(100);
    naive.display("Naive binarization (t = 100)");
    
    Image bin = finger.Binarize();
    bin.display("Binarization with Otsu's method");

    
    std::vector<cv::Point> struct_elt(9);
    struct_elt[0] = cv::Point(-1, -1);
    struct_elt[1] = cv::Point(0, -1);
    struct_elt[2] = cv::Point(1, -1);
    struct_elt[3] = cv::Point(-1, 0);
    struct_elt[4] = cv::Point(0, 0);
    struct_elt[5] = cv::Point(1, 0);
    struct_elt[6] = cv::Point(-1, 1);
    struct_elt[7] = cv::Point(0, 1);
    struct_elt[8] = cv::Point(1, 1);

    //Ne rien exécuter sauf si tu veux attentre 3 min par test !

    //Environ 3 min
    // Image swapped = bin.Erode(struct_elt);
    // swapped.display("Test erosion");

    //Environ 3min
    //Utilise le fait que l'érosion de l'arrière-plan correspond à
    //une dilatation du premier plan
    // Image moins = -bin;
    // Image dilatation = moins.Erode(struct_elt);
    // Image to_show = -dilatation;
    // to_show.display("Test dilataion");

    return 0;
}