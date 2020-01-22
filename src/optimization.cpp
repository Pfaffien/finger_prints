#include "optimization.h"

float l_tx(Image f, Image g, int p)
{
    Image h = g.TranslationH(p);
    return cv::norm(f(), h(), cv::NORM_L2);
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
    return cv::norm(f(), h(), cv::NORM_L2);   
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