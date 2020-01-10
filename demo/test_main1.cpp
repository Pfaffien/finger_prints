#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>

#include "Image.h"
#include "main1.h"

int main()
{
    Image finger("../img/clean_finger.png");
    finger.display("Finger", "Finger");

    int dist = 100;
    cv::Point center(finger().rows/2, finger().cols/2);
    cv::Point tmp((int) 0, (int) 0);
    std::vector<cv::Point> coords;
    
    for (int i = 0; i < finger().rows; i++) {
	tmp.x = i;
    	for (int j = 0; j < finger().cols; j++) {
	    tmp.y = j;
	    if (cv::norm(center - tmp) > dist)
                coords.push_back(tmp);
	}
    }

    Image res = finger.pressure_change(center, coords);
    res.display("Result", "Result");

    return 0;
}
