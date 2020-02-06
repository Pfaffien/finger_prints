#include "image.h"


//CONSTRUCTORS

Image::Image(cv::String filename)
{
    //Read the image into a cv::Mat matrix
    pixels = cv::imread(filename, 0).clone();

    //Check for invalid input
    if (pixels.empty())
        throw std::runtime_error("Could not open or find the image");

    //Divide values of matrix by 255 to get floatingpoint values inside [0,1]
    pixels /= 255.;

    //Set rows and cols
    rows = pixels.rows;
    cols = pixels.cols;
}


Image::Image(const cv::Mat_<float> &matrix)
{
    //Clone matrix
    pixels = matrix.clone();

    //Set rows and cols
    rows = pixels.rows;
    cols = pixels.cols;
}




//OPERATORS OVERLOADING

float &Image::operator()(int row, int col)
{
    //Check for invalid input
    if (row >= rows || row < 0 || col >= cols || col < 0)
        throw std::runtime_error("Warning: trying to acces pixel outside of image range.");
    else
        return pixels(row, col);
}


Image Image::operator*(cv::Mat_<float> filter)
{
    cv::Mat_<float> conv = convolutionDFT(pixels, filter);

    return Image(conv);
}


Image Image::operator*(Image filter)
{
    cv::Mat_<float> conv = convolutionDFT(pixels, filter());

    return Image(conv);
}


cv::Mat_<float> Image::operator()() const
{
    return pixels;
}


Image Image::operator-()
{
    cv::Mat_<float> ones(rows, cols, 1);

    return Image(ones - pixels);
}


Image Image::operator-(const Image &img)
{
    if (rows != img.rows || cols != img.cols)
        throw std::runtime_error("Images should have the same size");

    return Image(abs(pixels - img()));
}


bool Image::operator==(const Image &img)
{
    bool eq = true;

    if (rows != img.rows || cols != img.cols)
        throw std::runtime_error("Sizes do not match");

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (pixels(i, j) != img.pixels(i, j)){
                eq = false;
                break;
            }
        }
    }

    return eq;
}


double Image::max()
{
    double min, max;
    minMaxLoc(pixels, &min, &max);

    return max;
}


double Image::min()
{
    double min, max;
    minMaxLoc(pixels, &min, &max);

    return min;
}


float Image::error(Image img, float level)
{
    Image diff = *this - img;
    float res = 0;

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (diff(i, j) > level)
                res++;
        }
    }

    return res / (rows * cols);
}




//BASICS

cv::Mat_<uchar> Image::from1to255()
{
    cv::Mat_<uchar> res = pixels * 255;

    return res;
}


void Image::display(cv::String imageName)
{
    //Convert intensity values back to [0,255]
    cv::Mat_<float> tmp = pixels.clone();
    Image tmp_img(tmp);
    cv::Mat_<uchar> disp = tmp_img.from1to255();

    //Create a window for displaying
    cv::namedWindow(imageName, cv::WINDOW_AUTOSIZE);

    //Show the image inside the created window
    cv::imshow(imageName, disp);

    //Wait for a keystroke in the window to close it
    cv::waitKey(0);
}


void Image::save(std::string filename)
{
    //Convert intensity values back to [0,255]
    cv::Mat_<float> tmp = pixels.clone();
    Image tmp_img(tmp);
    cv::Mat_<uchar> disp = tmp_img.from1to255();

    //Save image as png-file
    filename = "../img/saved/" + filename + ".png";
    cv::imwrite(filename, disp);
}


Image Image::Rectangle(int x_begin, int y_begin,
                       unsigned int length, unsigned int width,
                       float color)
{
    cv::Mat_<float> new_mat = pixels.clone();
    Image new_pixels(new_mat);

    for (int i = y_begin; i < y_begin + length; i++){
        for (int j = x_begin; j < x_begin + width; j++)
            new_pixels(i, j) = color;
    }

    return new_pixels;
}


Image Image::sym_x()
{
    cv::Mat new_mat = pixels.clone();
    Image new_pixels(new_mat);

    for (int j = 0; j < cols; j++){
        for (int i = 0; i < rows; i++)
            new_pixels(i, j) = pixels(rows - i - 1, j);
    }

    return new_pixels;
}


Image Image::sym_y()
{
    cv::Mat new_mat = pixels.clone();
    Image new_img(new_mat);

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++)
            new_img(i, j) = pixels(i, cols - j - 1);
    }

    return new_img;
}


Image Image::sym_xy()
{
    cv::Mat_<float> new_mat(cols, rows);
    Image new_img(new_mat);

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++)
            new_img(j, i) = pixels(i, j);
    }

    return new_img;
}


