#include <iostream>
#include <math.h>
#include "transforms.h"
#include "imgops.h"

cv::Mat affineTransform(cv::Mat img, cv::Mat T) {
    cv::Mat res(img.rows, img.cols, CV_8UC3, cv::Scalar(0, 0, 0));
    // printf("CREATED MATRIX\n");

    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            // obtain the new positions
            cv::Mat pv({i, j, 1});
            cv::Mat posVec = affDot(T, pv);
            
            int ni = (int)posVec.at<double>(0);
            int nj = (int)posVec.at<double>(1);
            // std::cout << i << " "  << j << " " << ni << " " << nj << "\n";
            // fprintf(stream, "i: %d, j: %d, ni: %d, nj: %d\n", i, j, ni, nj);
           
            if (ni < img.rows && nj < img.cols) {
                // put in the values
                res.at<cv::Vec3b>(i, j)[0] = img.at<cv::Vec3b>(ni, nj)[0];
                res.at<cv::Vec3b>(i, j)[1] = img.at<cv::Vec3b>(ni, nj)[1];
                res.at<cv::Vec3b>(i, j)[2] = img.at<cv::Vec3b>(ni, nj)[2];
            } 
        }
    }
    return res;
}

cv::Mat getTransformMatrix(double paramX, double paramY, char operation) {
    cv::Mat T = cv::Mat::eye(3, 3, CV_64F);
    if (operation == 't') {
        T.at<double>(0, 2) = paramX; 
        T.at<double>(1, 2) = paramY;
        return T; 
    } else if (operation == 'r') {
        double theta;
        if (paramY == 1) theta = CV_PI/180 * paramX;
        else theta = paramX;

        T.at<double>(0, 0) *= cos(theta);
        T.at<double>(0, 1) *= -sin(theta);
        T.at<double>(1, 0) *= sin(theta);
        T.at<double>(0, 1) *= cos(theta);
        
        return T; 
    } else if (operation == 's') {
        T.at<double>(0, 1) *= paramX; 
        T.at<double>(1, 0) *= paramY;
        return T; 
    } else {
        throw std::invalid_argument("invalid operation");
    }
    return T;
}

cv::Mat fillTransformMatrix(cv::Mat &T, double paramX, double paramY, char operation) {
    if (operation == 't') {
        T.at<double>(0, 2) += paramX; 
        T.at<double>(1, 2) += paramY;
    } else if (operation == 'r') {
        double theta;
        if (paramY == 1.0) theta = CV_PI/180 * paramX;
        else theta = paramX;
        
        if (T.at<double>(0, 0) == 0) T.at<double>(0, 0) = cos(theta);
        else T.at<double>(0, 0) *= cos(theta);
        
        if (T.at<double>(0, 1) == 0) T.at<double>(0, 1) = -sin(theta);
        else T.at<double>(0, 1) *= -sin(theta);
        
        if (T.at<double>(1, 0) == 0) T.at<double>(1, 0) = sin(theta);
        else T.at<double>(1, 0) *= sin(theta);
        
        if (T.at<double>(1, 1) == 0) T.at<double>(1, 1) = cos(theta);
        else T.at<double>(1, 1) *= cos(theta);

    } else if (operation == 's') {
        T.at<double>(0, 1) *= paramX; 
        T.at<double>(1, 0) *= paramY;
    } else {
        throw std::invalid_argument("invalid operation");
    }
    return T;
}

cv::Mat fillTransformMatrix2(cv::Mat &T, double paramX, double paramY, char operation) {
    cv::Mat temp = cv::Mat::eye(3, 3, CV_64F);
    
    if (operation == 't') {
        temp.at<double>(0, 2) += paramX; 
        temp.at<double>(1, 2) += paramY;
        T = temp * T;
    } 
    else if (operation == 'r') {
        double theta;
        if (paramY == 1.0) theta = CV_PI/180 * paramX;
        else theta = paramX;
        
        // create matrix for rotation
        temp.at<double>(0, 0) = cos(theta);
        temp.at<double>(0, 1) = -sin(theta);
        temp.at<double>(1, 0) = sin(theta);
        temp.at<double>(1, 1) = cos(theta);
        
        // compose new transformation matrix
        T = temp * T;
    } 
    else if (operation == 's') {
        temp.at<double>(0, 0) = paramX; 
        temp.at<double>(1, 1) = paramY;
        T = temp * T;
    } 
    else {
        throw std::invalid_argument("invalid operation");
    }
    return T;
}


