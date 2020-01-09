#include <iostream>

#include "Image.h"


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

cv::Mat_<float> Image::operator()() const {
    return pixels;
}

Image Image::operator-(const Image &img) {
    return Image((*this)() - img());
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
    Image new_pixels(new_mat);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            new_pixels(i, j) = (*this)(i, cols-j-1);
    }

    return new_pixels;
}

Image Image::sym_xy(){
    Image new_pixels = (this->sym_x()).sym_y();
    return new_pixels;
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
    cv::Mat_<float> tmp = pixels.clone();
    Image tmp_img(tmp);
    cv::Mat_<uchar> disp = tmp_img.from1to255();
    cv::namedWindow( windowName, cv::WINDOW_AUTOSIZE ); // Create a window for display.
    cv::imshow( imageName, disp );                // Show our image inside it.
    cv::waitKey(0); // Wait for a keystroke in the window
}

void Image::save(std::string s){
    cv::Mat_<float> tmp = pixels.clone();
    Image tmp_img(tmp);
    cv::Mat_<uchar> disp = tmp_img.from1to255();
    s  = "../img/saved/" + s + ".png";
    cv::imwrite(s, disp);
}
