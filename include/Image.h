#ifndef _IMAGES_H_
#define _IMAGES_H_

/**
 * \file Image.h
 * \brief Definition of the basis of the image
 * \author Thomas.B Clara.B Carole.B Svenja.B
 * \version 0.1
 * \date 01/12/20
 */


#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <iostream>

#include "main1.h"


/**
 * \class Image
 * \brief class representing an image
 */
class Image{

    private:
        cv::Mat_<float> pixels; /** Matrix of the pixels of the image */

    public:
        //Constructors
        /**
        * \brief Constructor
        * \param Image path
        */
        Image(cv::String);

        /**
        * \brief Constructor
        * \param Matrix of pixels
        */
        Image(cv::Mat_<float>);

        //Operator overloading
        /**
        * \brief Getter of the pixel of index (i,j)
        * \param i,j indices of the pixel
        * \return Pixel of index (i,j)
        */
        float& operator()(int i, int j);

        /**
        * \brief Getter of the matrix of pixels
        * \return Matrix of pixels
        */
        cv::Mat_<float> operator()() const;

        /**
        * \brief Soustraction of images
        * \param img Image
        * \return this-img
        */
        Image operator-(const Image & img);

        //Functions for min max
        /**
        * \brief Maximum
        * \return Maximum of the image
        */
        double max();

        /**
        * \brief Minimum
        * \return Minimum of the image
        */
        double min();

        //Rectangles
        /**
        * \brief Change the value of the pixels in a rectangle
        * \param x, y coordinates of the upper left point of the rectangle
          length length of the rectangle
          width width of the rectangle
          color color of the pixels in the rectangle
        * \return Image with the modified pixels
        */
        Image rectangle(int x, int y, unsigned int length, unsigned int width, float color);

        //Symetries
        /**
        * \brief Symmetry along axis x
        * \return Symmetrized image
        */
        Image sym_x();

        /**
        * \brief Symmetry along axis y
        * \return Symmetrized image
        */
        Image sym_y();

        /**
        * \brief Symmetry along axis x and y
        * \return Symmetrized image
        */
        Image sym_xy();

        //Eventuellement le faire pour une ellipse quelconque
        std::vector<cv::Point> matrix2vector();
        std::vector<cv::Point> outside_ellipse(cv::Point, float, float);

	    //Pressure variation
	    //direction is used to choose if we want black of white
	    Image pressure(cv::Point, std::vector<cv::Point>,  bool iso = false, float param = 50, float param_x = 0.00035, float param_y = 0.000175);//, int direction = 1);

        //Conversion
        /**
        * \brief Conversion of matrix in [0,1] to matrix of [0,255]
        * \return Converted matrix
        */
        cv::Mat_<uchar> from1to255();

        //Plotting and saving
        /**
        * \brief Display the image
        * \param windowname name of the window
          imageName name of the image
        */
        void display(cv::String windowName = "Display finger_print", cv::String imageName = "Display finger_print");

        /**
        * \brief save the image in the folder img/saved
        * \param s name of the saved image
        */
        void save(std::string s = "finger_print");

};

#endif  /* _IMAGES_H_ */
