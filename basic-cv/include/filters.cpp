#include "filters.h"

cv::Mat_<cv::Vec3b> sketchFilter(cv::Mat_<cv::Vec3b> img) {
    cv::Mat_<cv::Vec3b> img_copy; 
    img.copyTo(img_copy);

    for (int i=0; i < img_copy.rows; i++) {
        for (int j=0; j < img_copy.cols; j++) {
            for (int c = 0; c < img_copy.channels(); c++) {
                if (img_copy.at<cv::Vec3b>(i, j)[c] <= 0 
                    && img_copy.at<cv::Vec3b>(i, j)[c] < 64) 
                {
                    img_copy.at<cv::Vec3b>(i, j)[c] = 0;
                } 
                else if (img_copy.at<cv::Vec3b>(i, j)[c] <= 64
                            && img_copy.at<cv::Vec3b>(i, j)[c] < 128) 
                {
                    img_copy.at<cv::Vec3b>(i, j)[c] = 64;
                }
                else if (img_copy.at<cv::Vec3b>(i, j)[c] <= 128
                            && img_copy.at<cv::Vec3b>(i, j)[c] < 192) 
                {
                    img_copy.at<cv::Vec3b>(i, j)[c] = 128;
                } else img_copy.at<cv::Vec3b>(i, j)[c] = 192;
            }
        }
    }
    return img_copy;
}