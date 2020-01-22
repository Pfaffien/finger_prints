#include "optimization.h"

float l_tx(Image f, Image g, int p)
{
    Image h = g.Translation(p, 0);
    return pow(cv::norm(f(), h(), cv::NORM_L2), 2);
}


int argmin_tx(Image f, Image g){
    //initialization of the minimum
    int min(0);
    float val_min = l_tx(f, g, 0);
    float val;

    for (int p = -f().cols; p < f().cols; p++){
        val = l_tx(f, g, p);
        if (val < val_min) {
            val_min = val;
            min = p;
        }
    }

    return min;
}

float l_ty(Image f, Image g, int p)
{
    Image h = g.Translation(0, p);
    return pow(cv::norm(f(), h(), cv::NORM_L2), 2);
}


int argmin_ty(Image f, Image g){
    //initialization of the minimum
    int min(0);
    float val_min = l_ty(f, g, 0);
    float val;

    for (int p = -f().rows; p < f().rows; p++){
        val = l_ty(f, g, p);
        if (val < val_min) {
            val_min = val;
            min = p;
        }
    }

    return min;
}


float l_txy(Image f, Image g, int px, int py)
{
    Image h = g.Translation(px, py);
    return pow(cv::norm(f(), h(), cv::NORM_L2), 2);   
}


void argmin_txy(Image f, Image g, int &px, int &py, int number){
    px = 0;
    py = 0;
    Image tmp = Image(g());
    float val = 0;
    bool arret = false;

    for (int i = 0; i < number; i++){
        val = argmin_tx(f, tmp);
        std::cout << val << std::endl;
        if (val != 0) px += val;
        else arret = true;
        tmp = tmp.Translation(val, 0);

        val = argmin_ty(f, tmp);
        std::cout << val << std::endl << std::endl;
        if (val != 0) py += val;
        else if (arret) return;
        tmp = tmp.Translation(0, val);

    }
}

float l_txn(Image f, Image g, int p)
{
    Image h = g.Translation(p, 0);

    float mean_f = f.mean();
    float mean_gw = h.mean();

    float num = 0;
    float denom1 = 0;
    float denom2 = 0;

    for (int i = 0; i < f().rows; i++){
        for (int j = 0; j < f().cols; j++){
            num += (f(i,j) - mean_f)*(h(i,j) - mean_gw);
            denom1 += pow(f(i,j) - mean_f, 2);
            denom2 += pow(h(i,j) - mean_gw, 2);
        }
    }
    return num/sqrt(denom1*denom2);
}


float l_tyn(Image f, Image g, int p)
{
    Image h = g.Translation(0, p);

    float mean_f = f.mean();
    float mean_gw = h.mean();

    float num = 0;
    float denom1 = 0;
    float denom2 = 0;

    for (int i = 0; i < f().rows; i++){
        for (int j = 0; j < f().cols; j++){
            num += (f(i,j) - mean_f)*(h(i,j) - mean_gw);
            denom1 += pow(f(i,j) - mean_f, 2);
            denom2 += pow(h(i,j) - mean_gw, 2);
        }
    }
    return num/sqrt(denom1*denom2);
}

int argmin_txn(Image f, Image g){
    //initialization of the minimum
    int min(0);
    float val_min = l_txn(f, g, 0);
    float val;

    for (int p = -f().cols; p < f().cols; p++){
        val = l_txn(f, g, p);
        if (val < val_min) {
            val_min = val;
            min = p;
        }
    }

    return min;
}


int argmin_tyn(Image f, Image g){
    //initialization of the minimum
    int min(0);
    float val_min = l_tyn(f, g, 0);
    float val;

    for (int p = -f().rows; p < f().rows; p++){
        val = l_tyn(f, g, p);
        if (val < val_min) {
            val_min = val;
            min = p;
        }
    }

    return min;
}

void argmin_txyn(Image f, Image g, int &px, int &py, int number){
    px = 0;
    py = 0;
    Image tmp = Image(g());
    float val = 0;

    for (int i = 0; i < number; i++){
        val = argmin_txn(f, tmp);
        if (val != 0) px += val;
        std::cout << val << std::endl;
        tmp = tmp.Translation(val, 0);

        val = argmin_tyn(f, tmp);
        if (val != 0) py += val;
        std::cout << val << std::endl << std::endl;
        tmp = tmp.Translation(0, val);

    }
}