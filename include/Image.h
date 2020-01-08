#ifndef _IMAGES_H_
#define _IMAGES_H_

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>


class Image{

    private:
        cv::Mat_<float> pixels;

    public:
        //Constructor
        Image(cv::String);
        Image(cv::Mat_<float>);

        //Operator overloading
        float& operator()(int, int);
        cv::Mat_<float> operator()();

        //Functions for min max
        double max();
        double min();

        //Rectangles
        Image rectangle(int, int, unsigned int, unsigned int, float);

        //Symetries
        Image sym_x();
        Image sym_y();
        Image sym_xy();

        //Conversion
        cv::Mat_<uchar> from1to255();

        //Plotting and saving
        void display(cv::String windowName = "Display finger_print", cv::String imageName = "Display finger_print");
        void save(std::string s = "finger_print");

};

#endif  /* _IMAGES_H_ */