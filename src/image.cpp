#include <iostream>
#include "Image.h"

/*Image uchar*/
//Constructors
Image::Image(cv::String name){
    img = cv::imread(name, 0);
    if (img.empty())                   // Check for invalid input
        std::cerr <<  "Could not open or find the image" << std::endl;
}

Image::Image(cv::Mat matrix){
    img = matrix;
}

Image::Image(Image_float image){
  cv::Mat_<float> mat = image().clone();
  mat = mat*255;
  img = mat.clone();
}

//Operator overloading
uchar& Image::operator()(int row, int col){
  //TODO check if indices make sense
  return img(row,col);
}

cv::Mat Image::operator()(){
  return img;
}

// Plotting and saving
void Image::display(cv::String windowName, cv::String imageName){
    cv::namedWindow( windowName, cv::WINDOW_AUTOSIZE ); // Create a window for display.
    cv::imshow( imageName, img );                // Show our image inside it.
    cv::waitKey(0); // Wait for a keystroke in the window
}

void Image::save(std::string s){
    s  = "../img/" + s + ".png";
    cv::imwrite(s, img);
}



/*Image_float*/
//Constructors
Image_float::Image_float(cv::Mat matrix){
    img = matrix;
}

Image_float::Image_float(Image image){
  img = image().clone();
  img = img/255;
}

//Operator overloading
float& Image_float::operator()(int row, int col){
  //TODO check if indices make sense
  return img(row,col);
}

cv::Mat Image_float::operator()(){
  return img;
}

// Min max
double Image_float::max(){
    double min, max;
    minMaxLoc(img, &min, &max);
    return max;
}

double Image_float::min(){
    double min, max;
    minMaxLoc(img, &min, &max);
    return min;
}

//Rectangle
Image_float Image_float::rectangle(int x_begin, int y_begin,
                        unsigned int length, unsigned int width,
                        float color){
  // TODO check if indices make sense
    cv::Mat new_mat = img.clone();
    Image_float new_img(new_mat);

    for (int i = x_begin; i < x_begin + length; i++){
        for (int j = y_begin; j < y_begin + width; j++){
            new_img(i,j) = color;
        }
    }

  return new_img;
}

//Symetries
Image_float Image_float::sym_x(){
    int rows, cols;
    rows = img.rows;
    cols = img.cols;

    cv::Mat new_mat = img.clone();
    Image_float new_img(new_mat);

    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++)
            new_img(i, j) = (*this)(rows-i-1, j);
    }

    return new_img;
}

Image_float Image_float::sym_y(){
    int rows, cols;
    rows = img.rows;
    cols = img.cols;

    cv::Mat new_mat = img.clone();
    Image_float new_img(new_mat);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            new_img(i, j) = (*this)(i, cols-j-1);
    }

    return new_img;
}

Image_float Image_float::sym_xy(){
    Image_float new_img = (this->sym_x()).sym_y();
    return new_img;
}
