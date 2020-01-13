#define PI 3.14159265359
#include <cmath>

#include "main1.h"


float c_isotropic(float r, float param)
{
    return exp(- param * r);
}


/* Je me suis un peu amusé mais c'est pas bon !
 * il faut d'abord réfléchir à ce qu'on prend comme classe de fonctions */
float c_anisotropic(int x, int y, cv::Point center, float param)
{
    return exp(- sqrt(2*pow(x-center.x, 2) + pow(y-center.y, 2)) * param);
    /* return exp(- param * (x + y - center.x - center.y)); */
    /* return 1 / sqrt(param * (x - center.x) + y - center.y); */
};


std::vector<float> pressure(cv::Point center, std::vector<cv::Point> coords, float param, bool iso)
{
    std::vector<float> res;
    int size = coords.size();
    float dist;

    if (iso) {
        for (int i = 0; i < size; i++) {
            dist = cv::norm(center - coords[i]);
	        res.push_back(c_isotropic(dist, param));
        }
    } else {
        for (int i = 0; i < size; i++)
            res.push_back(c_anisotropic(coords[i].x, coords[i].y, center, param));
    }

    return res;
}


std::vector<float> linspace(float begin, float end, int N, bool endpoint)
{
    std::vector<float> res;
    int total_it = N;

    if (endpoint)
        total_it++;

    for (int i = 0; i < total_it; i++)
        res.push_back((i * (end - begin) + begin) / N);

    return res;
}


/* Renvoie la liste des points formant l'ellipse */
/* Utile uniquement pour tracer une ellipse, pas les points en dehors */
/* donc pour du debuggage éventuellement */
std::vector<cv::Point> points_ellipse(cv::Point center, float a, float b)
{
    std::vector<cv::Point> res;
    std::vector<float> lin = linspace(0, 2*PI, 10000);

    for (std::vector<float>::iterator i = lin.begin(); i!= lin.end(); i++)
        res.push_back(cv::Point(int(center.x + a * cos(*i)), int(center.y + b * sin(*i))));

    return res;
}