cv::Point Image::center()
{
    Image cpy = -(*this);
    cv::Point tmp(0,0);
    cv::Point sum(0,0);
    float sum_val = 0;

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            tmp.x = j;
            tmp.y = i;

            sum += cpy(i,j)*tmp;
            sum_val += cpy(i,j);
        }
    }
    sum /= sum_val;

    return cv::Point((int)sum.x, (int)sum.y);
}


float Image::mean()
{
    float sum = 0;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++)
            sum += pixels(i,j);
    }

    return sum/(rows*cols);
}




//PRESSURE

std::vector<cv::Point> Image::MatrixToVector()
{
    std::vector<cv::Point> coord(rows * cols);

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++)
            coord[i * cols + j] = cv::Point(j, i);
    }

    return coord;
}


std::vector<cv::Point> Image::OutsideEllipse(cv::Point center, float a, float b)
{
    std::vector<cv::Point> coords;
    cv::Point tmp((int)0, (int)0);
    float dist, maximum = std::max(a, b);
    ;
    cv::Point focus1, focus2;

    if (a == b){
        focus1 = center;
        focus2 = center;
    } else if (a > b){
        dist = sqrt(a * a - b * b);
        focus1.x = center.x - dist;
        focus1.y = center.y;
        focus2.x = center.x + dist;
        focus2.y = center.y;
    }else if (a < b){
        dist = sqrt(b * b - a * a);
        focus1.x = center.x;
        focus1.y = center.y - dist;
        focus2.x = center.x;
        focus2.y = center.y + dist;
    }
    for (int i = 0; i < pixels.rows; i++){
        tmp.y = i;
        for (int j = 0; j < pixels.cols; j++){
            tmp.x = j;
            if (cv::norm(tmp - focus1) + cv::norm(tmp - focus2) > 2 * maximum)
                coords.push_back(cv::Point(tmp.x, tmp.y));
        }
    }

    return coords;
}


Image Image::Pressure(cv::Point center, std::vector<cv::Point> coords,
                      bool iso, float param, float param_x, float param_y)
{
    std::vector<float> new_values = coeffs(center, coords, param_x,
                                           param_y, param, iso);

    Image diff = -(*this);

    for (int i = 0; i < new_values.size(); i++)
        diff(coords[i].y, coords[i].x) *= new_values[i];

    diff = -diff;

    return diff;
}


Image Image::PressurePolar(cv::Point center, std::vector<cv::Point> coords,
                           bool iso, float param_rot, int number_angles,
                           float threshold, float param, float param_x, float param_y)
{
    std::vector<float> new_values = coeffs_polar(center, coords, param_x,
                                           param_y, param, param_rot,
                                           number_angles, threshold, iso);

    Image diff = -(*this);

    for (int i = 0; i < new_values.size(); i++)
        diff(coords[i].y, coords[i].x) *= new_values[i];

    diff = -diff;

    return diff;
}




//WARPS

void Image::IntToDoubleIndex(int i, int j, double &x, double &y)
{
    //Get maximum of rows and cols
    int max = std::max(rows, cols);

    //Compute corresponding coordinate of (i,j) in [-1,1]x[-a,a]
    x = (2 * i - rows) / (double)max;
    y = (2 * j - cols) / (double)max;
}


void Image::DoubleToIntIndex(double x, double y, int &i, int &j)
{
    //Get maximum of rows and cols
    int max = std::max(rows, cols);

    //Compute corresponding coordinate of (x,y) in [0,rows-1]x[0,cols-1]
    i = round((x * max + rows) / 2.);
    j = round((y * max + cols) / 2.);
}


void Image::RotateIndices(double x, double y, double theta, double &x_prime, double &y_prime)
{
    x_prime = std::cos(theta) * x - std::sin(theta) * y;
    y_prime = std::sin(theta) * x + std::cos(theta) * y;
}


Image Image::Rotation(double theta)
{
    //Create a new image that will be the rotation of the original image
    cv::Mat new_mat = cv::Mat::ones(rows, cols, CV_32F);
    Image new_img(new_mat);

    //Auxiliary indexing variables
    double x, y, x_prime, y_prime;
    int i_prime, j_prime;

    //Loop over all pixel in original image
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){

            //Transform indices to double
            IntToDoubleIndex(i, j, x, y);

            //Rotate indices
            RotateIndices(x, y, theta, x_prime, y_prime);

            //Transform rotated pixel indices back to integer indices
            DoubleToIntIndex(x_prime, y_prime, i_prime, j_prime);

            //Check if computed pixel is in range (0,rows)x(0,cols)
            if ((i_prime < 0) || (i_prime >= rows))
                continue;
            if ((j_prime < 0) || (j_prime >= cols))
                continue;

            //Set new pixel to intensity of original pixel
            new_img(i_prime, j_prime) = pixels(i, j);
        }
    }

    return new_img;
}


