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
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/core/types.hpp>
#include "opencv2/highgui/highgui.hpp"

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
        * \param path Image path
        */
        Image(cv::String path);

        /**
        * \brief Constructor
        * \param mat Matrix of pixels
        */
        Image(cv::Mat_<float> mat);

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
        * \param length length of the rectangle
        * \param width width of the rectangle
        * \param color color of the pixels in the rectangle
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

        //Conversion
        /**
        * \brief Conversion of matrix in [0,1] to matrix of [0,255]
        * \return Converted matrix
        */
        cv::Mat_<uchar> from1to255();

        //Plotting and saving
        /**
        * \brief Display the image
        * \param imageName name of the image
        */
        void display(cv::String imageName = "Display finger_print");

        /**
        * \brief save the image in the folder img/saved
        * \param s name of the saved image
        */
        void save(std::string s = "finger_print");

};

#endif  /* _IMAGES_H_ */
