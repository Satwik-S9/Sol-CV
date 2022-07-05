#pragma once

#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui.hpp>

cv::Mat_<cv::Vec3b> quantize(cv::Mat_<cv::Vec3b>, uint8_t);