void Image::BilinearInterpolation()
{
    //Loop over all pixels to find the non-affected ones
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            //Check if the pixel has the default value 1
            if (pixels(i, j) == 1){
                //Check if pixel is corner or boundary pixel
                if (i == 0){
                    
                    if (j == 0)
                        pixels(i, j) = 0.5 * (pixels(i + 1, j) + pixels(i, j + 1));
                    else if (j == cols - 1)
                        pixels(i, j) = 0.5 * (pixels(i + 1, j) + pixels(i, j - 1));
                    else
                        pixels(i, j) = (1. / 3.) * (pixels(i + 1, j) + pixels(i, j - 1) + pixels(i, j + 1));
                
                } else if (i == rows - 1){

                    if (j == cols - 1)
                        pixels(i, j) = 0.5 * (pixels(i - 1, j) + pixels(i, j - 1));
                    else if (j == 0)
                        pixels(i, j) = 0.5 * (pixels(i - 1, j) + pixels(i, j + 1));
                    else
                        pixels(i, j) = (1. / 3.) * (pixels(i - 1, j) + pixels(i, j - 1) + pixels(i, j + 1));
                
                } else if (j == 0){

                    pixels(i, j) = (1. / 3.) * (pixels(i + 1, j) + pixels(i - 1, j) + pixels(i, j + 1));
                
                } else if (j == cols - 1){

                    pixels(i, j) = (1. / 3.) * (pixels(i + 1, j) + pixels(i - 1, j) + pixels(i, j - 1));
                
                } else {

                    //Interpolation for non-boundary pixels
                    pixels(i, j) = 0.25 * (pixels(i - 1, j) + pixels(i + 1, j) + pixels(i, j - 1) + pixels(i, j + 1));
                
                }
            }
        }
    }
}


Image Image::InverseRotation(double theta, int extension)
{
    //Get maximum of rows and cols
    int max = std::max(rows, cols);

    //Create a new image that will be the rotation of the original image.
    // Pixels get the default value 1
    cv::Mat new_mat = cv::Mat::ones(rows+extension,cols+extension,CV_32F);
    Image new_img(new_mat);

    //Auxiliary variables
    double x, y, x_rot, y_rot;
    int neighbour_x, neighbour_y;
    double interp_x1, interp_x2, dist_x, dist_y;


    //Loop over all pixels in rotated image
    for (int i = 0; i < rows+extension; i++) {
        for (int j = 0; j < cols+extension; j++) {

            //Transform pixel indices to coordinates in [-1,1]x[-a,a],
            // where a is aspect ratio of the image
            IntToDoubleIndex(i, j, x, y);

            //Rotate the coordinates by a given value theta
            RotateIndices(x, y, 2 * M_PI - theta, x_rot, y_rot);

            //Transform the coordinates back to the [0,rows-1]x[0,cols-1] range
            x_rot = (x_rot*max + rows + extension)/2.;
            y_rot = (y_rot*max + cols + extension)/2.;

            //Determine indices of nearest neighbouring pixel of given coordinate
            neighbour_x = floor(x_rot);
            neighbour_y = floor(y_rot);

            //Check if computed neighbouring pixel is in range [0,rows-1]x[0,cols-1];
            //If it is not, continue with next pixel, current pixel will
            // keep default value 1
            if ((neighbour_x < 0) || (neighbour_x >= rows))
                continue;
            if ((neighbour_y < 0) || (neighbour_y >= cols))
                continue;

            //Compute distance of coordinates to neighbouring pixel
            // in x- and y-direction
            dist_x = x_rot - neighbour_x;
            dist_y = y_rot - neighbour_y;

            //Handle boundaries seperately
            if ((neighbour_x == rows - 1) && (neighbour_y == cols - 1)){

                new_img(i, j) = pixels(rows - 1, cols - 1);

            } else if (neighbour_x == rows - 1){

                //Interpolation in y-direction
                new_img(i, j) = (1. - dist_y) * pixels(neighbour_x, neighbour_y) + dist_y * pixels(neighbour_x, neighbour_y + 1);
            
            } else if (neighbour_y == cols - 1){

                //Interpolation in x-direction
                new_img(i, j) = (1. - dist_x) * pixels(neighbour_x, neighbour_y) + dist_x * pixels(neighbour_x + 1, neighbour_y);
            
            } else{

                //Bilinear interpolation
                //Interpolate value in x-direction
                interp_x1 = (1. - dist_x) * pixels(neighbour_x, neighbour_y) + dist_x * pixels(neighbour_x + 1, neighbour_y);
                interp_x2 = (1. - dist_x) * pixels(neighbour_x, neighbour_y + 1) + dist_x * pixels(neighbour_x + 1, neighbour_y + 1);
                //Interpolation in y-direction
                new_img(i, j) = (1. - dist_y) * interp_x1 + dist_y * interp_x2;

            }
        }
    }

    return new_img;
}


