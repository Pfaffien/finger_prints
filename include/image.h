#ifndef IMAGE_H_
#define IMAGE_H_

/**
 * \file Image.h
 * \brief Definition of the basis of the image
 * \author Thomas B. Clara B. Carole B. Svenja B.
 * \version 0.1
 * \date 01/12/20
 */

#include <iostream>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#include "main1.h"
#include "starter3.h"


/**
 * \class Image
 * \brief class representing an image
 */
class Image{

    private:
        cv::Mat_<float> pixels; //!< Matrix containing the intensity values of each pixel
        int rows;               //!< Number of rows of the pixel matrix
        int cols;               //!< Number of columns of the pixel matrix

    public:
        //Constructors
        /**
        * \brief Constructor from string
        * \param FILENAME is a string representing the path to the image
        */
        Image(cv::String);

        /**
        * \brief Constructor from matrix
        * \param MATRIX pixel matrix representing an image
        */
        Image(const cv::Mat_<float>&);

        //Operator overloading
        /**
        * \brief Getter for the pixel of index (i,j)
        * \param I,J indices of the pixel
        * \return Pixel of index (i,j)
        */
        float& operator()(int i, int j);
        
        /**
        * \brief Convolution with matrix
        * \param FILTER is a matrix to perform the convolution with
        * \return Convolution of this and FILTER
        */
        Image operator*(cv::Mat_<float>);
        /**
        * \brief Convolution with image
        * \param FILTER is an instance of image. The convolution is performed with the pixel matrix of this class.
        * \return Convolution of this and the matrix of FILTER.
        */
        Image operator*(Image);


        /**
        * \brief Getter of the matrix of pixels
        * \return Matrix of pixels
        */
        cv::Mat_<float> operator()() const;

        /**
        * \brief Subtraction of images
        * \param img Image
        * \return this-img
        */
        Image operator-(const Image &);

        //Functions for min max
        /**
        * \brief Maximum
        * \return Maximal intensity value of the image
        */
        double max();

        /**
        * \brief Minimum
        * \return Minimal intensity value of the image
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

        //Eventuellement le faire pour une ellipse quelconque
        std::vector<cv::Point> matrix2vector();
        std::vector<cv::Point> outside_ellipse(cv::Point, float, float);

	    //Pressure variation
	    //direction is used to choose if we want black of white
	    Image pressure(cv::Point, std::vector<cv::Point>,  bool iso = false, float param = 50, float param_x = 0.00035, float param_y = 0.000175);

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
        
        //Scaled Rotation function
        //Image scaled_rotation(double, double, double, double);
        
        //Index shifting
        /**
         * \brief Index change integer to double
         * 
         * This function transforms given pixel indices (i,j) in the range [0,rows-1]x[0,cols-1] to the corresponding double indices (x,y) in [-1,1]x[-a,a] where a is aspect ratio of the image
         * \param[in] I integer index for row (=x-direction)
         * \param[in] J integer index for column (=y-direction)
         * \param[out] X double index for row (=x-direction)
         * \param[out] Y double index for column (=y-direction)
         * 
         * The inverse of this function is given by \ref DoubleToIntIndex.
         * */
        void IntToDoubleIndex(int i, int j, double& x, double& y);
        /**
         * \brief Index change integer to double
         * 
         * This function transforms given indices (x,y) in the range [-1,1]x[-a,a] (a is aspect ratio of the image) to the corresponding integer indices (x,y) in [0,rows-1]x[0,cols-1]. To obtain integers, the values are rounded.
         * It is the inverse function of \ref IntToDoubleIndex.
         * \param[in] X double index for row (=x-direction)
         * \param[in] Y double index for column (=y-direction)
         * \param[out] I integer index for row (=x-direction)
         * \param[out] J integer index for column (=y-direction)
         * */
        void DoubleToIntIndex(double x_prime, double y_prime, int& x, int& y);
        /**
         * \brief Rotate indices
         * 
         * This function rotates given indices (x,y) in the range [-1,1]x[-a,a] (a is aspect ratio of the image) by a factor theta.
         * \param[in] X double index for row (=x-direction)
         * \param[in] Y double index for column (=y-direction)
         * \param[in] THETA rotation factor
         * \param[out] X_PRIME rotated index for row (=x-direction)
         * \param[out] Y_PRIME rotated index for column (=y-direction)
         * */
        void RotateIndices(double x, double y, double theta, double& x_prime, double& y_prime);
        
        //Pure rotation function
        /**
         * \brief Rotate image
         * 
         * This function rotates an image by a factor theta. It therefore performs some index transformations and then the actual rotation. 
         * \param[in] THETA rotation factor
         * */
        Image Rotation(double theta);
        //Pure interpolation
        /**
         * \brief Bi-linear interpolation
         * 
         * This function performs bi-linear interpolation for all pixels that have the value 1. It is used to improve the result of \ref Rotation where pixels that could not be assigned to an intensity value got the default value 1.
         * */
        void BilinearInterpolation();
        
        //Combined rotation and interpolation
        /**
         * \brief Improved rotation method
         * 
         * This function combines rotation and interpolation in such a way that no rounding of indices is performed anymore (in contrast to the combination of \ref Rotation and \ref BilinearInterpolation). Another difference is that we are looping over the pixels in the rotated target image instead of the pixels in the original image. Therefore we are perforing a backward rotation of the factor 2*PI-THETA to get the intensity values for our result pixels.
         * \param[in] THETA is the rotation factor
         * */
        Image InverseRotation(double theta);
        //Image DifferenceMatrix(Image second);
};

#endif  // IMAGES_H_ 