cv::Mat getTransformMatrix(std::vector<double> &params, std::string opStr) {    
    if (params.size() != 2*opStr.length()) 
        throw std::invalid_argument("Missing Operation Parameters");

    cv::Mat T = cv::Mat::eye(3, 3, CV_64F);
    for (int i=0; i<2*opStr.length(); i+=2) {
        fillTransformMatrix(T, params[i], params[i+1], opStr[i/2]);
    }
    return T;
}

cv::Mat getTransformMatrix2(std::vector<double> &params, std::string opStr) {    
    if (params.size() != 2*opStr.length()) 
        throw std::invalid_argument("Missing Operation Parameters");

    cv::Mat T = cv::Mat::eye(3, 3, CV_64F);
    for (int i=0; i<2*opStr.length(); i+=2) {
        fillTransformMatrix2(T, params[i], params[i+1], opStr[i/2]);
    }
    return T;
}

cv::Mat shiftDiff(cv::Mat img, int v, int axis) {
    if (axis > 2) throw std::invalid_argument("axis must be 0 or 1");
    
    cv::Mat T;
    if (axis == 0) T = getTransformMatrix(v, 0, 't');
    else if (axis == 1) T = getTransformMatrix(0, v, 't');
    else T = getTransformMatrix(v, v, 't');

    cv::Mat tempRes = affineTransform(img, T);
    cv::Mat res = img - tempRes;
    return res;
}

std::pair<int, int> shearCoord(double theta, int x, int y) {
    /*
    |1  -tan(𝜃/2) |  |1        0|  |1  -tan(𝜃/2) | 
    |0      1     |  |sin(𝜃)   1|  |0      1     |
    */

   // shear 1
   double tangent = tan(theta/2);
   int new_x = floor(x - y*tangent);
   int new_y = y;

   // shear 2
   new_y = floor(new_x*sin(theta) + new_y);

   // shear 3
   new_x = floor(new_x - new_y*tangent); 
   return {new_y, new_x};
}

cv::Mat rotate(cv::Mat img, double theta, bool deg, bool aliasing) {
    if (deg) theta = (CV_PI/180) * theta;
    int rows = img.rows, cols = img.cols;
    
    if (aliasing) {
        double sine = sin(theta), cosine = cos(theta);

        int nrows = abs((double)rows*cosine + abs((double)cols*sine))+1;
        int ncols = abs((double)cols*cosine + abs((double)rows*sine))+1;

        cv::Mat output(nrows, ncols, CV_8UC3, cv::Scalar(0, 0, 0));
        int original_centre_height = floor(((rows+1)/2)-1);    
        int original_centre_width = floor(((cols+1)/2)-1); 

        int new_centre_height = floor(((nrows+1)/2)-1);
        int new_centre_width = floor(((ncols+1)/2)-1);

        for (int i=0; i<rows; i++) {
            for (int j=0; j<cols; j++) {
                int y = rows - 1 - i - original_centre_height;
                int x = cols - 1 - j - original_centre_width;

                int new_y = floor(-(double)x*sine + (double)y*cosine);
                int new_x = floor((double)x*cosine + (double)y*sine);
                
                new_y = new_centre_height - new_y;
                new_x = new_centre_width - new_x;

                if (new_x >= 0 && ncols > new_x && new_y >= 0 && nrows > new_y) {
                    output.at<cv::Vec3b>(new_y, new_x)[0] = img.at<cv::Vec3b>(i, j)[0];
                    output.at<cv::Vec3b>(new_y, new_x)[1] = img.at<cv::Vec3b>(i, j)[1];
                    output.at<cv::Vec3b>(new_y, new_x)[2] = img.at<cv::Vec3b>(i, j)[2];
                }
            }
        }
        return output;
    }
    else {
        double sine = sin(theta), cosine = cos(theta);

        int nrows = abs((double)rows*cosine + abs((double)cols*sine))+1;
        int ncols = abs((double)cols*cosine + abs((double)rows*sine))+1;

        cv::Mat output(nrows, ncols, CV_8UC3, cv::Scalar(0, 0, 0));
        int original_centre_height = floor(((rows+1)/2)-1);    
        int original_centre_width = floor(((cols+1)/2)-1); 

        int new_centre_height = floor(((nrows+1)/2)-1);
        int new_centre_width = floor(((ncols+1)/2)-1);

        for (int i=0; i<rows; i++) {
            for (int j=0; j<cols; j++) {
                int y = rows - 1 - i - original_centre_height;
                int x = cols - 1 - j - original_centre_width;

                std::pair<int, int> p = shearCoord(theta, x, y);
                int new_y = p.first;
                int new_x = p.second;
                
                new_y = new_centre_height - new_y;
                new_x = new_centre_width - new_x;

                if (new_x >= 0 && ncols > new_x && new_y >= 0 && nrows > new_y) {
                    output.at<cv::Vec3b>(new_y, new_x)[0] = img.at<cv::Vec3b>(i, j)[0];
                    output.at<cv::Vec3b>(new_y, new_x)[1] = img.at<cv::Vec3b>(i, j)[1];
                    output.at<cv::Vec3b>(new_y, new_x)[2] = img.at<cv::Vec3b>(i, j)[2];
                }
            }
        }
        return output;
    }
    return img;
}

