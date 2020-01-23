#include "optimization.h"

float l(Image f, Image g, int px, int py)
{
    Image gw = g.Translation(px, py);

    return pow(cv::norm(f(), gw(), cv::NORM_L2), 2);
}

int argmin(Image f, Image g, int arg)
{
    float val_min = 10000000;
    float val;
    int min = 0;

    switch (arg) {
        case 0:
            for (int p = -f().cols; p < f().cols; p++){
                val = l(f,g,p);
                if (val < val_min){
                    val_min = val;
                    min = p;
                }
            }
            return min;

        case 1:
            for (int p = -f().rows; p < f().rows; p++){
                val = l(f,g,0,p);
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


void argmin_txy(Image f, Image g, int &px, int &py, int number){
    px = 0;
    py = 0;
    Image tmp = Image(g());
    float val = 0;
    bool stop = false;

    for (int i = 0; i < number; i++){
        val = argmin(f, tmp, 0);
        std::cout << val << std::endl;
        if (val != 0) px += val;
        else stop = true;
        tmp = tmp.Translation(val, 0);

        val = argmin(f, tmp, 1);
        std::cout << val << std::endl << std::endl;
        if (val != 0) py += val;
        else if (stop) return;
        tmp = tmp.Translation(0, val);

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
            for (int p = -f().cols; p < f().cols; p++){
                val = l_n(f,g,p);
                if (val < val_min){
                    val_min = val;
                    min = p;
                }
            }
            return min;

        case 1:
            for (int p = -f().rows; p < f().rows; p++){
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
    float val = 0;
    bool stop = false;

    for (int i = 0; i < number; i++){
        val = argmin_n(f, tmp, 0);
        std::cout << val << std::endl;
        if (val != 0) px += val;
        else stop = true;
        tmp = tmp.Translation(val, 0);

        val = argmin_n(f, tmp, 1);
        std::cout << val << std::endl << std::endl;
        if (val != 0) py += val;
        else if (stop) return;
        tmp = tmp.Translation(0, val);

    }
}