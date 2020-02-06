#ifndef _IMAGE_H_
#define _IMAGE_H_


/**
 * \file image.h
 * \brief Definition of the class image and the methods
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

#include "pressure.h"
#include "linear_filtering.h"


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
        * \param  pixel is a matrix representing an image
        */
        Image(const cv::Mat_<float> &pixel);



        //OPERATOR OVERLOADING

        /**
        * \brief Getter for the pixel of index (i,j)
        * \param i,j are the indices of the pixel
        * \return Value of the pixel of index (i,j)
        */
        float& operator()(int i, int j);


        /**
        * \brief Convolution with matrix
        * \param filter is a matrix to perform the convolution with
        * \return Convolution of this and filter
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
         * Exchanges the convention for black and white
         * \return ones-img
         */
        Image operator-();


        /**
        * \brief Subtraction of images
        * \param img is an Image
        * \return this-img
        */
        Image operator-(const Image & img);


        /**
         * \brief Equality of images
         * \param img is an Image
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
        * \param imageName is the name of the window
        */
        void display(cv::String imageName = "Display finger_print");


        /**
        * \brief Save the image in the folder img/saved
        * \param s is the name of the saved image
        */
        void save(std::string s = "finger_print");


        /**
        * \brief Find the maximum value in the image
        * \return Maximal intensity value of the image
        */
        double max();


        /**
        * \brief Find the minimum value in the image
        * \return Minimal intensity value of the image
        */
        double min();


  	    /**
  	    * \brief Compute the error between two images
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
        Image Rectangle(int x, int y, unsigned int length, unsigned int width, float color);


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


        /**
         * \brief Find the center of the image
         * This function uses the method of barycenter to find the center
         * \return Points of the center
         */
        cv::Point center();


        /**
         * \brief Compute the mean of the image
         * \return Mean of the image
         */
        float mean();



        //PRESSURE

        /**
        * \brief Put the pixels of the image in a vector of Point
        * \return Vector of Point
        */
        std::vector<cv::Point> MatrixToVector();


        /**
        * \brief Put the pixels that are outside an ellipse in a vector of Point
        * \param center is the center of the ellipse
        * \param a,b are the semi axes
        * \return Vector of Point
        */
        std::vector<cv::Point> OutsideEllipse(cv::Point center, float a, float b);


        /**
        * \brief Change the pressure of the image using cartesian coordinates
        * \param center is the center of the image
        * \param coords is the vector of coordinates to change
        * \param iso is the boolean saying if the function used is isotropic or not
        * \param param, param_x, param_y are the parameters of the functions
        * \return Image with modified pressure
        */
  	    Image Pressure(cv::Point center, std::vector<cv::Point> coords,  bool iso = false,
                        float param = 50, float param_x = 0.00035, float param_y = 0.000175);


        /**
        * \brief Change the pressure of the image using polar coordinates
        * \param center is the center of the image
        * \param coords is the vector of coordinates to change
        * \param iso is the boolean saying if the function used is isotropic or not
        * \param param_rot is the angle by which the ellipsoid on which we apply the function is rotated
        * \param number_angles is the number of angle ranges we want to use to approximate a weak pressure
        * \param threshold is the threshold used to determine whether a random angle is kept or not
        * \param param, param_x, param_y are the parameters of the function
        * \return Image with modified pressure
        */
  	    Image PressurePolar(cv::Point center, std::vector<cv::Point> coords,  bool iso = false,
                            float param_rot = 0, int number_angles = 0, float threshold = 0.5,
                            float param = 50, float param_x = 0.00035, float param_y = 0.000175);



        //WARPS

        /**
         * \brief Index change integer to double
         *
         * This function transforms given pixel indices (i,j) in the range [0,rows-1]x[0,cols-1] to the corresponding double indices (x,y) in [-1,1]x[-a,a] where a is aspect ratio of the image
         * \param[in] i is the integer index for row (=x-direction)
         * \param[in] j is the integer index for column (=y-direction)
         * \param[out] x is the double index for row (=x-direction)
         * \param[out] y is the double index for column (=y-direction)
         *
         * The inverse of this function is given by \ref DoubleToIntIndex.
         * */
        void IntToDoubleIndex(int i, int j, double& x, double& y);


        /**
         * \brief Index change integer to double
         *
         * This function transforms given indices (x,y) in the range [-1,1]x[-a,a] (a is aspect ratio of the image) to the corresponding integer indices (x,y) in [0,rows-1]x[0,cols-1]. To obtain integers, the values are rounded.
         * It is the inverse function of \ref IntToDoubleIndex.
         * \param[in] x_prime is the double index for row (=x-direction)
         * \param[in] y_prime is the double index for column (=y-direction)
         * \param[out] x is the integer index for row (=x-direction)
         * \param[out] y is the integer index for column (=y-direction)
         * */
        void DoubleToIntIndex(double x_prime, double y_prime, int& x, int& y);


        /**
         * \brief Rotate indices
         *
         * This function rotates given indices (x,y) in the range [-1,1]x[-a,a] (a is aspect ratio of the image) by a factor theta.
         * \param[in] x is the double index for row (=x-direction)
         * \param[in] y is the double index for column (=y-direction)
         * \param[in] theta is the rotation factor
         * \param[out] x_prime is the rotated index for row (=x-direction)
         * \param[out] y_prime is the rotated index for column (=y-direction)
         * */
        void RotateIndices(double x, double y, double theta, double& x_prime, double& y_prime);


        /**
         * \brief Rotate image
         *
         * This function rotates an image by a factor theta. It therefore performs some index transformations and then the actual rotation.
         * \param[in] theta is the rotation factor
         * \return 
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
         * \param theta is the rotation factor
         * \param extension 
         * \return 
         * */
        Image InverseRotation(double theta, int extension = 0);


        /**
         * \brief 
         * This function computes 
         * \param i is the x coordinate of the curente pixel 
         * \param j is the x coordinate of the curente pixel
         * \param origin is the origin of the circle we apply the rotation in
         * \param radius is the radius of the circle we apply the rotation in
         * \param theta is the rotation factor
         * \return 
         * */
        double ThetaScaled(int i, int j, cv::Point origin, double radius, double theta);

        /**
         * \brief 
         * \param theta is the rotation factor
         * \param radius is the radius of the circle we apply the rotation in
         * \param center_x is the x coordinate of the origin of the circle we apply the rotation in
         * \param center_y is the y coordinate of the origin of the circle we apply the rotation in
         * \return 
         */ 
        Image ScaledRotation(double theta, double radius, double center_x, double center_y);

        /**
         * \brief
         * \param theta is the rotation factor
         * \param radius is the radius of the circle we apply the rotation in
         * \param center_x is the x coordinate of the origin of the circle we apply the rotation in
         * \param center_y is the y coordinate of the origin of the circle we apply the rotation in
         * \return 
         */ 
        Image InverseScaledRotation(double theta, double radius, double center_x, double center_y);


        /**
         * \brief Translation of this of px pixels in x axis and py pixels in y axis
         * \param px is the number of pixels to translate the image along x axis
         * \param py is the number o pixels to translate the image along y axis
         * \return Translated image
         */ 
        Image Translation(double px, double py);



        // MORPHOLOGICAL FILTERING

        /**
         * \brief Binarize an image using a user defined threshold
         * \param threshold user defined parameter to determine whether a pixel is set to 0 or 1
         * \return Binarized image
         */ 
        Image BinarizeNaive(float threshold);


        /**
         * \brief Binarize an image using an optimal threshold (according to Otsu's method)
         * \return Binarized image
         */ 
        Image Binarize();

        /**
         * \brief Erode a binary image using a naive approach
         * \param struct_elt is the structuring element
         * \return Eroded image
         */
        Image ErodeNaive(std::vector<cv::Point> struct_elt);

        /**
         * \brief Dilate a binary image using \ref ErodeNaive
         * Erosion and dilation are dual notions (an erosion of the foreground corresponds
         * to a dilation of the background) thus it uses the already implemented \ref ErodeNaive
         * \param struct_elt is the structuring element
         * \return Dilated image
         */
        Image DilateNaive(std::vector<cv::Point> struct_elt);




        /**
         * \brief Erode an image after binarizing it
         * \param kernel is the structuring element
         * \return Eroded binary image
         */
        Image ErodeBin(cv::Mat_<float> kernel);


        /**
         * \brief Dilate an image after binarizing it using \ref ErodeBin
         * Erosion and dilation are dual notions (an erosion of the foreground corresponds
         * to a dilation of the background) thus it uses the already implemented \ref ErodeBin
         * \param kernel the structuring element
         * \return Dilated binary image
         */
        Image DilateBin(cv::Mat_<float> kernel);


        /**
         * \brief Erode a grayscale image
         * \param kernel is the structuring element
         * \return Eroded image
         */
        Image ErodeGray(cv::Mat_<float> kernel);


        /**
         * \brief Dilate a grayscale image using \ref ErodeGray
         * Erosion and dilation are dual notions (an erosion of the foreground corresponds
         * to a dilation of the background) thus it uses the already implemented \ref ErodeGray
         * \param kernel the structuring element
         * \return Dilated image
         */
        Image DilateGray(cv::Mat_<float> kernel);


        /**
         * \brief A general method to use all the previous erosions
         * \param kernel the structuring element
         * This method also implements a complex erosion by taking the distance to the center
         * into account
         * \param erosion_type binary, grayscale or complex - determines which erosion to compute
         * \return Eroded image
         */
        Image Erode(cv::Mat_<float> kernel, std::string erosion_type);


        /**
         * \brief A general method to use all the previous dilations (calling \ref Erode)
         * Erosion and dilation are dual notions (an erosion of the foreground corresponds
         * to a dilation of the background) thus it uses the already implemented \ref Erode
         * \param kernel the structuring element
         * \param dilation_type binary, grayscale or complex - determines which dilation to compute
         * \return Dilated image
         */
        Image Dilate(cv::Mat_<float> kernel, std::string dilation_type);


        /**
         * \brief Skeletonization on an image
         * \return Binary skeleton of the image
         */
        Image Skeletonize();

};


#endif  /* _IMAGE_H_ */
