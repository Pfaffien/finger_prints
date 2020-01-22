#include "optimization.h"

using namespace std;

int main()
{
    //Images used in the functions
    Image finger("../img/clean_finger.png");
    finger.display("Finger");
    Image finger_tx("../img/tx_finger.png");
    //finger_tx.display("Finger tx");
    Image finger_txy("../img/txy_finger.png");
    finger_txy.display("Finger txy");


    //Computation of the argmin for tx
    int p = argmin_tx(finger_tx, finger);
    cout << "argmin : " << p << endl;

    Image res = finger.TranslationH(p);
    res.display("res");

    
    int px(0), py(0);
    argmin_txy(finger_txy, finger, px, py);
    
    cout << px << endl;
    cout << py << endl;

    Image res2 = finger.TranslationH(px);
    res2 = res2.TranslationV(py);
    res2.display("res2");


    return 0;
}