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
    res.save("tx");

    Image diff = res - finger_tx;
    diff.display("Difference translation x");
    diff.save("diff_tx");

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
    res.save("txy");

    diff = res - finger_txy;
    diff.display("Difference translation xy");
    diff.save("diff_txy");


    // //Improvements
    double px_d(0), py_d(0);
    improvement_xy(finger_txy, finger, px_d, py_d);
    cout << "(p_x, p_y) = (" << px_d  << ", " << py_d << ")" << endl;

    res = finger.Translation(px_d, py_d);
    res.display("Result translation xy improvement");
    res.save("imp_txy");

    diff = res - finger_txy;
    diff.display("Difference translation xy improvement");
    diff.save("diff_imp_txy");
    
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
    res.save("rtxy");

    diff = res - rtxy;
    diff.display("Difference rtxy");
    diff.save("diff_rtxy");

    //Clear the windows
    cv::destroyAllWindows();
    
    p = descent_x(finger_tx, finger, 10, 0.8);
    cout << p << endl;
    res = finger.Translation(p, 0);
    res.display("Descent x");
    res.save("grad_x");

    diff = res - finger_tx;
    diff.display("Difference descent x");
    diff.save("diff_grad_x");
 
    //Clear the windows
    cv::destroyAllWindows();
 
    finger_txy.display("txy");
    descent(finger_txy, finger, px_d, py_d, 5, -25, 0.5, 0.5);
    cout << "(p_x, p_y) = (" << px_d  << ", " << py_d << ")" << endl;
    res = finger.Translation(px_d, py_d);

    res.display("res");
    res.save("grad_xy");    

    return 0;
}