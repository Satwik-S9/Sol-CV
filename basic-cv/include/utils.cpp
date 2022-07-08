#include "utils.h"


std::string getSeparator(int length) {
    std::string sep = "";
    for (int i = 0; i < length; i++) 
        sep += '-';
    sep += '\n';
    return sep;
}

void printImg(cv::Mat img, FILE* stream) {
    fprintf(stream, "[\n");
    cv::Mat temp; 
    img.convertTo(temp, CV_64F);

    for (int c = 0; c < img.channels(); c++) {
        for (int i = 0; i < img.rows; i++) {
            for (int j =0; j < img.cols; j++) {
                double pixVal = temp.at<cv::Vec3d>(i, j)[c];
                if (i == 0 && j == 0) {
                    fprintf(stream, "⌈ %.2f, ", pixVal); 
                    continue; 
                } else if (i != 0 && i != img.rows-1 && j == 0) {
                    fprintf(stream, "| %.2f, ", pixVal); 
                    continue;
                } else if (i != 0 && i != img.rows-1 && j == img.cols-1) {
                    fprintf(stream, "%.2f |\n", pixVal); 
                    continue;
                } else if ( i == img.rows-1 && j == 0) {
                    fprintf(stream, "⌊ %.2f, ", pixVal); 
                    continue;
                } else if (i == 0 && j == img.cols-1) {
                    fprintf(stream, "%.2f ⌉\n", pixVal); 
                    continue;
                } else if (i == img.rows-1 && j == img.cols-1) {
                    fprintf(stream, "%.2f ⌋,\n", pixVal); 
                    continue;
                }
                else fprintf(stream, "%.2f, ", pixVal);
            } 
        } 
    } fprintf(stream, "]\n");
}

void printImg(cv::Mat img) {
    printf("[\n");
    cv::Mat temp; 
    img.convertTo(temp, CV_64F);

    for (int c = 0; c < img.channels(); c++) {
        for (int i = 0; i < img.rows; i++) {
            for (int j =0; j < img.cols; j++) {
                double pixVal = temp.at<cv::Vec3d>(i, j)[c];
                if (i == 0 && j == 0) {
                    printf("⌈ %.2f, ", pixVal); 
                    continue; 
                } else if (i != 0 && i != img.rows-1 && j == 0) {
                    printf("| %.2f, ", pixVal); 
                    continue;
                } else if (i != 0 && i != img.rows-1 && j == img.cols-1) {
                    printf("%.2f |\n", pixVal); 
                    continue;
                } else if ( i == img.rows-1 && j == 0) {
                    printf("⌊ %.2f, ", pixVal); 
                    continue;
                } else if (i == 0 && j == img.cols-1) {
                    printf("%.2f ⌉\n", pixVal); 
                    continue;
                } else if (i == img.rows-1 && j == img.cols-1) {
                    printf("%.2f ⌋,\n", pixVal); 
                    continue;
                }
                else printf("%.2f, ", pixVal);
            } 
        } 
    } printf("]\n");
}


void print2DMat(cv::Mat m) {
    /* print a 2D array */
    m.convertTo(m, CV_64F);
    std::cout << "[";
    for (int i=0; i<m.rows; i++) {
        std::cout << "[";
        for (int j=0; j<m.cols-1; j++)
            printf("%.2f, ", m.at<double>(i, j));

        if (i < m.rows-1) printf("%.2f], ", m.at<double>(i, m.cols-1));
        else printf("%.2f]", m.at<double>(i, m.cols-1));
    } std::cout << "]\n";
}

void print2DMat(cv::Mat m, const char* preText) {
    /* print a 2D array */
    m.convertTo(m, CV_64F);
    std::cout << preText << "[";
    for (int i=0; i<m.rows; i++) {
        std::cout << "[";
        for (int j=0; j<m.cols-1; j++)
            printf("%.2f, ", m.at<double>(i, j));

        if (i < m.rows-1) printf("%.2f], ", m.at<double>(i, m.cols-1));
        else printf("%.2f]", m.at<double>(i, m.cols-1));
    } std::cout << "]\n";
}

void print2DMat(cv::Mat m, FILE* stream) {
    /* print a 2D array */
    m.convertTo(m, CV_64F);
    fprintf(stream, "[");
    for (int i=0; i<m.rows; i++) {
        fprintf(stream, "[");
        for (int j=0; j<m.cols-1; j++)
            fprintf(stream, "%.2f, ", m.at<double>(i, j));

        if (i < m.rows-1) fprintf(stream, "%.2f], ", m.at<double>(i, m.cols-1));
        else fprintf(stream, "%.2f]", m.at<double>(i, m.cols-1));
    } fprintf(stream, "]\n");
}

void print2DMat(cv::Mat m, FILE* stream, const char* preText) {
    /* print a 2D array */
    m.convertTo(m, CV_64F);
    fprintf(stream, "%s[", preText);
    for (int i=0; i<m.rows; i++) {
        fprintf(stream, "[");
        for (int j=0; j<m.cols-1; j++)
            fprintf(stream, "%.2f, ", m.at<double>(i, j));

        if (i < m.rows-1) fprintf(stream, "%.2f], ", m.at<double>(i, m.cols-1));
        else fprintf(stream, "%.2f]", m.at<double>(i, m.cols-1));
    } fprintf(stream, "]\n");
}