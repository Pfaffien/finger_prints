#include <iostream>
#include <cmath>

#include "Image.h"


//Constructor 
Image::Image(cv::String name){
    
    //Read the image into a cv::Mat matrix
    pixels = cv::imread(name, 0);
    
    //Check for invalid input
    if (pixels.empty())                   
        std::cerr <<  "Could not open or find the image " << name << std::endl;
    
    //Divide values of matrix by 255 to get floatingpoint values inside [0,1]
    pixels /= 255.;
    
    //Set rows and cols
    rows = pixels.rows;
    cols = pixels.cols;
}

//Constructor
Image::Image(const cv::Mat_<float>& matrix){
    //Clone matrix
    pixels = matrix.clone();
    
    //Set rows and cols
    rows = pixels.rows;
    cols = pixels.cols;
}


//Operator overloading to get intensity value of a pixel
float& Image::operator()(int row, int col){
    //Check for invalid input
    if(row>=rows || row<0 || col>=cols || col<0){
        std::cerr << "Warning: trying to acces pixel outside of image range. Returning pixel (0,0)!\n";
        return pixels(0,0);
    }else{
        return pixels(row,col);
    }
}

//Operator overloading to get the whole image matrix
cv::Mat_<float> Image::operator()(){
    return pixels;
}

//Compute maximal intensity value of image matrix
double Image::Max(){
    double min, max;
    minMaxLoc(pixels, &min, &max);
    return max;
}

//Compute maximal intensity value of image matrix
double Image::Min(){
    double min, max;
    minMaxLoc(pixels, &min, &max);
    return min;
}

//Rectangle
Image Image::Rectangle(int x_begin, int y_begin,
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


//Symmetries
Image Image::Sym_x(){
    
    cv::Mat new_mat = pixels.clone();
    Image new_pixels(new_mat);

    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++)
            new_pixels(i, j) = (*this)(rows-i-1, j);
    }

    return new_pixels;
}

Image Image::Sym_y(){
    
    cv::Mat new_mat = pixels.clone();
    Image new_img(new_mat);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            new_img(i, j) = (*this)(i, cols-j-1);
    }

    return new_img;
}

Image Image::Sym_xy(){
    return (this->Sym_x()).Sym_y();
}


// Conversion from intensity values in [0,1] to values in [0,255]
cv::Mat_<uchar> Image::From1to255()
{
    cv::Mat_<uchar> res = pixels*255;
    return res;
}


//Plotting
void Image::Display(cv::String windowName, cv::String imageName){
    //Convert intensity values back to [0,255]
    cv::Mat_<uchar> disp = this->From1to255();
    //Create a window for displaying
    cv::namedWindow( windowName, cv::WINDOW_AUTOSIZE ); 
    //Show the image inside the created window
    cv::imshow( imageName, disp ); 
    //Wait for a keystroke in the window to close it
    cv::waitKey(0); 
}

