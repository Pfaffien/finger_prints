/**
 * \file test_pressure.cpp
 * \brief Test of the implementation of the pressure variation
 * \author Clara.B
 * \version 0.1
 * \date 01/22/20
 */

#include "image.h"

using namespace std;

int main()
{
   //Image used for the test
    Image finger("../img/clean_finger.png");
    finger.display("Finger");

    //Test of vertical translation
    Image transv = finger.TranslationV(-50);
    transv.display("Vertical translation (-50)");
    Image transv2 = finger.TranslationV(50);
    transv2.display("Vertical translation (50");

    //Test of horizontal translation
    Image transh = finger.TranslationH(50);
    transh.display("Horizontal translation (50)");
    Image transh2 = finger.TranslationH(-50);
    transh2.display("Horizontal translation (-50");
    return 0;
}
