#ifndef _TEST_DISTMAX_H_
#define _TEST_DISTMAX_H_

#include <iostream>
#include <cmath>
#include <opencv2/core/types.hpp>

#include "starter3.h"
#include "gtest/gtest.h"


TEST(distmax, max)
{
    cv::Mat_<float> mat(4, 9, (int) 0);
    cv::Point center(1, 0);
    cv::Point furthest(4, 8);
    
    double dist = cv::norm(center - furthest);
    double estimated_dist = distance_max(mat, center.x, center.y);

    EXPECT_DOUBLE_EQ(estimated_dist, dist);
}


#endif  /* _TEST_DISTMAX_H_ */
