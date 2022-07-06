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
    for (int c = 0; c < img.channels(); c++) {
        for (int i = 0; i < img.rows; i++) {
            for (int j =0; j < img.cols; j++) {
                int pixVal = (int)img.at<cv::Vec3b>(i, j)[c];
                if (i == 0 && j == 0) {
                    fprintf(stream, "⌈ %d, ", pixVal); 
                    continue; 
                } else if (i != 0 && i != img.rows-1 && j == 0) {
                    fprintf(stream, "| %d, ", pixVal); 
                    continue;
                } else if (i != 0 && i != img.rows-1 && j == img.cols-1) {
                    fprintf(stream, "%d |\n", pixVal); 
                    continue;
                } else if ( i == img.rows-1 && j == 0) {
                    fprintf(stream, "⌊ %d, ", pixVal); 
                    continue;
                } else if (i == 0 && j == img.cols-1) {
                    fprintf(stream, "%d ⌉\n", pixVal); 
                    continue;
                } else if (i == img.rows-1 && j == img.cols-1) {
                    fprintf(stream, "%d ⌋,\n", pixVal); 
                    continue;
                }
                else fprintf(stream, "%d, ", pixVal);
            } 
        } 
    } fprintf(stream, "]\n");
}

void printImg(cv::Mat img) {
    printf("[\n");
    for (int c = 0; c < img.channels(); c++) {
        for (int i = 0; i < img.rows; i++) {
            for (int j =0; j < img.cols; j++) {
                int pixVal = (int)img.at<cv::Vec3b>(i, j)[c];
                if (i == 0 && j == 0) {
                    printf("⌈ %d, ", pixVal); 
                    continue; 
                } else if (i != 0 && i != img.rows-1 && j == 0) {
                    printf("| %d, ", pixVal); 
                    continue;
                } else if (i != 0 && i != img.rows-1 && j == img.cols-1) {
                    printf("%d |\n", pixVal); 
                    continue;
                } else if ( i == img.rows-1 && j == 0) {
                    printf("⌊ %d, ", pixVal); 
                    continue;
                } else if (i == 0 && j == img.cols-1) {
                    printf("%d ⌉\n", pixVal); 
                    continue;
                } else if (i == img.rows-1 && j == img.cols-1) {
                    printf("%d ⌋,\n", pixVal); 
                    continue;
                }
                else printf("%d, ", pixVal);
            } 
        } 
    } printf("]\n");
}


void print2DMat(cv::Mat m) {
    /* print a 2D array */
    std::cout << "[";
    for (int i=0; i<m.rows; i++) {
        std::cout << "[";
        for (int j=0; j<m.cols-1; j++)
            std::cout << m.at<int>(i, j) << ", ";

        if (i < m.rows-1) std::cout << m.at<int>(i, m.cols-1) << "], ";
        else std::cout << m.at<int>(i, m.cols-1)<< "]";
    } std::cout << "]\n";
}

void print2DMat(cv::Mat m, const char* preText) {
    /* print a 2D array */
    std::cout << preText << "[";
    for (int i=0; i<m.rows; i++) {
        std::cout << "[";
        for (int j=0; j<m.cols-1; j++)
            std::cout << m.at<int>(i, j) << ", ";

        if (i < m.rows-1) std::cout << m.at<int>(i, m.cols-1) << "], ";
        else std::cout << m.at<int>(i, m.cols-1)<< "]";
    } std::cout << "]\n";
}

void print2DMat(cv::Mat m, FILE* stream) {
    /* print a 2D array */
    fprintf(stream, "[");
    for (int i=0; i<m.rows; i++) {
        fprintf(stream, "[");
        for (int j=0; j<m.cols-1; j++)
            fprintf(stream, "%d, ", m.at<int>(i, j));

        if (i < m.rows-1) fprintf(stream, "%d], ", m.at<int>(i, m.cols-1));
        else fprintf(stream, "%d]", m.at<int>(i, m.cols-1));
    } fprintf(stream, "]\n");
}

void print2DMat(cv::Mat m, FILE* stream, const char* preText) {
    /* print a 2D array */
    fprintf(stream, "%s[", preText);
    for (int i=0; i<m.rows; i++) {
        fprintf(stream, "[");
        for (int j=0; j<m.cols-1; j++)
            fprintf(stream, "%d, ", m.at<int>(i, j));

        if (i < m.rows-1) fprintf(stream, "%d], ", m.at<int>(i, m.cols-1));
        else fprintf(stream, "%d]", m.at<int>(i, m.cols-1));
    } fprintf(stream, "]\n");
}