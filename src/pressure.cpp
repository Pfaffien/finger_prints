#include "pressure.h"


void cartesian_to_polar(cv::Point origin, cv::Point pt, float &r, float &theta)
{
    cv::Point diff = pt - origin;
    r = cv::norm(diff);
    //cf. function atan2
    theta = atan2(diff.y, diff.x);
}

 
/*
 * Réfléchir à comment inclure un angle dans la définition
 * et choisir de l'appliquer seulement aux pixels dans une direction
 * donnée, et utiliser un tirage aléatoire de points dépendant du
 * tirage précédent 
 */
float c_isotropic(float r, float param, int func)
{
    switch (func) {
        case 0:
            return 1 - exp(- 1 / (param * pow(r, 2)));
        case 1:
            return exp(- param * r);
        case 2:
            return 1 / (1 + param * r);
        default:
            return 1 - exp(- 1 / (param* pow(r, 2)));;
    }
}


float c_anisotropic(int x, int y, cv::Point center, float param_x, 
                    float param_y, float param)
{
    return 1-exp(-param/pow(param_x*pow(x-center.x, 2) + param_y*pow(y-center.y, 2), 8));
}


float c_anisotropic_polar(float r, float theta, cv::Point center,
                          float param_x, float param_y, float param)
{
    return 1-exp(-param/pow(param_x*pow(r * cos(theta), 2) + param_y*pow(r * sin(theta), 2), 8));
}


std::vector<float> coeffs(cv::Point center, std::vector<cv::Point> coords,
                          float param_x, float param_y, float param, bool iso)
{
    std::vector<float> res;
    int size = coords.size();
    float dist;

    //Utiliser la fonction c_anisotropic aussi vu qu'elle permet d'avoir un résultat isotrope
    if (iso) {
        for (int i = 0; i < size; i++) {
            dist = cv::norm(center - coords[i]);
	        res.push_back(c_isotropic(dist, param));
        }
    } else {
        for (int i = 0; i < size; i++)
            res.push_back(c_anisotropic(coords[i].x, coords[i].y, center, param_x, param_y, param));
    }

    return res;
}


std::vector<float> coeffs_polar(cv::Point center, std::vector<cv::Point> coords,
                          float param_x, float param_y, float param, float param_rot, bool iso)
{
    std::vector<float> res;
    int size = coords.size();
    float dist;

    //Utiliser la fonction c_anisotropic aussi vu qu'elle permet d'avoir un résultat isotrope
    if (iso) {
        for (int i = 0; i < size; i++) {
            dist = cv::norm(center - coords[i]);
	        res.push_back(c_isotropic(dist, param));
        }
    } else {
        float r, theta;
        for (int i = 0; i < size; i++) {
            cv::Point rotated(int(cos(param_rot) * coords[i].x - sin(param_rot) * coords[i].y),
                              int(sin(param_rot) * coords[i].x + cos(param_rot) * coords[i].y));
            cartesian_to_polar(center, rotated, r, theta);

            if (-PI/8 <= theta && theta <= 0)
                res.push_back(c_anisotropic_polar(r, theta, center, 1.5*param_x, param_y, 5*param));
            else
                res.push_back(c_anisotropic_polar(r, theta, center, param_x, param_y, param));
        }
    }

    return res;
}


std::vector<float> linspace(float begin, float end, int N, bool endpoint)
{
    std::vector<float> res;
    int total_it = N;

    if (endpoint) total_it++;

    for (int i = 0; i < total_it; i++)
        res.push_back((i * (end - begin) + begin)/N);

    return res;
}


std::vector<cv::Point> points_ellipse(cv::Point center, float a, float b)
{
    std::vector<cv::Point> res;
    std::vector<float> lin = linspace(0, 2*PI, 10000);

    for (std::vector<float>::iterator i = lin.begin(); i != lin.end(); i++)
        res.push_back(cv::Point(int(center.x + a * cos(*i)), int(center.y + b * sin(*i))));

    return res;
}
