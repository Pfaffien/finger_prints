#include "optimization.h"

float l_tx(Image f, Image g, int p)
{
    Image h = g.TranslationH(p);
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


float l_txy(Image f, Image g, int px, int py)
{
    Image h = g.TranslationH(px);
    h = h.TranslationV(py);
    return pow(cv::norm(f(), h(), cv::NORM_L2), 2);   
}


void argmin_txy(Image f, Image g, int &px, int &py){
    //initialization of the minimum
    float val_min = l_txy(f, g, 0, 0);
    px = 0;
    py = 0;
    float val;

    for (int ppx = -f().cols/4; ppx < f().cols/4; ppx++){
        for (int ppy = -f().rows/4; ppy < f().rows/4; ppy++){
            val = l_txy(f, g, ppx, ppy);
            if (val < val_min){
                val_min = val;
                px = ppx;
                py = ppy;
            }
        }
    }
}

float l_txyn(Image f, Image g, int px, int py)
{
    Image h = g.TranslationH(px);
    h = h.TranslationV(py);

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

void argmin_txyn(Image f, Image g, int &px, int &py){
    //initialization of the minimum
    float val_min = l_txyn(f, g, 0, 0);
    px = 0;
    py = 0;
    float val;

    for (int ppx = -f().cols/4; ppx < f().cols/4; ppx++){
        for (int ppy = -f().rows/4; ppy < f().rows/4; ppy++){
            val = l_txyn(f, g, ppx, ppy);
            if (val < val_min){
                val_min = val;
                px = ppx;
                py = ppy;
            }
        }
    }
}