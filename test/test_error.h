#ifndef _TEST_ERROR_H
#define _TEST_ERROR_H

#include "gtest/gtest.h"
#include "image.h"

TEST(error, easy)
{
	//Initialization of images
	cv::Mat_<float> mat1(5,5,1);
	Image im1(mat1);
	cv::Mat_<float> mat2(5,5,int(0));
	Image im2(mat2);
	cv::Mat_<float> mat3 = mat1.clone();
	mat3(1,1) = 0;
	Image im3(mat3);

	//tests
	float res1 = im1.error(im1, 0.01);
	EXPECT_FLOAT_EQ(res1, 0);

	float res2 = im1.error(im2, 0.01);
	EXPECT_FLOAT_EQ(res2, 1);

	float res3 = im1.error(im2,1);
	EXPECT_FLOAT_EQ(res3, 0); 
	
	float res4 = im1.error(im3, 0.1);
	EXPECT_FLOAT_EQ(res4, 1./(5*5));
}


#endif
