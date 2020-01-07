#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;

class Image{
 private:
    Mat_<uchar> img;
public:
    //Constructor
    Image(String);
    Image(Mat);

    //Functions for min max
    double max();
    double min();

    //Plotting and saving
    void display();
    void save(std::string s = "finger_print");

    //Symetries
    Image sym_y();
    Image sym_xy();

    //Change intensity intervals
    void OneTo255();
    void From255ToOne();

    //Operator overloading
    uchar& operator()(int, int);
    Mat operator()();

    //Rectangles
    Image rectangle(int, int, unsigned int, unsigned int, float);
};

/*Image::Image(std::string name){

    img = imread(samples::findFile(name), 0);
    if( img.empty() )                   // Check for invalid input
        std::cerr <<  "Could not open or find the image" << std::endl ;
}*/

Image::Image(String name){
    img = imread(name, 0);
    if (img.empty())                   // Check for invalid input
        std::cerr <<  "Could not open or find the image" << std::endl ;

}

Image::Image(Mat matrix){
    img = matrix;
}

double Image::max(){
    double min, max;
    minMaxLoc(img, &min, &max);
    return max;
}

double Image::min(){
    double min, max;
    minMaxLoc(img, &min, &max);
    return min;
}

void Image::display(){
    namedWindow( "Display finger_print", WINDOW_AUTOSIZE ); // Create a window for display.
    imshow( "Display finger_print", img );                // Show our image inside it.
    waitKey(0); // Wait for a keystroke in the window
}

void Image::save(std::string s){
    s  = "../../" + s + ".png";
    imwrite(s, img);

}

Image Image::sym_y()
{
    int rows, cols;
    rows = img.rows;
    cols = img.cols;
    
    Mat new_mat = img.clone();
    Image new_img(new_mat);
    std::cout << "rows: " << rows << ", cols: " << cols << std::endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            new_img(i, j) = (*this)(i, cols-j-1);
    }

    return new_img;
}

/* Image sym_xy() */
/* { */

void Image::OneTo255(){
    img = 255. * img;
}

void Image::From255ToOne(){
    img = img / 255.;
}

uchar& Image::operator()(int row, int col){
    //TODO check if indices make sense
    return img(row,col);
    /* return img.at<uchar>(row,col); */
}

Image Image::rectangle(int x_begin, int y_begin,
                        unsigned int length, unsigned int width,
                        float color){
  // TODO check if indices make sense
  Mat new_mat = img.clone();
  Image new_img(new_mat);
  for (int i = x_begin; i < x_begin + length; i++){
    for (int j = y_begin; j < y_begin + width; j++){
      new_img(i,j) = color;
    }
  }
  return new_img;
}

Mat Image::operator()(){
  return img;
}
