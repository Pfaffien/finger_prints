#include <iostream>
#include <cmath>

#include "Starter2.h"


//Constructors
Image::Image(cv::String name){
    pixels = cv::imread(name, 0);

    if (pixels.empty())                   // Check for invalid input
        std::cerr <<  "Could not open or find the image" << std::endl;
    
    pixels /= 255.;
}

Image::Image(cv::Mat_<float> matrix){
    pixels = matrix.clone();
}


//Operator overloading
float& Image::operator()(int row, int col){
    return pixels(row,col);
}

cv::Mat_<float> Image::operator()(){
    return pixels;
}


//Min max
double Image::max(){
    double min, max;
    minMaxLoc(pixels, &min, &max);
    return max;
}

double Image::min(){
    double min, max;
    minMaxLoc(pixels, &min, &max);
    return min;
}


//Rectangle
Image Image::rectangle(int x_begin, int y_begin,
                        unsigned int length, unsigned int width,
                    float color){
    cv::Mat_<float> new_mat = pixels.clone();
    Image new_pixels(new_mat);

    for (int i = x_begin; i < x_begin + length; i++){
        for (int j = y_begin; j < y_begin + width; j++){
            new_pixels(i,j) = color;
        }
    }

  return new_pixels;
}


//Symetries
Image Image::sym_x(){
    int rows, cols;
    rows = pixels.rows;
    cols = pixels.cols;

    cv::Mat new_mat = pixels.clone();
    Image new_pixels(new_mat);

    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++)
            new_pixels(i, j) = (*this)(rows-i-1, j);
    }

    return new_pixels;
}

Image Image::sym_y(){
    int rows, cols;
    rows = pixels.rows;
    cols = pixels.cols;

    cv::Mat new_mat = pixels.clone();
    Image new_img(new_mat);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            new_img(i, j) = (*this)(i, cols-j-1);
    }

    return new_img;
}

Image Image::sym_xy(){
    Image new_img = (this->sym_x()).sym_y();
    return new_img;
}


// Conversion
cv::Mat_<uchar> Image::from1to255()
{
    cv::Mat_<uchar> res = pixels*255;
    /* res *= 255; */
    /* res = pixels.clone(); */
    return res;
}


// Plotting and saving
void Image::display(cv::String windowName, cv::String imageName){
    cv::Mat_<uchar> disp = this->from1to255();
    cv::namedWindow( windowName, cv::WINDOW_AUTOSIZE ); // Create a window for display.
    cv::imshow( imageName, disp );                // Show our image inside it.
    cv::waitKey(0); // Wait for a keystroke in the window
}

void Image::save(std::string s){
    cv::Mat_<uchar> disp = this->from1to255();
    s  = "../img/saved/" + s + ".png";
    cv::imwrite(s, disp);
}


/*Image Image::rotate(){
    //Get dimensions of image
    int rows, cols;
    rows = pixels.rows;
    cols = pixels.cols;
    
    //Create a clone of image that will be rotated
    cv::Mat new_mat = pixels.clone();
    
    //Determine point around which the image will be rotated (Here center of image)
    cv::Point2f p(rows/2., cols/2.);
    //Compute rotation matrix
    cv::Mat rot = cv::getRotationMatrix2D(p, 45, 1);
    //Compute affine transformation represented by the rotation matrix
    cv::warpAffine(pixels, new_mat, rot, pixels.size(), 1,0,1 );
    //Save computed matrix as image
    Image new_img(new_mat);
    
    return new_img;
    
}*/

/*Image Image::scaled_rotation(double a, double b, double t_x, double t_y){
    
    int rows, cols;
    rows = pixels.rows;
    cols = pixels.cols;
    
    cv::Mat new_mat = pixels.clone();
    Image new_img(new_mat);
    double x,y;
    double x_prime, y_prime;
    int x_int, y_int;
    int max = std::max(rows,cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++){
            x = (2*i-rows)/max;
            y = (2*j-cols)/max;
            x_prime = a*x-b*y+t_x; 
            y_prime = b*x+a*y+t_y;
            x_int = 
            y_int = 
            new_img(x, y) = (*this)(i, j);
        }
    }

    return new_img;
    
}*/

