#ifndef _TEST_BINARIZATION_H_
#define _TEST_BINARIZATION_H_

#include "image.h"


TEST(binarization, naive)
{
    int size = 5;
    int threshold = size / 2;

    // Naive binarization
    cv::Mat_<float> pixels(size, size, (int) 0);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            pixels(i, j) += (float) (i + j) / 255;
    }
    Image img(pixels);
    Image binarized = img.BinarizeNaive(threshold);

    // Creation of the test matrix
    cv::Mat_<float> test(size, size, (int) 0);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i + j > threshold)
                test(i, j) = 1;
            else
                test(i, j) = 0;
        }
    }

    // Test
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            EXPECT_EQ(binarized(i, j), test(i, j));
    }
}


#endif  /* _TEST_BINARIZATION_H_ */