cv::Mat rotate(cv::Mat img, double theta, bool deg) {
    if (deg) theta = (CV_PI/180.0) * theta;
    int rows = img.rows, cols = img.cols;

    double sine = sin(theta), cosine = cos(theta);

    int nrows = abs((double)rows*cosine + abs((double)cols*sine))+1;
    int ncols = abs((double)cols*cosine + abs((double)rows*sine))+1;

    cv::Mat output(nrows, ncols, CV_8UC3, cv::Scalar(0, 0, 0));
    int original_centre_height = floor(((rows+1)/2)-1);    
    int original_centre_width = floor(((cols+1)/2)-1); 

    int new_centre_height = floor(((nrows+1)/2)-1);
    int new_centre_width = floor(((ncols+1)/2)-1);

    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            int y = rows - 1 - i - original_centre_height;
            int x = cols - 1 - j - original_centre_width;

            std::pair<int, int> p = shearCoord(theta, x, y);
            int new_y = p.first;
            int new_x = p.second;
            
            new_y = new_centre_height - new_y;
            new_x = new_centre_width - new_x;

            if (new_x >= 0 && ncols > new_x && new_y >= 0 && nrows > new_y) {
                output.at<cv::Vec3b>(new_y, new_x)[0] = img.at<cv::Vec3b>(i, j)[0];
                output.at<cv::Vec3b>(new_y, new_x)[1] = img.at<cv::Vec3b>(i, j)[1];
                output.at<cv::Vec3b>(new_y, new_x)[2] = img.at<cv::Vec3b>(i, j)[2];
            }
        }
    }
    return output;
}

