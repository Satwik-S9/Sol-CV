#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <opencv4/opencv2/core.hpp>


std::string getSeparator(int);
void printImg(cv::Mat, FILE* );
void printImg(cv::Mat);
void print2DMat(cv::Mat m);
void print2DMat(cv::Mat m, const char* preText);
void print2DMat(cv::Mat m, FILE* stream);
void print2DMat(cv::Mat m, FILE* stream, const char* preText);