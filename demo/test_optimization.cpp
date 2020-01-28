#include "optimization.h"

using namespace std;

int main()
{
    Image finger("../img/clean_finger.png");
    finger.display("Finger");

    //X translation
    Image finger_tx("../img/tx_finger.png");
    finger_tx.display("Finger tx");

    int p = argmin(finger_tx, finger, 0);
    cout << "px =  " << p << endl;

    Image res = finger.Translation(p, 0);
    res.display("Result translation x");

    Image diff = res - finger_tx;
    diff.display("Difference translation x");

    //Clear the windows
    cv::destroyAllWindows();

    //XY translation 
    Image finger_txy("../img/txy_finger.png");
    finger_txy.display("Finger txy");

    int px, py;
    argmin_txy(finger_txy, finger, px, py);
    
    cout << "(p_x, p_y) = (" << px  << ", " << py << ")" << endl;

    res = finger.Translation(px, py);
    res.display("Result translation xy");

    diff = res - finger_txy;
    diff.display("Difference translation xy");


    //Improvements
    double px_d(0), py_d(0);
    improvement_xy(finger_txy, finger, px_d, py_d);
    cout << "(p_x, p_y) = (" << px_d  << ", " << py_d << ")" << endl;

    res = finger.Translation(px_d, py_d);
    res.display("Result translation xy improvement");

    diff = res - finger_txy;
    diff.display("Difference translation xy improvement");
    
    //Clear the windows
    cv::destroyAllWindows();

    //RTXY
    Image rtxy("../img/rtxy_finger.png");
    rtxy.display("rtxy");
    double theta;
    argmin_rtxy(rtxy, finger, px, py, theta);
    cout << "(px, py, theta) = " << "(" << px << ", " << py << ", " << theta << ")" << endl;

    res = finger.Translation(px, py);
    res = res.InverseRotation(theta);
    res.display("Result rtxy");

    diff = res - rtxy;
    diff.display("Difference rtxy");

    /*
    double p = descent_x(finger_tx, finger, 30);
    cout << p << endl;
    Image res = finger.Translation(p, 0);
    res.display("Descent x");
    Image diff = res - finger_tx;
    diff.display("diff");

       
    descent_xy(finger_txy, finger, px, py, -10, 30);
    cout << "(p_x, p_y) = (" << px  << ", " << py << ")" << endl;
    res = finger.Translation(-10, 30);
    res.display("res");
    */

    return 0;
}