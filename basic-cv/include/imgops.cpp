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

cv::Mat imgDot(cv::Mat m1, cv::Mat m2) {
    cv::Mat img_copy;

    if (m1.cols == m2.rows) {
        cv::Mat res = cv::Mat::zeros(m1.rows, m2.cols, CV_8UC3);
        for (int i=0; i<m1.rows; i++) {
            for (int j=0; j<m2.cols; j++) {
                int sum = 0;
                for (int k=0; k<m2.rows; k++) {
                    sum += m1.at<uchar>(i, k) * m2.at<uchar>(k, i);
                }
                res.at<uchar>(i, j) = sum;
            }
        }
        return res;
    } else {
        throw std::invalid_argument("Dimension Mismatch");
    }
}