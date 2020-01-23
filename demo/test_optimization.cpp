#include "optimization.h"

using namespace std;

int main()
{
    //Images used in the functions
    Image finger("../img/clean_finger.png");
    finger.display("Finger");
    Image finger_tx("../img/tx_finger.png");
    finger_tx.display("Finger tx");
    

    Image trans = finger.Translation(50.5, 0);
    trans.display("Translation");
    trans.BilinearInterpolation();
    trans.display("interpolation");

    //Computation of the argmin for tx
    int p = argmin_n(finger_tx, finger, 0);
    cout << "argmin : " << p << endl;

    Image res = finger.Translation(p, 0);
    res.display("res");
    res.BilinearInterpolation();
    res.display("interpolation");
    
    Image finger_txy("../img/txy_finger.png");
    finger_txy.display("Finger txy");
    int px, py;
    argmin_txy(finger_txy, finger, px, py);
    
    cout << "(p_x, p_y) = (" << px  << ", " << py << ")" << endl;

    Image res2 = finger.Translation(px, py);
    res2.display("res2");
    
    return 0;
}