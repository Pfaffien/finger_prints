#include "optimization.h"

using namespace std;

int main()
{
    //Images used in the functions
    Image finger("../img/clean_finger.png");
    finger.display("Finger");
    Image finger_tx("../img/tx_finger.png");
    finger_tx.display("Finger tx");

    //Computation of the argmin for tx
    int p = argmin_tx(finger_tx, finger);
    cout << "argmin : " << p << endl;

    Image res = finger.TranslationH(p);
    res.display("res");

    Image diff = finger_tx - res;
    diff.display("diff");

    float err = finger_tx.error(res, 0.0001);
    cout << "error : " << 100*err << "%" << endl;



    return 0;
}