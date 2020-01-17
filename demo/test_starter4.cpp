#include "image.h"


int main()
{
    Image finger("../img/clean_finger.png");
    finger.display("Original");

    Image naive = finger.BinarizeNaive(100);
    naive.display("Naive binarization (t = 100)");
    
    Image bin = finger.Binarize();
    bin.display("Binarization with Otsu's method");

    return 0;
}