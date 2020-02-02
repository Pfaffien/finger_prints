/**
 * \file test_translations.cpp
 * \brief Test of the implementation of the translations
 * \author Clara.B
 * \version 0.1
 * \date 01/20/20
 */

#include "image.h"

using namespace std;

int main()
{
   //Image used for the test
    Image finger("../img/clean_finger.png");
    finger.display("Finger");

    Image trans = finger.Translation(-50,10);
    trans.display("translation");
    
    return 0;
}
