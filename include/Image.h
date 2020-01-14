#ifndef _IMAGES_H_
#define _IMAGES_H_

#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <iostream>

#include "main1.h"


class Image{

    private:
        cv::Mat_<float> pixels;

    public:
        //Constructor
        Image(cv::String);
        Image(cv::Mat_<float>);

        //Operator overloading
        float& operator()(int, int);
        cv::Mat_<float> operator()() const;
        Image operator-(const Image &);

        //Functions for min max
        double max();
        double min();

        //Rectangles
        Image rectangle(int, int, unsigned int, unsigned int, float);

        //Symetries
        Image sym_x();
        Image sym_y();
        Image sym_xy();

        //Eventuellement le faire pour une ellipse quelconque
        std::vector<cv::Point> matrix2vector();
        std::vector<cv::Point> outside_ellipse(cv::Point, float, float);

	    //Pressure variation
	    //direction is used to choose if we want black of white
	    Image pressure(cv::Point, std::vector<cv::Point>,  bool iso = false, float param = 50, float param_x = 0.00035, float param_y = 0.000175);//, int direction = 1);

        //Conversion
        cv::Mat_<uchar> from1to255();

        //Plotting and saving
        void display(cv::String windowName = "Display finger_print", cv::String imageName = "Display finger_print");
        void save(std::string s = "finger_print");

};

#endif  /* _IMAGES_H_ */