/*double PixelTransformX(int i, int j, double a, double b, double t_x){
    
    int rows, cols;
    rows = pixels.rows;
    cols = pixels.cols;
    
    double x,y;
    double x_prime;
    int max = std::max(rows,cols);
    
    //Compute corresponding coordinate of i in [-1,1]x[-max,max]
    x = (2*i-rows)/max;
    y = (2*j-cols)/max;
    
    //Compute transformation of coordinates
    x_prime = a*x-b*y+t_x;
    
    return x_prime;
    
}

double PixelTransformY(int i, int j, double a, double b, double t_y){
    
    int rows, cols;
    rows = pixels.rows;
    cols = pixels.cols;
    
    double x,y;
    double y_prime;
    int max = std::max(rows,cols);
    
    //Compute corresponding coordinate of i in [-1,1]x[-max,max]
    x = (2*i-rows)/max;
    y = (2*j-cols)/max;
    
    //Compute transformation of coordinates
    y_prime = b*x+a*y+t_y;
    
    return y_prime;
    
}*/


//This are the functions from Thursday

//transform integer indices to double indices (first step)
void Image::IntToDoubleIndex(int i, int j, double& x, double& y){
    int rows, cols;
    rows = pixels.rows;
    cols = pixels.cols;
    
    int max = std::max(rows,cols);
    
    //Compute corresponding coordinate of i in [-1,1]x[-max,max]
    x = (2*i-rows)/(double)max;
    y = (2*j-cols)/(double)max;
}

//Third step
void Image::DoubleToIntIndex(double x_prime, double y_prime, int& x, int& y){
    int rows, cols;
    rows = pixels.rows;
    cols = pixels.cols;
    
    int max = std::max(rows,cols);
    
    //Compute corresponding coordinate of i in [0,rows]x[0,cols]
    x = round((x_prime*max+rows)/2.);
    y = round((y_prime*max+cols)/2.);
}

//transforms double indices x,y of original image to rotated double indices of new image
void Image::rotate_indices(double x, double y, double theta, double& x_prime, double& y_prime){
    
    x_prime = std::cos(theta)*x-std::sin(theta)*y;
    y_prime = std::sin(theta)*x + std::cos(theta)*y;
}

//Compute pure rotation (without interpolation)
Image Image::rotate(double theta){
    //Get dimensions of image
    int rows, cols;
    rows = pixels.rows;
    cols = pixels.cols;
    
    //Create a new image that will be the rotation of the original image
    cv::Mat new_mat = cv::Mat::zeros(rows,cols,CV_32F);
    Image new_img(new_mat);
    
    double x, y, x_prime, y_prime;
    int i_prime, j_prime;
    for(int i=0; i<rows;i++){
        for(int j=0;j<cols;j++){
            //Transform indices to double
            IntToDoubleIndex(i, j, x, y);
            
            //Get double index of rotated pixel
            rotate_indices(x, y, theta, x_prime, y_prime);
            //Transform rotated pixel indices back to integer inidces
            DoubleToIntIndex(x_prime, y_prime, i_prime, j_prime);
            //Check if computed pixel is in range (0,rows)x(0,cols)
            if((i_prime < 0) ||(i_prime >=rows)){
                continue;
            }
            if((j_prime < 0) || (j_prime >=cols)){
                continue;
            }
            //TODO this has to be improved
            //Set new pixel to intensity of original pixel
            new_img(i_prime, j_prime) = (*this)(i, j); 
            //std::cerr << "set pixel (" << i_prime <<", " <<j_prime<<") to " << (*this)(i, j)<<"\n";
        }
    }
    
    return new_img;
    
}





