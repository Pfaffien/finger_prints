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
    int p = argmin(finger_tx, finger, 0);
    cout << "argmin : " << p << endl;

    Image res = finger.Translation(p, 0);
    res.display("res");
    
    Image finger_txy("../img/txy_finger.png");
    finger_txy.display("Finger txy");
    int px, py;
    argmin_txy(finger_txy, finger, px, py);
    
    cout << px << endl;
    cout << py << endl;

    Image res2 = finger.Translation(px, py);
    res2.display("res2");

    return 0;
}