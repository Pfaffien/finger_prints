#ifndef _TEST_DISTMAX_H_
#define _TEST_DISTMAX_H_

#include <iostream>
#include <cmath>
#include <opencv2/core/types.hpp>

#include "linear_filtering.h"
#include "gtest/gtest.h"


TEST(distmax, max)
{
    cv::Mat_<float> mat(4, 4, (int) 0);
    cv::Point center(0, 0);
    cv::Point furthest(3, 3);
    
    float dist = cv::norm(center - furthest);
    float estimated_dist = distance_max(mat, center.x, center.y);

    EXPECT_FLOAT_EQ(estimated_dist, dist);
}


#endif  /* _TEST_DISTMAX_H_ */
