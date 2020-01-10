#include <iostream>
#include <vector>
#include <cmath>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>

#include "main1.h"


float c(float r, float param)
{
    return exp(- param * r);
}
