/**
 * \file main_tests.cpp
 * \brief main function to perform all google tests
 */


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
