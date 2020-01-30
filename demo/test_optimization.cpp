#include "optimization.h"

using namespace std;

int main()
{
    Image finger("../img/clean_finger.png");
    Image finger_tx("../img/tx_finger.png");
    Image finger_txy("../img/txy_finger.png");
    Image rtxy("../img/rtxy_finger.png");


    //X translation
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

/*
    //XY translation 
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

    //Clear the windows
    cv::destroyAllWindows();   


    //Improvements
    finger_txy.display("txy");

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
    rtxy.display("rtxy");

    double theta;
    argmin_rtxy(rtxy, finger, px, py, theta, 15);
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
    

    //Coordinate descent x
    finger_tx.display("tx");

    double pp;
    pp = descent(finger_tx, finger, 10, 0.8, 0);
    cout << pp << endl;

    res = finger.Translation(pp, 0);
    res.display("Descent x");
    res.save("grad_x");

    diff = res - finger_tx;
    diff.display("Difference descent x");
    diff.save("diff_grad_x");
 
    //Clear the windows
    cv::destroyAllWindows();
    
*/
    //Coordinate descent xy
    finger_txy.display("txy");

    double px_d, py_d;
    descent_xy(finger_txy, finger, px_d, py_d, 10, -20, 0.2, 0.2);
    cout << "(p_x, p_y) = (" << px_d  << ", " << py_d << ")" << endl;
    
    res = finger.Translation(px_d, py_d);
    res.display("res");
    res.save("grad_xy");   

    diff = res - finger_txy;
    diff.display("Difference descent xy");
    diff.save("diff_grad_xy");


    return 0;
}