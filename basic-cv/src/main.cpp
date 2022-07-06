#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <time.h>
#include <opencv4/opencv2/core.hpp>
#include "../include/dip.h"
#include "../include/utils.h"
#include "../include/filters.h"
#include "../include/imgops.h"
#include "../include/transforms.h"

const cv::String ROOT = "/home/satwik/dev/machine-learning/computer-vision/basic-cv/";
const cv::String OUT = ROOT + "output/";

int main(int argc, char** argv) {    
    // PREPARE IMG-DATA
    cv::String path = ROOT + "images/sample1.jpg";

    // PREPARE OUTPUT FILE
    std::string outpath = (std::string)OUT + "output.txt";
    FILE* outfile = fopen(const_cast<char*>(outpath.c_str()), "a");
    // std::string sep = getSeparator(69);
    // fprintf(outfile, "%s", sep.c_str());
    
    // LOAD IMG
    cv::Mat_<cv::Vec3b> img = cv::imread(path);
    if (img.empty()) {
        std::cout << "Could not open or find the image" << std::endl;
        std::cin.get(); //wait for any key press 
        return -1;
    }
    
    fprintf(outfile, "  ->  IMG-DIM: {%d, %d}\n", img.rows, img.cols);
    // cv::Mat bord = shiftDiff(img, 2, 0);

    //* QUANTIZE
    clock_t start = clock();
    int level = 3;
    cv::Mat_<cv::Vec3b> qimg = quantize(img, level);
    clock_t end = clock();
    float time_spent = (end - start) / CLOCKS_PER_SEC;

    if (qimg.empty()) {
        std::cout << "Could not open or find the image" << std::endl;
        std::cin.get(); //wait for any key press
        return -1;
    }

    // fprintf(outfile, "  ->  CPP - Time Taken to Quantize Image to level %d: %.6fs\n",
    //          level, time_spent);

    //* APPLY SKETCH FILTER
    cv::Mat_<cv::Vec3b> skImg = sketchFilter(img);

    //* TRANSFORMS
    // cv::Mat m1 = cv::Mat::eye(3, 3, CV_8UC1);
    // m1.at<uchar>(0, 2) = 1;
    // m1.at<uchar>(1, 2) = 0;
    // print2DMat(m1, outfile, "\t");
    // cv::Mat m2({4, 5, 1});
    // cv::Mat r = imgDot(m1, m2);
    // int ni = r.at<uchar>(0);
    // int nj = r.at<uchar>(1);
    // std:: cout << "\n\n" << ni << "   " << nj << "\n\n";
    cv::Mat T = getTransformMatrix(5, 5, 't');
    print2DMat(T);
    cv::Mat res = affineTransform(img, T);

    // SHOW AND SAVE
    cv::String windowName1 = "Normal";
    cv::String windowName2 = "Quantized";
    cv::String windowName3 = "Sketch";
    cv::namedWindow(windowName1);
    cv::namedWindow(windowName2);
    cv::namedWindow(windowName3);

    cv::imshow(windowName1, img);
    cv::imshow(windowName2, qimg);
    cv::imshow(windowName3, skImg);
    cv::imshow("transform", res);
    
    cv::waitKey(0);
    cv::destroyAllWindows();

    // cv::String qimg_path = OUT + "qimg-2-8.jpg";
    // cv::String skimg_path = OUT + "skImg-2-8.jpg";
    // cv::imwrite(qimg_path, qimg);
    // cv::imwrite(skimg_path, skImg);

    // print2DMat(r, outfile, "\t");
    fclose(outfile);

    return 0;
}