//Method to calculate the scaled theta
double Image::ThetaScaled(int i, int j, cv::Point origin,
                          double radius, double theta){

    double dist, theta_scaled;

    //Creation of a point at the current indices
    cv::Point tmp_point (i,j);

    //Computation of the distance between the point and the original
    dist = cv::norm(origin - tmp_point);

    //Check if the point is inside the circle
    if (dist < radius){
        theta_scaled = std::abs(-2*pow(dist/radius, 3) + 3*pow(dist/radius, 2));
        theta_scaled = 1-theta_scaled;
        theta_scaled = theta*theta_scaled;
    } else //if the points lies outside the radius
        theta_scaled = 0;

    return theta_scaled;
}


//Compute pure scaled rotation (without interpolation)
Image Image::ScaledRotation(double theta, double radius,
                            double center_x, double center_y){

    //Create a new image that will be the rotation of the original image
    cv::Mat new_mat = cv::Mat::ones(rows,cols,CV_32F);
    Image new_img(new_mat);

    //Auxiliary indexing variables
    double x, y, x_prime, y_prime;
    int i_prime, j_prime;
    double theta_prime;

    //Coordinates of the origin of the wanted circle
    int origin_x = rows*center_x;
    int origin_y = cols*center_y;

    //Creation of a point, at the origin of the wanted circle
    cv::Point origin (origin_x,origin_y);

    //Loop over all pixel in original image
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            //Calculation of theta_prime
            theta_prime = ThetaScaled(i, j, origin, radius, theta);

            //Transform indices to double
            IntToDoubleIndex(i, j, x, y);

            //Rotate indices
            RotateIndices(x, y, theta_prime, x_prime, y_prime);

            //Transform rotated pixel indices back to integer indices
            DoubleToIntIndex(x_prime, y_prime, i_prime, j_prime);

            //Check if computed pixel is in range (0,rows)x(0,cols)
            if ((i_prime < 0) ||(i_prime >= rows)) continue;
            if ((j_prime < 0) ||(j_prime >= cols)) continue;

            //Set new pixel to intensity of original pixel
            new_img(i_prime, j_prime) = (*this)(i, j);
        }
    }

    return new_img;

}

//Backward method for performing image scaled rotation with bilinear interpolation
Image Image::InverseScaledRotation(double theta, double radius,
                                    double center_x, double center_y){

    //Get maximum of rows and cols
    int max = std::max(rows,cols);

    //Create a new image that will be the rotation of the original image.
    // Pixels get the default value 1
    cv::Mat new_mat = cv::Mat::ones(rows,cols,CV_32F);
    Image new_img(new_mat);

    //Auxiliary variables
    double x, y, x_rot, y_rot;
    int neighbour_x, neighbour_y;
    double interp_x1, interp_x2, dist_x, dist_y;

    //Scaled theta or the rotation
    double theta_prime;

    //Coordinates of the origin of the wanted circle
    int origin_x = rows*center_x;
    int origin_y = cols*center_y;

    //Creation of a point, at the orig in of the wanted circle
    cv::Point origin (origin_x,origin_y);

    //Loop over all pixels in rotated image
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            //Calculation of theta_prime
            theta_prime = ThetaScaled(i, j, origin, radius, theta);

            //Transform pixel indices to coordinates in [-1,1]x[-a,a],
            // where a is aspect ratio of the image
            IntToDoubleIndex(i, j, x, y);

            //Rotate the coordinates by a given value theta
            RotateIndices(x, y, 2*M_PI - theta_prime, x_rot, y_rot);

            //Transform the coordinates back to the [0,rows-1]x[0,cols-1] range
            x_rot = (x_rot*max + rows)/2.;
            y_rot = (y_rot*max + cols)/2.;

            //Determine indices of nearest neighbouring pixel of given coordinate
            neighbour_x = floor(x_rot);
            neighbour_y = floor(y_rot);

            //Check if computed neighbouring pixel is in range [0,rows-1]x[0,cols-1];
            //If it is not, continue with next pixel, current pixel will
            // keep default value 1
            if ((neighbour_x < 0) || (neighbour_x >=rows)) continue;
            if ((neighbour_y < 0) || (neighbour_y >=cols)) continue;

            //Compute distance of coordinates to neighbouring pixel
            // in x- and y-direction
            dist_x = x_rot - neighbour_x;
            dist_y = y_rot - neighbour_y;

            //Handle boundaries seperately
            if ((neighbour_x == rows-1)&&(neighbour_y == cols-1)) {
                new_img(i,j) = (*this)(rows-1,cols-1);
            } else if (neighbour_x == rows-1) {
                //Interpolation in y-direction
                new_img(i, j) = (1.-dist_y)*(*this)(neighbour_x,neighbour_y) + dist_y*(*this)(neighbour_x,neighbour_y+1);
            } else if (neighbour_y == cols-1) {
                //Interpolation in x-direction
                new_img(i, j) = (1.-dist_x)*(*this)(neighbour_x,neighbour_y) + dist_x*(*this)(neighbour_x+1,neighbour_y);
            } else {
                //Bilinear interpolation
                //Interpolate value in x-direction
                interp_x1 = (1.-dist_x)*(*this)(neighbour_x,neighbour_y)
                            + dist_x*(*this)(neighbour_x+1,neighbour_y);
                interp_x2 = (1.-dist_x)*(*this)(neighbour_x,neighbour_y+1)
                            + dist_x*(*this)(neighbour_x+1,neighbour_y+1);
                //Interpolation in y-direction
                new_img(i, j) = (1.-dist_y)*interp_x1 + dist_y*interp_x2;
            }
        }
    }

    return new_img;
}


