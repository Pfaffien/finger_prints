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
    int vpx(0), vpy(0);
    double val;
    double prec = l(f,g);
    double val_min = 100000;

    for (int i = 0; i < number; i++){
        vpx += argmin(f, tmp, 0);
        vpy += argmin(f, tmp, 1);
        
        val = l(f,g,vpx, vpy);
        if (val == prec) return;
        prec = val;

        if (val < val_min){
            px = vpx;
            py = vpy;
            val_min = val;
        }
        tmp = g.Translation(vpx, vpy);
    }
}


void argmin_rtxy(Image f, Image g, int& px, int& py, double& theta, int number)
{
    px = 0;
    py = 0;
    theta = 0;
    double val_min = 10000000;
    double val;
    double prec = l(f,g);
    int vpx(0), vpy(0);
    double vt;

    Image tmp = Image(g().clone());

    for (int i = 0; i < number; i++){
        vpx += argmin(f, tmp, 0);
        vpy += argmin(f, tmp, 1);
        vt += argmin(f, tmp, 2);

        val = l(f,g,vpx,vpy,vt);
        if (val == prec) return ;
        prec = val;

        if (val < val_min){
            px = vpx;
            py = vpy;
            theta = vt;
            val_min = val;
        }

        tmp = g.InverseRotation(vt);
        tmp = tmp.Translation(vpx, vpy);
    }
}


double improvement(Image f, Image g, int p, int arg)
{
    float val_min = 10000000;
    float val;
    double min = 0;

    switch (arg) {
        case 0:
            for (double i = p-1; i <= p+1; i = i+0.05){
                val = l(f,g,i);
                if (val < val_min){
                    val_min = val;
                    min = i;
                }
            }
            return min;

        case 1:
            for (double i = p-1; i <= p+1; i = i+0.05){
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
    px_d = px;
    py_d = py;

    double vpx(0), vpy(0);
    double val = l(f,g,px,py);
    double prec = val;
    double val_min = val;

    Image gw = g.Translation(px, py);

    for (int i = 0; i < number; i++){
        vpx += improvement(f, gw, px, 0);
        vpy += improvement(f, gw, py, 1);

        val = l(f,g,vpx,vpy);
        if (val == prec) return;
        prec = val;

        if (val < val_min){
            px_d = vpx;
            py_d = vpy;
            val_min = val;
        }

        gw = g.Translation(vpx, vpy);
    }
}


double descent(Image f, Image g, double p0, double alpha, int arg)
{
    double p = p0;
    double p_up, p_down;
    double val, val_up, val_down;
    double al = alpha;
    val = l(f,g);

    if (val < 500) return 0;

    while (al > 0.001) {

        p_up = p*(1+al);
        p_down = p*(1-al);

        switch (arg)
        {
            case 0:
            val_up = l(f, g, p_up);
            val_down = l(f, g, p_down);
        case 1:
            val_up = l(f, g, 0, p_up);
            val_down = l(f, g, 0, p_down);
        case 2:
            val_up = l(f, g, 0, 0, p_up);
            val_down = l(f, g, 0, 0, p_down);
        default:
            val_up = 0;
            val_down = 0;
        }

        if (val_up < val) {
            p = p_up;
            al *= (1+0.1);
            val = val_up;
        } else if (val_down < val){
            p = p_down;
            al *= (1+0.1);
            val = val_down;
        } else al /= 2;

    }
    return p;
}


void descent_xy(Image f, Image g, double& px, double& py, double p0x, double p0y, 
                double alphax, double alphay, int number)
{
    px = p0x;
    py = p0y;
    double val_min = l(f,g,px,py);
    double val;
    double vpx(0), vpy(0);

    Image tmp(g());

    for (int i = 0; i < number; i++){
        vpx = descent(f, tmp, px, alphax, 0);
        vpy = descent(f, tmp, py, alphay, 1);

        tmp = g.Translation(vpx, vpy);

        val = l(f,g,vpx,vpy);

        if (val < val_min){
            px = vpx;
            py = vpy;
            val_min = val;
            alphax /= 2;
            alphay /= 2;
        } else {
            alphax *= 1.1;
            alphay *= 1.1;
        }
    }
}

/*

void descent(Image f, Image g, double& px, double& py, double p0x, double p0y, double alphax, double alphay)
{
    px = p0x;
    py = p0y;
    double val, valuu, valud, valdu, valdd;
    double valxu, valxd, valyu, valyd;
    double pxu, pxd, pyu, pyd;

    val = l(f,g);
    if (val < 500) {
        px = 0;
        py = 0;
        return;
    };

    while (alphax > 0.001 || alphay > 0.001){

        pxu = px*(1+alphax);
        pxd = px*(1-alphax);
        pyu = py*(1+alphay);
        pyd = py*(1-alphay);

        valuu = l(f,g,pxu,pyu);
        valud = l(f,g,pxu,pyd);
        valdu = l(f,g,pxd,pyu);
        valdd = l(f,g,pxd,pyd);
        valxu = l(f,g,pxu,0);
        valxd = l(f,g,pxd,0);
        valyu = l(f,g,0,pyu);
        valyd = l(f,g,0,pyd);

        if (valuu < val) {
            px = pxu;
            py = pyu;
            alphax *= 1.1;
            alphay *= 1.1;
            val = valuu;
        } else if (valud < val) {
            px = pxu;
            py = pyd;
            alphax *= (1+0.1);
            alphay *= 1.1;
            val = valud;
        } else if (valdu < val){
            px = pxd;
            py = pyu;
            alphax *= 1.1;
            alphay *= 1.1;
            val = valdu;
        } else if (valdd < val) {
            px = pxd;
            py = pyd;
            alphax *= 1.1;
            alphay *= 1.1;
            val = valdd;
        } else if (valxu < val) {
            px = pxu;
            alphax *= 1.1;
            alphay /= 2;
            val = valxu;
        } else if (valxd < val) {
            px = pxd;
            alphax *= 1.1;
            alphay /= 2;
            val = valxd;
        } else if (valyu < val) {
            py = pyu;
            alphax /= 2;
            alphay *= 1.1;
            val = valyu;
        } else if (valyd < val) {
            py = pyd;
            alphax /= 2;
            alphay *= 1.1;
            val = valyd;
        } else {
            alphax /= 2;
            alphay /= 2;
        }
    }
}
*/









































/*
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
*/