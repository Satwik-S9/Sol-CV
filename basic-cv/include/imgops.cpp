#include <iostream>
#include "imgops.h"

cv::Mat addTwoImgs(cv::Mat img1, cv::Mat img2) {
    if (img1.size != img2.size) 
        throw std::invalid_argument(" Image Dimension mismatch");

    cv::Mat res = cv::Mat::zeros(cv::Size(img1.rows, img1.cols), CV_8UC3);
    res = img1 + img2;
    return res;
}

cv::Mat subTwoImgs(cv::Mat img1, cv::Mat img2) {
    if (img1.size != img2.size) 
        throw std::invalid_argument(" Image Dimension mismatch");

    cv::Mat res = cv::Mat::zeros(cv::Size(img1.rows, img1.cols), CV_8UC3);
    res = img1 - img2;
    return res;
}

cv::Mat affDot(cv::Mat ma1, cv::Mat ma2) {
    cv::Mat m1, m2;
    ma1.convertTo(m1, CV_64F);
    ma2.convertTo(m2, CV_64F);
    if (m1.cols == m2.rows && m1.cols == 3 && m2.rows == 3) {
        cv::Mat res = cv::Mat::zeros(m1.rows, m2.cols, CV_64F);
        for (int i=0; i<m1.rows; i++) {
            cv::Mat temp1 = cv::Mat(m1.at<cv::Vec3d>(i));
            res.at<double>(i, 0) = temp1.dot(m2); 
        }
        return res;
    } else {
        throw std::invalid_argument("Dimension Mismatch");
    }
}