#ifndef IMAGE_H_
#define IMAGE_H_

/**
 * \file image.h
 * \brief Definition of the basis of the image
 * \author Thomas B. Clara B. Carole B. Svenja B.
 * \version 0.1
 * \date 01/12/20
 */

#include <iostream>
#include <vector>
#include <cmath>

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
        //CONSTRUCTORS
        
        /**
        * \brief Constructor from string
        * \param filename is a string representing the path to the image
        */
        Image(cv::String filename);

        /**
        * \brief Constructor from matrix
        * \param  pixel matrix representing an image
        */
        Image(const cv::Mat_<float> &pixel);




        //OPERATOR OVERLOADING
        
        /**
        * \brief Getter for the pixel of index (i,j)
        * \param i,j indices of the pixel
        * \return Pixel of index (i,j)
        */
        float& operator()(int i, int j);

        /**
        * \brief Convolution with matrix
        * \param filter is a matrix to perform the convolution with
        * \return Convolution of this and FILTER
        */
        Image operator*(cv::Mat_<float> filter);
       
        /**
        * \brief Convolution with image
        * \param filter is an instance of image. The convolution is performed with the pixel matrix of this class.
        * \return Convolution of this and the matrix of FILTER.
        */
        Image operator*(Image filter);

        /**
        * \brief Getter of the matrix of pixels
        * \return Matrix of pixels
        */
        cv::Mat_<float> operator()() const;

        /**
         * \brief Swap high intensity and low intensity
         * \return ones-img
         */
        Image operator-();

        /**
        * \brief Subtraction of images
        * \param img Image
        * \return this-img
        */
        Image operator-(const Image & img);

        /**
         * \brief Equality of images
         * \param img Image
         */
        bool operator==(const Image &img);

        
        
        //BASICS

        /**
        * \brief Conversion of matrix in [0,1] to matrix of [0,255]
        * \return Converted matrix
        */
        cv::Mat_<uchar> from1to255();

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

	    /**
	    * \brief Computes the error between two images
	    * \param img image to compare this with
	    * \param level tolerance between the two images
	    * \return Error between the images in pourcentage
	    */
	    float error(Image img, float level);
        
        /**
        * \brief Change the value of the pixels in a rectangle
        * \param x, y coordinates of the upper left point of the rectangle
        * \param length length of the rectangle
        * \param width width of the rectangle
        * \param color color of the pixels in the rectangle
        * \return Image with the modified pixels
        */
        Image rectangle(int x, int y, unsigned int length, unsigned int width, float color);

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



        //PRESSURE 

        //Eventuellement le faire pour une ellipse quelconque
        /**
        * \brief Put the pixels of the image in a vector of Point
        * \return vector of Point
        */
        std::vector<cv::Point> matrix2vector();

        /**
        * \brief Put the pixels that are outside an ellipse in a vector of Point
        * \param center center of the ellipse
        * \param a,b semi axes
        * \return vector of Point
        */
        std::vector<cv::Point> outside_ellipse(cv::Point center, float a, float b);

        /**
        * \brief Change the pressure of the image
        * \param center center of the image
        * \param coords vector of coordinates to change
        * \param iso boolean saying if the function used is isotropic or not
        * \param param, param_x, param_y parameters of the functions
        * \return Image with modified pressure
        */
  	    Image pressure(cv::Point center, std::vector<cv::Point> coords,  bool iso = false, float param = 50, float param_x = 0.00035, float param_y = 0.000175);



        //WARPS
        
        /**
         * \brief Index change integer to double
         *
         * This function transforms given pixel indices (i,j) in the range [0,rows-1]x[0,cols-1] to the corresponding double indices (x,y) in [-1,1]x[-a,a] where a is aspect ratio of the image
         * \param[in] i integer index for row (=x-direction)
         * \param[in] j integer index for column (=y-direction)
         * \param[out] x double index for row (=x-direction)
         * \param[out] y double index for column (=y-direction)
         *
         * The inverse of this function is given by \ref DoubleToIntIndex.
         * */
        void IntToDoubleIndex(int i, int j, double& x, double& y);
        
        /**
         * \brief Index change integer to double
         *
         * This function transforms given indices (x,y) in the range [-1,1]x[-a,a] (a is aspect ratio of the image) to the corresponding integer indices (x,y) in [0,rows-1]x[0,cols-1]. To obtain integers, the values are rounded.
         * It is the inverse function of \ref IntToDoubleIndex.
         * \param[in] x_prime double index for row (=x-direction)
         * \param[in] y_prime double index for column (=y-direction)
         * \param[out] x integer index for row (=x-direction)
         * \param[out] y integer index for column (=y-direction)
         * */
        
        void DoubleToIntIndex(double x_prime, double y_prime, int& x, int& y);
        /**
         * \brief Rotate indices
         *
         * This function rotates given indices (x,y) in the range [-1,1]x[-a,a] (a is aspect ratio of the image) by a factor theta.
         * \param[in] x double index for row (=x-direction)
         * \param[in] y double index for column (=y-direction)
         * \param[in] theta rotation factor
         * \param[out] x_prime rotated index for row (=x-direction)
         * \param[out] y_prime rotated index for column (=y-direction)
         * */
        void RotateIndices(double x, double y, double theta, double& x_prime, double& y_prime);

        /**
         * \brief Rotate image
         *
         * This function rotates an image by a factor theta. It therefore performs some index transformations and then the actual rotation.
         * \param[in] theta rotation factor
         * */
        Image Rotation(double theta);
        
        /**
         * \brief Bi-linear interpolation
         *
         * This function performs bi-linear interpolation for all pixels that have the value 1. It is used to improve the result of \ref Rotation where pixels that could not be assigned to an intensity value got the default value 1.
         * */
        void BilinearInterpolation();

        /**
         * \brief Improved rotation method
         *
         * This function combines rotation and interpolation in such a way that no rounding of indices is performed anymore (in contrast to the combination of \ref Rotation and \ref BilinearInterpolation). Another difference is that we are looping over the pixels in the rotated target image instead of the pixels in the original image. Therefore we are perforing a backward rotation of the factor 2*PI-THETA to get the intensity values for our result pixels.
         * \param[in] theta is the rotation factor
         * */
        Image InverseRotation(double theta);

        

        //MORPHOLOGICAL FILTER
        
        /**
         * \brief Binarization using a user defined threshold
         * \param threshold The threshold set by the user
         * \return Image with only 0 and 1 pixel intensities
         */
        Image BinarizeNaive(float threshold = 128);

        /**
         * \brief Binarization using Otsu's method
         * 
         * This function computes the optimal theshold according to Otsu's criterion
         * \return Image with ontly 0 and 1 pixel intensities
         */
        Image Binarize();

        /**
         * \brief Morphological erosion using a naive representation of the mathematical operation
         * \param struct_elt Coordinates of the elements of the kernel
         * \return Eroded image
         */
        Image ErodeNaive(std::vector<cv::Point> struct_elt);

        /**
         * \brief Morphological dilatation using a naive representation
         * 
         * This function calls \ref ErodeNaive, as performing a dilataion on the foreground is equivalent to performing an erosion on the background
         * \param struct_elt Coordinates of the elements of the kernel
         * \return Dilated image
         */
        Image DilateNaive(std::vector<cv::Point> struct_elt);
        
        /**
         * \brief Morphological erosion optimized
         * \param kernel A matrix representing the structural element
         * \return Eroded image
         */
        Image ErodeBin(cv::Mat_<float> kernel);

        /**
         * \brief Morphological dilatation
         * 
         * This function calls \ref Erode, as performing a dilataion on the foreground is equivalent to performing an erosion on the background
         * \param kernel A matrix representing the structural element
         * \return Dilatet image
         */        
        Image DilateBin(cv::Mat_<float> kernel);

        Image ErodeGray(cv::Mat_<float> kernel);
        
        Image DilateGray(cv::Mat_<float> kernel);

};

#endif  // IMAGES_H_
