#include "optimization.h"

float l(Image f, Image g, int px, int py, double theta)
{
    Image gw = g.Translation(px, py);
    if (theta != 0) gw = gw.InverseRotation(theta);
    return pow(cv::norm(f(), gw(), cv::NORM_L2), 2);
}


double argmin(Image f, Image g, int arg)
{
    float val_min = 10000000;
    float val;
    int min = 0;

    switch (arg) {
        case 0:
            for (int p = -f().cols/2; p < f().cols/2; p++){
                val = l(f,g,p,0,0);
                if (val < val_min){
                    val_min = val;
                    min = p;
                }
            }
            return min;

        case 1:
            for (int p = -f().rows/2; p < f().rows/2; p++){
                val = l(f,g,0,p,0);
                if (val < val_min){
                    val_min = val;
                    min = p;
                }
            }
            return min;
        
        case 2:
            double theta_m;
            for (double t = -3.1; t < 3.1; t = t+0.1) {
                val = l(f,g,0,0,t);
                if (val < val_min){
                    val_min = val;
                    theta_m = t;
                }
            }
            return theta_m;

        default:
            return 0;
    }
}


void argmin_txy(Image f, Image g, int &px, int &py, int number){
    px = 0;
    py = 0;
    Image tmp = Image(g());
    int val = 0;
    bool stop = false;

    for (int i = 0; i < number; i++){
        val = argmin(f, tmp, 0);
        if (val != 0) {
            px += val;
            tmp = tmp.Translation(val, 0);
        }
        else stop = true;

        val = argmin(f, tmp, 1);
        if (val != 0) {
            py += val;
            tmp = tmp.Translation(0, val);
        }
        else if (stop) return;
    }
}


void argmin_rtxy(Image f, Image g, int& px, int& py, double& theta, int number)
{
    px = 0;
    py = 0;
    theta = 0;
    int val_p;
    double val_t;
    int stop = 0;

    Image tmp = Image(g().clone());

    for (int i = 0; i < number; i++){
        val_t = argmin(f, tmp, 2);
        if (abs(val_t) > 0.001){
            theta += val_t;
            tmp = tmp.InverseRotation(val_t);
        }
        else stop = 1;

        val_p = argmin(f, tmp, 0);
        if (val_p != 0) {
            px += val_p;
            tmp = tmp.Translation(val_p, 0);

        }
        else stop += 1;

        val_p = argmin(f, tmp, 1);
        if (val_p != 0) {
            py += val_p;
            tmp = tmp.Translation(0, val_p);
        }
        else if (stop == 2) return;
        stop = 0;
    }
}


double improvement(Image f, Image g, int p, int arg)
{
    float val_min = 10000000;
    float val;
    double min = 0;

    switch (arg) {
        case 0:
            for (double i = p-1; i < p+1; i = i + 0.1){
                val = l(f,g,i);
                if (val < val_min){
                    val_min = val;
                    min = i;
                }
            }
            return min;

        case 1:
            for (double i = p-1; i < p+1; i = i+0.1){
                val = l(f,g,0,i);
               
                if (val < val_min){
                    val_min = val;
                    min = i;
                }
            }
            return min;
        
        default:
            return 0;
            
    }
}


void improvement_xy(Image f, Image g, double &px_d, double &py_d, int number)
{
    //initialization of px and py
    int px(0), py(0);
    argmin_txy(f, g, px, py);

    Image gw = g.Translation(px, py);
    float val = 0;
    bool stop = false;

    for (int i = 0; i < number; i++){
        val = improvement(f, gw, px, 0);
        if (val != px_d) {
            px_d = val;
            gw = gw.Translation(val, 0);
        }
        else stop = true;

        val = improvement(f, gw, py, 1);
        if (val != py_d) {
            py_d = val;
            gw = gw.Translation(0, val);
        }
        else if (stop) return;
    }
}


double descent_x(Image f, Image g, double p0, double alpha)
{
    double p = p0;
    double p_up, p_down;
    double val, val_up, val_down;
    val = l(f,g);

    while (alpha > 0.001) {

        p_up = p*(1+alpha);
        p_down = p*(1-alpha);

        val_up = l(f, g, p_up);
        val_down = l(f, g, p_down);

        if (val_up < val) {
            p = p_up;
            alpha *= (1+0.1);
            val = val_up;
        } else if (val_down < val){
            p = p_down;
            alpha *= (1+0.1);
            val = val_down;
        } else alpha /= 2;

    }

    return p;
}

double descent_y(Image f, Image g, double p0, double alpha)
{
    double p = p0;
    double p_up, p_down;
    double val, val_up, val_down;
    val = l(f,g);

    while (alpha > 0.001) {

        p_up = p*(1+alpha);
        p_down = p*(1-alpha);

        val_up = l(f, g, 0, p_up);
        val_down = l(f, g, 0, p_down);

        if (val_up < val) {
            p = p_up;
            alpha *= (1+0.1);
            val = val_up;
        } else if (val_down < val){
            p = p_down;
            alpha *= (1+0.1);
            val = val_down;
        } else alpha /= 2;

    }

    return p;
}

void descent_xy(Image f, Image g, double &px, double &py, double p0x, double p0y, 
                double alphax, double alphay, int number)
{
    px = 0;
    py = 0;
    double val;
    Image tmp(g());

    for (int i = 0; i < number; i++){
        val = descent_x(f, tmp, p0x, alphax);
        px = val;
        std::cout << val << std::endl;
        tmp = tmp.Translation(val, 0);
        tmp.display("bla");
        val = descent_y(f, tmp, p0y, alphay);
        py = val;
        tmp = tmp.Translation(0, val);
        std::cout << val << std::endl;
        tmp.display("bla");
    }
}




















































































//il y a surement un problème avec cette fonction
float l_n(Image f, Image g, int px, int py)
{
    Image gw = g.Translation(px, py);

    float mean_f = f.mean();
    float mean_gw = gw.mean();

    float num = 0;
    float denom1 = 0;
    float denom2 = 0;

    for (int i = 0; i < f().rows; i++){
        for (int j = 0; j < f().cols; j++){
            num += (f(i,j) - mean_f)*(gw(i,j) - mean_gw);
            denom1 += pow(f(i,j) - mean_f, 2);
            denom2 += pow(gw(i,j) - mean_gw, 2);
        }
    }
    return num/sqrt(denom1*denom2);
}

int argmin_n(Image f, Image g, int arg)
{
    float val_min = 10000000;
    float val;
    int min = 0;

    switch (arg) {
        case 0:
            for (int p = -f().cols/2; p < f().cols/2; p++){
                val = l_n(f,g,p);
                if (val < val_min){
                    val_min = val;
                    min = p;
                }
            }
            return min;

        case 1:
            for (int p = -f().rows/2; p < f().rows/2; p++){
                val = l_n(f,g,0,p);
               
                if (val < val_min){
                    val_min = val;
                    min = p;
                }
            }
            return min;
        
        default:
            return 0;
            
    }
}


void argmin_txy_n(Image f, Image g, int &px, int &py, int number){
    px = 0;
    py = 0;
    Image tmp = Image(g());
    int val = 0;
    bool stop = false;

    for (int i = 0; i < number; i++){
        val = argmin_n(f, tmp, 0);
        if (val != 0) px += val;
        else stop = true;
        tmp = tmp.Translation(val, 0);

        val = argmin_n(f, tmp, 1);
        if (val != 0) py += val;
        else if (stop) return;
        tmp = tmp.Translation(0, val);

    }
}