cv::Mat shear(cv::Mat img, double theta, bool deg, int axis) {
    if (deg) theta = (CV_PI/180.0) * theta;
    int rows = img.rows, cols = img.cols;

    double sine = sin(theta), cosine = cos(theta);

    int nrows = abs((double)rows*cosine + abs((double)cols*sine))+1;
    int ncols = abs((double)cols*cosine + abs((double)rows*sine))+1;

    cv::Mat output(nrows, ncols, CV_8UC3, cv::Scalar(0, 0, 0));
    int original_centre_height = floor(((rows+1)/2)-1);    
    int original_centre_width = floor(((cols+1)/2)-1); 

    int new_centre_height = floor(((nrows+1)/2)-1);
    int new_centre_width = floor(((ncols+1)/2)-1);
    
    if (axis == 1) {
        for (int i=0; i<rows; i++) {
            for (int j=0; j<cols; j++) {
                int y = rows - 1 - i - original_centre_height;
                int x = cols - 1 - j - original_centre_width;
                
                // shear 1
                double tangent = tan(theta/2);
                int new_x = floor(x - y*tangent);
                int new_y = y;

                new_y = new_centre_height - new_y;
                new_x = new_centre_width - new_x;

                if (new_x >= 0 && ncols > new_x && new_y >= 0 && nrows > new_y) {
                    output.at<cv::Vec3b>(new_y, new_x)[0] = img.at<cv::Vec3b>(i, j)[0];
                    output.at<cv::Vec3b>(new_y, new_x)[1] = img.at<cv::Vec3b>(i, j)[1];
                    output.at<cv::Vec3b>(new_y, new_x)[2] = img.at<cv::Vec3b>(i, j)[2];
                }
            }
        }
        return output;
    } 
    else if (axis == 2) {
        for (int i=0; i<rows; i++) {
            for (int j=0; j<cols; j++) {
                int y = rows - 1 - i - original_centre_height;
                int x = cols - 1 - j - original_centre_width;

                // shear 1
                double tangent = tan(theta/2);
                int new_x = floor(x - y*tangent);
                int new_y = y;

                // shear 2
                new_y = floor(new_x*sin(theta) + new_y);

                new_y = new_centre_height - new_y;
                new_x = new_centre_width - new_x;

                if (new_x >= 0 && ncols > new_x && new_y >= 0 && nrows > new_y) {
                    output.at<cv::Vec3b>(new_y, new_x)[0] = img.at<cv::Vec3b>(i, j)[0];
                    output.at<cv::Vec3b>(new_y, new_x)[1] = img.at<cv::Vec3b>(i, j)[1];
                    output.at<cv::Vec3b>(new_y, new_x)[2] = img.at<cv::Vec3b>(i, j)[2];
                }
            }
        }
        return output;
    }
    else {
        throw std::invalid_argument("axis must be '1' or '2'");
    }
    return img;
}


//! NOT WORKING 
cv::Mat reflect(cv::Mat img, double theta, double x0, double y0, bool deg) {
    if (deg) theta = (CV_PI/180.0) * theta;
    cv::Mat res(img.rows, img.cols, CV_8UC3, cv::Scalar(255, 255, 255));

    for (int i=0; i<img.rows; i++) {
        for (int j=0; j<img.cols; j++) {
            double delta = ((double)i - x0) * sin(theta) - 
                            ((double)j - y0) * cos(theta);
            double ni = i + 2 * delta * (-sin(theta));
            double nj = j + 2 * delta * cos(theta);

            if (ni >= 0 && nj >= 0 && ni < img.rows && nj < img.cols) {
                res.at<cv::Vec3b>((int)ni, (int)nj)[0] = img.at<cv::Vec3b>(i, j)[0];
                res.at<cv::Vec3b>((int)ni, (int)nj)[1] = img.at<cv::Vec3b>(i, j)[1];
                res.at<cv::Vec3b>((int)ni, (int)nj)[2] = img.at<cv::Vec3b>(i, j)[2];
            }
        }
    }
    return res;
}

cv::Mat reflect(cv::Mat img, int axis) {
    if (axis > 1 || axis < -1) throw std::invalid_argument("Invalid Value for axis");

    cv::Mat res(img.rows, img.cols, CV_8UC3, cv::Scalar(255, 255, 255));
    double theta;
    
    if (axis == 0) theta = 0.0;
    else if (axis == 1) theta = (CV_PI/180.0)*90.0;
    else theta = (CV_PI/180.0)*90.0*axis;
    
    for (int i=0; i<img.rows; i++) {
        for (int j=0; j<img.cols; j++) {
            double delta = i * sin(theta) - 
                            j * cos(theta);
            int ni = i + 2 * delta * (-sin(theta));
            int nj = j + 2 * delta * cos(theta);

            if (ni >= 0 && nj >= 0 && ni < img.rows && nj < img.cols) {
                res.at<cv::Vec3b>(ni, nj)[0] = img.at<cv::Vec3b>(i, j)[0];
                res.at<cv::Vec3b>(ni, nj)[1] = img.at<cv::Vec3b>(i, j)[1];
                res.at<cv::Vec3b>(ni, nj)[2] = img.at<cv::Vec3b>(i, j)[2];
            }
        }
    }
    return res;
}