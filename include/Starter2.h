#ifndef _STARTER2_H_
#define _STARTER2_H_

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>


/*! \class Image
    \brief Class representing an image

    This class represents an image. It contains a cv::Matrix containing the intensity values of the image. Furthermore it supplies diffferent methods to transform, display or save the image.
    The class only works for grey level images.
*/


class Image{

    private:
        cv::Mat_<float> pixels;             //!< Matrix containing the intensity values of the image
        int rows, cols;                     //!< Number of rows and columns of image matrix
        
    public:
        //Constructor
        Image(cv::String);                  //!< Construct image from given string
        Image(cv::Mat_<float>);             //!< Construct image from given matrix

        //Operator overloading
        float& operator()(int, int);        //!< Get pixel value of image matrix
        cv::Mat_<float> operator()();       //!< Get the whole image matrix

        //Functions for min max
        double Max();                       //!< Get maximal intensity value of image matrix
        double Min();                       //!< Get minimal intensity value of image matrix

        //Rectangles
        Image Rectangle(int, int, unsigned int, unsigned int, float);

        //Symetries
        Image Sym_x();
        Image Sym_y();
        Image Sym_xy();

        //Intensity value conversion
        cv::Mat_<uchar> From1to255();       //!< Transform intensity values from range [0,255] to [0,1]

        //Plotting and saving
        void Display(cv::String windowName = "Display finger_print", cv::String imageName = "Display finger_print");
        void Save(std::string s = "finger_print");

        //Scaled Rotation function
        //Image scaled_rotation(double, double, double, double);
        void IntToDoubleIndex(int i, int j, double& x, double& y);
        void DoubleToIntIndex(double x_prime, double y_prime, int& x, int& y);
        void RotateIndices(double x, double y, double theta, double& x_prime, double& y_prime);
        Image Rotation(double theta);
        void BilinearInterpolation();
        Image BackwardInterpolation(double theta);
        Image DifferenceMatrix(Image second);
};

#endif  /* _IMAGES_H_ */
