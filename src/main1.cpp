#include "main1.h"

float c_isotropic(float r, float param, int func)
{
    switch (func) {
        case 0:
            return 1 - exp(- param / pow(r, 16));
            break;
        case 1:
            return exp(- param * r);
            break;
        case 2:
            return 1 / (1 + param * r);
            break;
        default:
            return 1 - exp(- param / pow(r, 16));;
    }
}


float c_anisotropic(int x, int y, cv::Point center, float param_x, float param_y, float param)
{
    return 1-exp(-param/pow(param_x*pow(x-center.x, 2) + param_y*pow(y-center.y, 2), 8));
};


std::vector<float> coeffs(cv::Point center, std::vector<cv::Point> coords, float param_x, float param_y, float param, bool iso)
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
            res.push_back(c_anisotropic(coords[i].x, coords[i].y, center, param_x, param_y, param));
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