//Saving
void Image::Save(std::string s){
    //Convert intensity values back to [0,255]
    cv::Mat_<uchar> disp = this->From1to255();
    //Save image as png-file
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


//Transform indices from [0,rows]x[0,cols] to double indices in [-1,1]x[-a,a], where a is aspect ratio of the image
void Image::IntToDoubleIndex(int i, int j, double& x, double& y){
    
    //Get maximum of rows and cols
    int max = std::max(rows,cols);
    
    //Compute corresponding coordinate of (i,j) in [-1,1]x[-a,a]
    x = (2*i-rows)/(double)max;
    y = (2*j-cols)/(double)max;
}

//Transform indices from [-1,1]x[-a,a] to indices in [0,rows]x[0,cols], by applying the inverse formula of IntToDoubleIndex plus rounding
void Image::DoubleToIntIndex(double x, double y, int& i, int& j){
    
    //Get maximum of rows and cols
    int max = std::max(rows,cols);
    
    //Compute corresponding coordinate of (x,y) in [0,rows]x[0,cols]
    i = round((x*max+rows)/2.);
    j = round((y*max+cols)/2.);
}

//Rotating double indices (x,y) by a given value theta. The resulting indices are called x_prime, y_prime.
void Image::RotateIndices(double x, double y, double theta, double& x_prime, double& y_prime){
    
    x_prime = std::cos(theta)*x-std::sin(theta)*y;
    y_prime = std::sin(theta)*x + std::cos(theta)*y;
}

//Compute pure rotation (without interpolation)
Image Image::Rotation(double theta){
    
    //Create a new image that will be the rotation of the original image
    cv::Mat new_mat = cv::Mat::ones(rows,cols,CV_32F);
    Image new_img(new_mat);
    
    //Auxiliary indexing variables
    double x, y, x_prime, y_prime;
    int i_prime, j_prime;
    
    //Loop over all pixel in original image
    for(int i=0; i<rows;i++){
        for(int j=0;j<cols;j++){
            
            //Transform indices to double
            IntToDoubleIndex(i, j, x, y);
            
            //Rotate indices
            RotateIndices(x, y, theta, x_prime, y_prime);
            
            //Transform rotated pixel indices back to integer indices
            DoubleToIntIndex(x_prime, y_prime, i_prime, j_prime);
            
            //Check if computed pixel is in range (0,rows)x(0,cols)
            if((i_prime < 0) ||(i_prime >=rows)){
                continue;
            }
            if((j_prime < 0) || (j_prime >=cols)){
                continue;
            }
            
            //Set new pixel to intensity of original pixel
            new_img(i_prime, j_prime) = (*this)(i, j); 
        }
    }
    
    return new_img;
    
}

//Apply bilinear interpolation to a given image matrix
void Image::BilinearInterpolation(){
    
    //Loop over all pixels to find the non-affected ones
    for(int i=0; i<rows;i++){
        for(int j=0;j<cols;j++){
            //Check if pixel is corner or boundary pixel
            if((*this)(i,j) == 1){
                if(i==0){
                    if(j==0)
                        (*this)(i,j) = 0.5*((*this)(i+1,j)+(*this)(i,j+1));
                    else if(j==cols-1)
                        (*this)(i,j) = 0.5*((*this)(i+1,j)+(*this)(i,j-1));
                    else
                        (*this)(i,j) = (1./3.)*((*this)(i+1,j)+(*this)(i,j-1)+(*this)(i,j+1));
                }
                else if(i==rows-1){
                    if(j==cols-1)
                        (*this)(i,j) = 0.5*((*this)(i-1,j)+(*this)(i,j-1));
                    else if(j==0)
                        (*this)(i,j) = 0.5*((*this)(i-1,j)+(*this)(i,j+1));
                    else
                        (*this)(i,j) = (1./3.)*((*this)(i-1,j)+(*this)(i,j-1)+(*this)(i,j+1));
                }
                else if(j==0){
                    (*this)(i,j) = (1./3.)*((*this)(i+1,j)+(*this)(i-1,j)+(*this)(i,j+1));
                }
                else if(j==cols-1){
                    (*this)(i,j) = (1./3.)*((*this)(i+1,j)+(*this)(i-1,j)+(*this)(i,j-1));
                }
                //Interpolation for non-boundary pixels
                else
                    (*this)(i,j) = 0.25*((*this)(i-1,j)+(*this)(i+1,j)+(*this)(i,j-1)+(*this)(i,j+1));
            }
            
        }
    }
}


//Backward method for performing image rotation with bilinear interpolation
Image Image::BackwardInterpolation(double theta){
    
    //Get maximum of rows and cols
    int max = std::max(rows,cols);
    
    //Create a new image that will be the rotation of the original image. Pixels get the default value 1
    cv::Mat new_mat = cv::Mat::ones(rows,cols,CV_32F);
    Image new_img(new_mat);
    
    //Auxiliary variables
    double x, y, x_rot, y_rot;
    int neighbour_x, neighbour_y;
    double interp_x1, interp_x2, dist_x, dist_y;
    
    //Loop over all pixels in rotated image
    for(int i=1; i<rows;i++){
        for(int j=1;j<cols;j++){
    
            //Transform pixel indices to coordinates in [-1,1]x[-a,a], where a is aspect ratio of the image
            IntToDoubleIndex(i, j, x, y);
            
            //Rotate the coordinates by a given value theta
            RotateIndices(x, y, theta, x_rot, y_rot);        
            
            //Transform the coordinates back to the [0,rows-1]x[0,cols-1] range
            x_rot = (x_rot*max+rows)/2.;
            y_rot = (y_rot*max+cols)/2.;
            
            //Determine indices of nearest neighbouring pixel of given coordinate
            neighbour_x = floor(x_rot);
            neighbour_y = floor(y_rot);
            
            //Check if computed neighbouring pixel is in range [0,rows-1]x[0,cols-1]
            if((neighbour_x < 0) ||(neighbour_x >=rows)){
                //If true, continue with next pixel, cuurent pixel will keep default value 1
                continue;
            }
            if((neighbour_y < 0) || (neighbour_y >=cols)){
                //If true, continue with next pixel, cuurent pixel will keep default value 1
                continue;
            }
            
            //Compute distance of coordinates to neighbouring pixel in x- and y-direction
            dist_x = x_rot-neighbour_x;
            dist_y = y_rot-neighbour_y; 
            
            //Handle boundaries seperately
            if((neighbour_x == rows-1)&&(neighbour_y == cols-1)){
                new_img(i,j) = (*this)(rows-1,cols-1);
            }else if(neighbour_x == rows-1){
                //Interpolation in y-direction
                new_img(i, j) = (1.-dist_y)*(*this)(neighbour_x,neighbour_y) + dist_y * (*this)(neighbour_x,neighbour_y+1);
            }else if(neighbour_y == cols-1){
                //Interpolation in x-direction
                new_img(i, j) = (1.-dist_x)*(*this)(neighbour_x,neighbour_y) + dist_x * (*this)(neighbour_x+1,neighbour_y);
            }else{
                //Bilinear interpolation
                //Interpolate value in x-direction
                interp_x1 = (1.-dist_x)*(*this)(neighbour_x,neighbour_y)
                            + dist_x*(*this)(neighbour_x+1,neighbour_y);
                interp_x2 = (1.-dist_x)*(*this)(neighbour_x,neighbour_y+1)
                            + dist_x*(*this)(neighbour_x+1,neighbour_y+1);
                //Interpolation in y-direction
                new_img(i, j) = (1.-dist_y)*interp_x1 + dist_y * interp_x2;
            }        
        }
    }
    
    return new_img;
}

//Compute the difference between two image matrices
Image Image::DifferenceMatrix(Image second){
    
    //Create new matrix for storing the difference
    cv::Mat new_mat = cv::Mat::zeros(rows,cols,CV_32F);
    Image image_diff(new_mat);
    
    //Loop over all pixels
    for(int i=0; i<rows;i++){
        for(int j=0;j<cols;j++){
            image_diff(i, j) = std::abs(  (*this)(i,j) - second(i,j) );
        }
    }
    
    return image_diff;
}
