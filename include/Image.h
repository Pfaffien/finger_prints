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

        //Functions for min max
        double max();
        double min();

        //Plotting and saving
        void display();
        void save(std::string s = "finger_print");

        //Symmetries
        Image sym_x();
        Image sym_y();
        Image sym_xy();

        //Change intensity intervals
        void OneTo255();
        void From255ToOne();

        //Operator overloading
        uchar& operator()(int, int);
        cv::Mat operator()();

        //Rectangles
        Image rectangle(int, int, unsigned int, unsigned int, float);
};


#endif  /* _IMAGES_H_ */
