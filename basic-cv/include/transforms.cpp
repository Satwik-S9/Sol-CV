#include "transforms.h"
#include "imgops.h"

cv::Mat affineTransform(cv::Mat img, cv::Mat T) {
    cv::Mat res(img.rows, img.cols, CV_8UC3, cv::Scalar(0, 0, 0));
    // printf("CREATED MATRIX");

    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            // obtain the new positions
            cv::Mat posVec({i, j, 1});
            posVec = imgDot(T, posVec);
            int ni = posVec.at<int>(0);
            int nj = posVec.at<int>(1);
           
            if (ni < img.rows && nj < img.cols) {
                // put in the values
                res.at<cv::Vec3b>(i, j)[0] = img.at<cv::Vec3b>(ni, nj)[0];
                res.at<cv::Vec3b>(i, j)[2] = img.at<cv::Vec3b>(ni, nj)[1];
                res.at<cv::Vec3b>(i, j)[3] = img.at<cv::Vec3b>(ni, nj)[2];
            } 
        }
    }
    return res;
}

cv::Mat getTransformMatrix(int paramX, int paramY, char operation) {
    cv::Mat T = cv::Mat::eye(3, 3, CV_32SC1);
    if (operation == 'T' || operation == 't') {
        T.at<int>(0, 2) = paramX; 
        T.at<int>(1, 2) = paramY;
        return T; 
    } else if (operation == 'R' || operation == 'r') {
        T.at<int>(0, 2) = paramX; 
        T.at<int>(1, 2) = paramY;
        return T; 
    } else if (operation == 'S' || operation == 's') {
        T.at<int>(0, 2) = paramX; 
        T.at<int>(1, 2) = paramY;
        return T; 
    } else {
        throw std::invalid_argument("invalid operation");
    }
    return T;
}

cv::Mat shiftBy(cv::Mat img, int dist, int axis);
cv::Mat shiftDiff(cv::Mat img, int v, int axis);