Image Image::Translation(double px, double py)
{
    cv::Mat new_mat = cv::Mat::ones(rows, cols, CV_32F);
    Image new_img(new_mat);
    double x, y;
    double x_trans, y_trans;
    int neighbour_x, neighbour_y;
    double interp_x1, interp_x2, dist_x, dist_y;


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            x_trans = i + py;
            y_trans = j + px;

            //Determine indices of nearest neighbouring pixel of given coordinate
            neighbour_x = floor(x_trans);
            neighbour_y = floor(y_trans);

            //Check if computed neighbouring pixel is in range [0,rows-1]x[0,cols-1];
            //If it is not, continue with next pixel, current pixel will
            // keep default value 1
            if ((neighbour_x < 0) || (neighbour_x >= rows))
                continue;
            if ((neighbour_y < 0) || (neighbour_y >= cols))
                continue;

            //Compute distance of coordinates to neighbouring pixel
            // in x- and y-direction
            dist_x = x_trans - neighbour_x;
            dist_y = y_trans - neighbour_y;

            //Handle boundaries seperately
            if ((neighbour_x == rows - 1) && (neighbour_y == cols - 1)){

                new_img(i, j) = pixels(rows - 1, cols - 1);

            } else if (neighbour_x == rows - 1){

                //Interpolation in y-direction
                new_img(i, j) = (1. - dist_y) * pixels(neighbour_x, neighbour_y) + dist_y * pixels(neighbour_x, neighbour_y + 1);
            
            } else if (neighbour_y == cols - 1){

                //Interpolation in x-direction
                new_img(i, j) = (1. - dist_x) * pixels(neighbour_x, neighbour_y) + dist_x * pixels(neighbour_x + 1, neighbour_y);
            
            } else {

                //Bilinear interpolation
                //Interpolate value in x-direction
                interp_x1 = (1. - dist_x) * pixels(neighbour_x, neighbour_y) + dist_x * pixels(neighbour_x + 1, neighbour_y);
                interp_x2 = (1. - dist_x) * pixels(neighbour_x, neighbour_y + 1) + dist_x * pixels(neighbour_x + 1, neighbour_y + 1);
                //Interpolation in y-direction
                new_img(i, j) = (1. - dist_y) * interp_x1 + dist_y * interp_x2;

            }
        }
    }

    return new_img;
}




//MORPHOLOGICAL FILTER

Image Image::BinarizeNaive(float threshold)
{
    //Conversion to grayscale
    cv::Mat_<uchar> grayscale = this->from1to255();
    Image res(cv::Mat_<float>(rows, cols, (int)0));

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (grayscale(i, j) > threshold)
                res(i, j) = 1;
            else
                res(i, j) = 0;
        }
    }

    return res;
}


Image Image::Binarize()
{
    //Conversion to grayscale
    cv::Mat_<uchar> grayscale = this->from1to255();

    //Initialization of the parameters
    int N = rows * cols;
    float threshold(0);
    float muT(0), omega(0), mu(0);
    float numerator(0), denominator(1);
    float var_max(0), sigmaB2(0);
    int max_intensity = 255;

    std::vector<float> histogram(max_intensity + 1, 0);
    Image res(cv::Mat_<float>(rows, cols, (int)0));

    //Creation of the intensity histogram
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++)
            histogram[grayscale(i, j)]++;
    }

    //Normalization of histogram and
    //initialization of muT
    for (int i = 0; i <= max_intensity; i++){
        histogram[i] /= N;
        muT += i * histogram[i];
    }

    //Otsu's method
    for (int t = 0; t <= max_intensity; t++){
        omega += histogram[t];

        if (omega == 0)
            continue;

        mu += t * histogram[t];
        numerator = pow(muT * omega - mu, 2);
        denominator = omega * (1 - omega);
        sigmaB2 = numerator / denominator;

        //Test to chose the optimal threshold
        if (sigmaB2 > var_max){
            threshold = t;
            var_max = sigmaB2;
        }
    }

    //Classification
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (grayscale(i, j) > threshold)
                res(i, j) = 1;
            else
                res(i, j) = 0;
        }
    }

    return res;
}


