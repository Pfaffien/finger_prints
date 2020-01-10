#include <cmath>

#include "main1.h"


float c(float r, float param)
{
    return exp(- param * r);
}


std::vector<float> pressure(cv::Point center, std::vector<cv::Point> coords, float param)
{
    std::vector<float> res;
    int size = coords.size();
    float dist;

    for(int i = 0; i < size; i++) {
        dist = cv::norm(center - coords[i]);
	res.push_back(c(dist, param));
    }

    return res;
}
