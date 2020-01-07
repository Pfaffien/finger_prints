#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;

class Image{
 private:
    Mat img;
public:
    //Image(std::string);
    Image(String);
    Image(Mat);
    double max();
    double min();
    void display();
    void save(std::string s = "finger_print");
    Image sym_y();
    Image sym_xy();
};

/*Image::Image(std::string name){
    
    img = imread(samples::findFile(name), 0);
    if( img.empty() )                   // Check for invalid input
        std::cerr <<  "Could not open or find the image" << std::endl ;
}*/

Image::Image(String name){
    std::cerr << "String name is: " << name << std::endl;
    img = imread(name, 0);
    if( img.empty() )                   // Check for invalid input
        std::cerr <<  "Could not open or find the image" << std::endl ;
}

Image::Image(Mat matrix){
    img = matrix;
}

double Image::max(){
    return 0;
}

double Image::min(){
    return 0;
    
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

Image sym_y()
{
    int rows, cols;
    rows = img.rows;
    cols = img.cols;
    
    Mat new_img(rows, cols, CV_16UC1);

    for (int i = n-1; i >= 0; i--)
}

Image sym_xy()
{

}