//Boundary conditions not treated yet
Image Image::ErodeNaive(std::vector<cv::Point> struct_elt)
{
    Image bin = this->Binarize();
    Image swapped = -bin;
    Image res(cv::Mat_<float>(rows, cols, 1));
    std::vector<cv::Point> high_intensity;

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (swapped(i, j) == 1)
                // Point(j, i) because j represents x and i y
                high_intensity.push_back(cv::Point(j, i));
        }
    }

    for (int i = 1; i < rows - 1; i++){
        for (int j = 1; j < cols - 1; j++){
            for (auto ii : struct_elt){
                if (std::find(high_intensity.begin(), high_intensity.end(), cv::Point(j, i) + ii) == high_intensity.end())
                    res(i, j) = 0;
            }
        }
    }

    return -res;
}


//Boundary conditions not treated yet
Image Image::DilateNaive(std::vector<cv::Point> struct_elt)
{
    Image swapped = -(*this);
    Image res = swapped.ErodeNaive(struct_elt);

    return -res;
}


//Pour améliorer, utiliser les histogrammes ! Et en niveau de gris
//Binariser les images déjà modifiées
Image Image::ErodeBin(cv::Mat_<float> kernel)
{
    Image bin = this->Binarize();
    Image res(cv::Mat_<float>(rows, cols, (int) 0));
    int ii, jj;

    for (int y = 0; y < rows; y++){
        for (int x = 0; x < cols; x++){
            for (int j = 0; j < kernel.rows; j++){
                for (int i = 0; i < kernel.cols; i++){

                    //Tests for boundary conditions
                    ii = x - i;
                    jj = y - j;

                    if (ii < 0)
                        ii = 0;
                    if (jj < 0)
                        jj = 0;
                    if (bin(jj, ii) == 1 && kernel(j, i) == 1){
                        res(y, x) = 1;
                        break;
                    }
                }
            }
        }
    }

    return res;
}


Image Image::DilateBin(cv::Mat_<float> kernel)
{
    Image swapped = -(*this);
    Image res = swapped.ErodeBin(kernel);

    return -res;
}


Image Image::ErodeGray(cv::Mat_<float> kernel)
{
    double min, max;
    cv::Mat_<uchar> grayscale = (-(*this)).from1to255();
    cv::Mat_<uchar> tmp(kernel.rows, kernel.cols, (int)0);
    cv::Mat_<float> res(rows, cols, 255);
    int ii, jj;

    for (int y = 0; y < rows; y++){
        for (int x = 0; x < cols; x++){
            for (int j = 0; j < kernel.rows; j++){
                for (int i = 0; i < kernel.cols; i++){
                    //Tests for boundary conditions
                    ii = x - i;
                    jj = y - j;

                    if (ii < 0)
                        ii = 0;
                    if (jj < 0)
                        jj = 0;

                    tmp(j, i) = abs(grayscale(jj, ii) - kernel(j, i));
                    minMaxLoc(tmp, &min, &max);
                    res(y, x) = min;
                }
            }
        }
    }
    cv::normalize(res, res, 0, 1, cv::NORM_MINMAX);

    return -Image(res);
}


Image Image::DilateGray(cv::Mat_<float> kernel)
{
    Image swapped = -(*this);
    Image res = swapped.ErodeGray(kernel);

    return -res;
}


Image Image::Erode(cv::Mat_<float> kernel, std::string erosion_type)
{
    if (erosion_type == "binary")
        return this->ErodeBin(kernel);

    else if (erosion_type == "grayscale")
        return this->ErodeGray(kernel);

    else if (erosion_type == "complex"){
        double min, max;
        double dist, dist_max;
        cv::Mat_<uchar> grayscale = (-(*this)).from1to255();
        cv::Mat_<uchar> tmp(kernel.rows, kernel.cols, (int) 0);
        cv::Mat_<float> res(rows, cols, 255);
        cv::Point center = this->center();
        int ii, jj;

        dist_max = distance_max(pixels, center.x, center.y);

        for (int y = 0; y < rows; y++){
            for (int x = 0; x < cols; x++){
                for (int j = 0; j < kernel.rows; j++){
                    for (int i = 0; i < kernel.cols; i++){
                        //Tests for boundary conditions
                        ii = x - i;
                        jj = y - j;

                        if (ii < 0)
                            ii = 0;
                        if (jj < 0)
                            jj = 0;

                        dist = cv::norm(cv::Point(ii, jj) - center);

                        // if (dist > 50) {
                            tmp(j, i) = abs(grayscale(jj, ii) - dist * kernel(j, i));
                            minMaxLoc(tmp, &min, &max);
                            res(y, x) = min;
                        // } else {
                        //     res(y, x) = grayscale.at<uchar>(y, x);
                        // }

                    }
                }
            }
        }
        cv::normalize(res, res, 0, 1, cv::NORM_MINMAX);

        return -Image(res);
    } else
        throw std::runtime_error("Unknown operation. Supported types: binary, grayscale, complex");


}


