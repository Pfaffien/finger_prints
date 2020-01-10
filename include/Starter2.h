#ifndef _STARTER2_H_
#define _STARTER2_H_

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>


class Image{

    private:
        cv::Mat_<float> pixels;
        // \TODO int rows, cols; ?

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

        //Scaled Rotation function
        //Image scaled_rotation(double, double, double, double);
        void IntToDoubleIndex(int i, int j, double& x, double& y);
        void DoubleToIntIndex(double x_prime, double y_prime, int& x, int& y);
        void rotate_indices(double x, double y, double theta, double& x_prime, double& y_prime);
        Image rotate(double theta);
};

#endif  /* _IMAGES_H_ */
