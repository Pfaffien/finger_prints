#ifndef _IMAGES_H_
#define _IMAGES_H_

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>


class Image{

    private:
        cv::Mat_<uchar> img;

    public:
        //Constructor
        Image(cv::String);
        Image(cv::Mat);
        Image(Image_float);

        //Functions for min max
        double max();
        double min();

        //Plotting and saving
        void display(cv::String windowName = "Display finger_print", cv::String imageName = "Display finger_print");
        void save(std::string s = "finger_print");
};

class Image_float{

    private:
        cv::Mat_<float> img;

    public:
        //Constructor
        Image_float(cv::String);
        Image_float(cv::Mat);
        Image_float(Image);

        //Operator overloading
        float& operator()(int, int);
        cv::Mat operator()();

        //Rectangles
        Image_float rectangle(int, int, unsigned int, unsigned int, float);

        //Symetries
        Image_float sym_x();
        Image_float sym_y();
        Image_float sym_xy();

}

#endif  /* _IMAGES_H_ */