Image Image::Dilate(cv::Mat_<float> kernel, std::string dilation_type)
{
    Image swapped = -(*this);
    Image res = swapped.Erode(kernel, dilation_type);

    return -res;
}


//BUG
Image Image::Skeletonize()
{
    Image bin = this->Binarize();
    bin = -bin;
    Image tmp(cv::Mat_<float>(rows, cols, (int) 0));
    int N(0), S(0);
    int ii, jj, xx, yy;
    bool eight_neighbours = true;
    //To store de values of the neighbours and calculate S
    std::vector<int>(8, -1);
    int p2(0), p3(0), p4(0), p5(0), p6(0), p7(0), p8(0), p9(0);
    int counter = 0;
    int counters = 25;

    do {
        counter = 0;
        std::cout << counter << std::endl;
        //STEP 1
        for (int y = 1; y < rows-1; y++) {
            for (int x = 1; x < cols-1; x++) {
                //8-Neighbourhood
                N = -bin(y, x);
                for (int j = -1; j < 2; j++) {
                    for (int i = -1; i < 2; i++) {
                        //Boundary conditions
                        ii = x + i;
                        jj = y + j;

                        //Attention, test si > rows et cols aussi non ?
                        if (ii < 0) {
                            ii = 0;
                            eight_neighbours = false;
                        } if (jj < 0) {
                            jj = 0;
                            eight_neighbours = false;
                        }

                        N += bin(jj, ii);
                        //Trouver un moyen de calculer S

                    }

                    //Conditions
                    //Attention, x +/- 1 et y +/- 1 ne sont pas forcément définis
                    if (y-1 < 0) {
                        yy = 0;
                        xx = x;
                        p2 = bin(yy, xx);

                        if (x-1 < 0) {
                            xx = 0;
                            p9 = bin(yy, xx);
                        } else if (x+1 >= cols) {
                            xx = cols-1;
                            p3 = bin(yy, xx);
                        }

                    } else if (y+1 >= rows) {
                        yy = rows-1;
                        xx = x;
                        p6 = bin(yy, xx);

                        if (x-1 < 0) {
                            xx = 0;
                            p7 = bin(yy, xx);
                        } else if (x+1 >= cols) {
                            xx = cols-1;
                            p5 = bin(yy, xx);
                        }

                    } else {
                        yy = y-1;
                        xx = x;
                        p2 = bin(yy, xx);

                        if (x-1 < 0) {
                            xx = 0;
                            p9 = bin(yy, xx);
                        } else if (x+1 >= cols) {
                            xx = cols-1;
                            p3 = bin(yy, xx);
                        }

                        yy = y+1;
                        xx = x;
                        p2 = bin(yy, xx);

                        if (x-1 < 0) {
                            xx = 0;
                            p9 = bin(yy, xx);
                        } else if (x+1 >= cols) {
                            xx = cols-1;
                            p3 = bin(yy, xx);
                        }

                    }

                    if (x-1 < 0) {
                        p8 = bin(y, x);
                    } else {
                        p8 = bin(y, x-1);
                    }

                    if (x+1 >= cols) {
                        p4 = bin(y, x);
                    } else {
                        p4 = bin(y, x+1);
                    }

                    S = 0;
                    if (p2 == 0 && p3 == 1) S++;
                    if (p3 ==0 && p4 == 1) S++;
                    if (p4 == 0 && p5 == 1) S++;
                    if (p5 == 0 && p6 == 1) S++;
                    if (p6 == 0 && p7 == 1) S++;
                    if (p7 == 0 && p8 == 1) S++;
                    if (p8 == 0 && p9 == 1) S++;
                    if (p9 == 0 && p2 == 1) S++;

                    // p2 = y-1 < 0 ? bin(y, x) : bin(y-1, x);
                    // p4 = x+1 >= cols ? bin(y, x) : bin(y, x+1);
                    // p6 = y+1 >= rows ? bin(y, x) : bin(y+1, x);
                    // p8 = x-1 < 0 ? bin(y, x) : bin(y, x-1);

                    if (eight_neighbours &&
                        2 <= N && N <= 6 &&
                        S == 1 &&
                        p2 * p4 * p6 == 0 &&
                        p4 * p6 * p8 == 0) {
                        tmp(y, x) = 1;
                        counter++;
                    }
                }
            }
        }

        //Setting noted points to zero
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                if (tmp(y, x) == 1) {
                    bin(y, x) = 0;
                    //Reinitializing tmp
                    tmp(y, x) = 0;
                }
            }
        }

        eight_neighbours = true;

        //STEP 2
        for (int y = 1; y < rows-1; y++) {
            for (int x = 1; x < cols-1; x++) {
                //8-Neighbourhood
                N = -bin(y, x);
                for (int j = -1; j < 2; j++) {
                    for (int i = -1; i < 2; i++) {
                        //Boundary conditions
                        ii = x + i;
                        jj = y + j;

                        //Attention, test si > rows et cols aussi non ?
                        if (ii < 0) {
                            ii = 0;
                            eight_neighbours = false;
                        } else if (ii >= cols) {
                            ii = cols-1;
                            eight_neighbours = false;
                        }

                        if (jj < 0) {
                            jj = 0;
                            eight_neighbours = false;
                        } else if (jj >= rows) {
                            jj = rows-1;
                            eight_neighbours = false;
                        }

                        N += bin(jj, ii);
                        //Trouver un moyen de calculer S

                    }

                    //Conditions
                    //Attention, x +/- 1 et y +/- 1 ne sont pas forcément définis
                    if (y-1 < 0) {
                        yy = 0;
                        xx = x;
                        p2 = bin(yy, xx);

                        if (x-1 < 0) {
                            xx = 0;
                            p9 = bin(yy, xx);
                        } else if (x+1 >= cols) {
                            xx = cols-1;
                            p3 = bin(yy, xx);
                        }

                    } else if (y+1 >= rows) {
                        yy = rows-1;
                        xx = x;
                        p6 = bin(yy, xx);

                        if (x-1 < 0) {
                            xx = 0;
                            p7 = bin(yy, xx);
                        } else if (x+1 >= cols) {
                            xx = cols-1;
                            p5 = bin(yy, xx);
                        }

                    } else {
                        yy = y-1;
                        xx = x;
                        p2 = bin(yy, xx);

                        if (x-1 < 0) {
                            xx = 0;
                            p9 = bin(yy, xx);
                        } else if (x+1 >= cols) {
                            xx = cols-1;
                            p3 = bin(yy, xx);
                        }

                        yy = y+1;
                        xx = x;
                        p2 = bin(yy, xx);

                        if (x-1 < 0) {
                            xx = 0;
                            p9 = bin(yy, xx);
                        } else if (x+1 >= cols) {
                            xx = cols-1;
                            p3 = bin(yy, xx);
                        }

                    }

                    if (x-1 < 0) {
                        p8 = bin(y, x);
                    } else {
                        p8 = bin(y, x-1);
                    }

                    if (x+1 >= cols) {
                        p4 = bin(y, x);
                    } else {
                        p4 = bin(y, x+1);
                    }

                    S = 0;
                    if (p2 == 0 && p3 == 1) S++;
                    if (p3 ==0 && p4 == 1) S++;
                    if (p4 == 0 && p5 == 1) S++;
                    if (p5 == 0 && p6 == 1) S++;
                    if (p6 == 0 && p7 == 1) S++;
                    if (p7 == 0 && p8 == 1) S++;
                    if (p8 == 0 && p9 == 1) S++;
                    if (p9 == 0 && p2 == 1) S++;
                    // std::cout << "S: " << S << std::endl;
                    // std::cout << "N: " << N << std::endl;
                    // std::cout << p2 << p4 << p6 << p8 << std::endl;

                    // p2 = y-1 < 0 ? bin(y, x) : bin(y-1, x);
                    // p4 = x+1 >= cols ? bin(y, x) : bin(y, x+1);
                    // p6 = y+1 >= rows ? bin(y, x) : bin(y+1, x);
                    // p8 = x-1 < 0 ? bin(y, x) : bin(y, x-1);

                    if (eight_neighbours &&
                        2 <= N && N <= 6 &&
                        S == 1 &&
                        p2 * p4 * p6 == 0 &&
                        p2 * p6 * p8 == 0) {
                        tmp(y, x) = 1;
                        counter++;
                    }
                }
            }
        }

        //Setting noted points to zero
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                if (tmp(y, x) == 1) {
                    bin(y, x) = 0;
                    //Reinitializing tmp
                    tmp(y, x) = 0;
                }
            }
        }
        std::cout << counter << std::endl;

        eight_neighbours = true;
        counters--;
    } while(counters != 0);

    return -bin;
}


//TODO: skeletonization (ZS thinning) (create a method)
//TODO: conversion of a dry finger to a clean image with skeletonization and dilatation (create a method)
//TODO: conversion of a moist finger to a clean image with erosion (?) (create a method)
//TODO: deconvolution (algorithm to approximate the blurring kernel) to unblur an image (create a method)
