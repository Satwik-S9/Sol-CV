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
    //* PREPARE IMG-DATA
    cv::String path = ROOT + "images/sample1.jpg";

    //* PREPARE OUTPUT FILE
    std::string outpath = (std::string)OUT + "output.txt";
    FILE* outfile = fopen(const_cast<char*>(outpath.c_str()), "a");
    std::string sep = getSeparator(69);
    fprintf(outfile, "%s", sep.c_str());
    
    //* LOAD IMG
    cv::Mat_<cv::Vec3b> img = cv::imread(path);
    if (img.empty()) {
        std::cout << "Could not open or find the image" << std::endl;
        std::cin.get(); //wait for any key press 
        return -1;
    }
    
    // fprintf(outfile, "  ->  IMG-DIM: {%d, %d}\n", img.rows, img.cols);

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
    //-- HELPERS --//
    // cv::Mat m1 = cv::Mat::eye(3, 3, CV_32SC1);
    // cv::Mat m2 = cv::Mat::ones(3, 1, CV_32SC1);
    // cv::Mat r = cv::Mat::zeros(3, 1, CV_32SC1);
    // m1.at<int>(0, 2) = 3;
    // m1.at<int>(1, 2) = 3;
    // m2.at<int>(0, 0) = 4;
    // m2.at<int>(1, 0) = 5;
    // print2DMat(m1, "\t");

    // SOME INITIAL TESTING
    // cv::Vec3i t11 = m1.at<cv::Vec3i>(0);
    // cv::Mat t1 = cv::Mat(t11);
    // r.at<int>(0, 0) = t1.dot(m2); 

    // cv::Vec3i t22 = m1.at<cv::Vec3i>(1);
    // cv::Mat t2 = cv::Mat(t22);
    // r.at<int>(1, 0) = t2.dot(m2); 

    // cv::Vec3i t33 = m1.at<cv::Vec3i>(2);
    // cv::Mat t3 = cv::Mat(t33);
    // r.at<int>(2, 0) = t3.dot(m2); 
    // print2DMat(r);

    //-- TRANSFORMATIONS --//
    std::vector<double> params = {5.0, 5.0, 30.0, 1.0, 1.0, 1.0};
    std::string op = "trs";
    cv::Mat T = getTransformMatrix(params, op);
    print2DMat(T, outfile, "Transformation Matrix:\n\t");

    cv::Mat res = affineTransform(img, T);
    cv::Mat res2 = rotate(img, 30, true);
    cv::Mat sres = shear(img, 30, 1, 2);

    //* OUTLINE
    cv::Mat bord = shiftDiff(img, 2, 2);

    //* SHOW AND SAVE
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
    cv::imshow("rotated", res2);
    cv::imshow("sheared", sres);
    cv::imshow("outline", bord);
    
    cv::waitKey(0);
    cv::destroyAllWindows();

    // cv::String qimg_path = OUT + "qimg-2-8.jpg";
    // cv::String skimg_path = OUT + "skImg-2-8.jpg";
    // cv::String bpath = OUT + "bord-1.jpg";
    // cv::String tpath = OUT + "transf-1.jpg";
    // cv::imwrite(qimg_path, qimg);
    // cv::imwrite(skimg_path, skImg);
    // cv::imwrite(tpath, res);
    // cv::imwrite(bpath, bord);

    // print2DMat(r, outfile, "\t");
    fclose(outfile);

    return 0;
}