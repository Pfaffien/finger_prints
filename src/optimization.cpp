#include "optimization.h"

float l_tx(Image f, Image g, int p)
{
    Image h = g.TranslationH(p);
    float res(0);
    for (int i = 0; i < f().rows; i++){
        for (int j = 0; j < f().cols; j++){
            res += pow(f(i,j)-h(i,j), 2);
        }
    }

    return res;
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

    float res(0);
    for (int i = 0; i < f().rows; i++){
        for (int j = 0; j < f().cols; j++){
            res += pow(f(i,j)-h(i,j), 2);
        }
    }

    return res;   
}


void argmin_txy(Image f, Image g, int & px, int & py){
    //initialization of the minimum
    float val_min = l_txy(f, g, 0, 0);
    px = 0;
    py = 0;
    float val;

    for (int ppx = -f().cols; ppx < f().cols; ppx++){
        for (int ppy = -f().rows; ppy < f().rows; ppy++){
            val = l_txy(f, g, ppx, ppy);
            if (val < val_min){
                val_min = val;
                px = ppx;
                py = ppy;
            }
        }
    }
}