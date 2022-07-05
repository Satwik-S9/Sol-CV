#include <iostream>
#include <math.h>
#include "dip.h"

cv::Mat_<cv::Vec3b> quantize(cv::Mat_<cv::Vec3b> img, uint8_t b) {
    if (b > 8) {
        printf("Can Quantize to 8 levels only !!");
        return img;
    }
    
    uint8_t level = pow(2, b);
    cv::Mat_<cv::Vec3b> img_copy; 
    img.copyTo(img_copy);

    // QUANTIZATION -- LEVEL : 2
    if (level == 2) {
        for (int i=0; i < img_copy.rows; i++) {
            for (int j=0; j < img_copy.cols; j++) {
                for (int c = 0; c < img_copy.channels(); c++) {
                    if (img_copy.at<cv::Vec3b>(i, j)[c] < 128) 
                        img_copy.at<cv::Vec3b>(i, j)[c] = 0;
                    else img_copy.at<cv::Vec3b>(i, j)[c] = 255;
                }
            }
        }
        return img_copy; 
    }
    
    // QUANTIZATION -- LEVEL : > 2 
    else if (level > 2 && 256 % level == 0) {
        for (int i = 0; i < img_copy.rows; i++) {
            for (int j = 0; j < img_copy.cols; j++) {
                for (int c = 0; c < img_copy.channels(); c++) {
                    for (int m = 0; m < level; m++) {
                        unsigned int bar1 = m * (256 / level) < 255 ?
                                            m * (256 / level) : 255; 
                        unsigned int bar2 = (m+1) * (256 / level) < 255 ?
                                            (m+1) * (256 / level) : 255; 
                        // if (i % 100 == 0 && j % 100 == 0)
                        //     std::cout << bar1 << " " << bar2 << std::endl;

                        if (img_copy.at<cv::Vec3b>(i, j)[c] >= bar1 
                            && img_copy.at<cv::Vec3b>(i, j)[c] < bar2) 
                        {
                            img_copy.at<cv::Vec3b>(i, j)[c] = bar1;
                        } 
                    }
                }
            }
        }
        return img_copy;
    }

    printf("Quantization not implemented for level: %d", level);
    return img_copy;
}


/*
    else if (level == 8) {
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

    * FILTER - 1
    else if (level == 4) {
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
*/