#include "main1.h"
#include "Image.h"

//TODO méthodes convolutions

//Constructors
Image::Image(cv::String name){
    pixels = cv::imread(name, 0).clone();

    if (pixels.empty())                   // Check for invalid input
        throw std::runtime_error("Could not open or find the image");
    pixels /= 255.;
}

Image::Image(cv::Mat_<float> matrix){
    pixels = matrix.clone();
}


//Operator overloading
float& Image::operator()(int row, int col){
    if (row < 0 || row >= pixels.rows || col < 0 || col >= pixels.cols)
        throw std::runtime_error("Index out of range");
    return pixels(row,col);
}

cv::Mat_<float> Image::operator()() const {
    return pixels;
}

Image Image::operator-(const Image &img){
    cv::Mat_<float> im1 = (*this)().clone();
    cv::Mat_<float> im2 = img();
    cv::Mat_<float> diff = im1-im2;
    return Image(abs(diff));
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

    for (int i = y_begin; i < y_begin + length; i++){
        for (int j = x_begin; j < x_begin + width; j++){
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

//All pixels into a vector
std::vector<cv::Point> Image::matrix2vector()
{
    std::vector<cv::Point> coord;

    for (int i = 0; i < (*this)().rows; i++) {
        for (int j = 0; j < (*this)().cols; j++)
            coord.push_back(cv::Point(j, i));
    }

    return coord;
}

//Set of points of the image outside the geometric figure
std::vector<cv::Point> Image::outside_ellipse(cv::Point center, float a, float b)
{
    std::vector<cv::Point> coords;
    cv::Point tmp((int) 0, (int) 0);
    float dist, maximum;
    cv::Point focus1, focus2;

    if (a == b) {
        focus1 = center;
        focus2 = center;
    } else if (a > b) {
        dist = sqrt(a*a - b*b);
        focus1.x = center.x - dist;
        focus1.y = center.y;
        focus2.x = center.x + dist;
        focus2.y = center.y;
    } else if (a < b) {
        dist = sqrt(b*b - a*a);
        focus1.x = center.x;
        focus1.y = center.y - dist;
        focus2.x = center.x;
        focus2.y = center.y + dist;
    }

    maximum = std::max(a, b);

    for (int i = 0; i < pixels.rows; i++) {
	    tmp.y = i;
    	for (int j = 0; j < pixels.cols; j++) {
	        tmp.x = j;
            if (cv::norm(tmp - focus1) + cv::norm(tmp - focus2) > 2*maximum)
                coords.push_back(cv::Point(tmp.x, tmp.y));
	    }
    }

    return coords;
}


//Pressure variation
Image Image::pressure(cv::Point center, std::vector<cv::Point> coords, bool iso, float param, float param_x, float param_y, int direction)
{
    std::vector<float> new_values = coeffs(center, coords, param_x, param_y, param, iso);
    cv::Mat_<float> new_pixels = pixels.clone();
    Image ones(cv::Mat_<float>((*this)().rows, (*this)().cols, 1));
    Image diff = new_pixels.clone();
  
    if (direction)
        diff = ones - new_pixels;
    
    for (int i = 0; i < new_values.size(); i++)
        diff(coords[i].y, coords[i].x) *= new_values[i];

    if (direction)
        diff = ones - diff;

    return diff;
}


// Conversion
cv::Mat_<uchar> Image::from1to255()
{
    cv::Mat_<uchar> res = pixels*255;
    return res;
}


// Plotting and saving
void Image::display(cv::String imageName){
    cv::Mat_<float> tmp = pixels.clone();
    Image tmp_img(tmp);
    cv::Mat_<uchar> disp = tmp_img.from1to255();
    cv::namedWindow( imageName, cv::WINDOW_AUTOSIZE ); // Create a window for display.
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
