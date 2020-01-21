#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#include "image.h"
#include "gtest/gtest.h"

#include "test_getters.h"
#include "test_difference.h"
#include "test_minmax.h"
#include "test_convolution.h"
#include "test_distmax.h"
#include "test_rectangles.h"
#include "test_binarization.h"
#include "test_equality.h"
#include "test_error.h"


int main(int argc,char *argv[]) {
 ::testing::InitGoogleTest(&argc,argv);
 return RUN_ALL_TESTS();
}
