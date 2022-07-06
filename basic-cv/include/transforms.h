#include <opencv4/opencv2/core.hpp>

cv::Mat affineTransform(cv::Mat img, cv::Mat T);
cv::Mat getTransformMatrix(int paramX, int paramY, char operation);
cv::Mat getTransformMatrix(std::vector<int> &params, std::string operation);

void translation(cv::Mat img, int tx, int ty);
void rotate(cv::Mat img, int tx, int ty);
void scale(cv::Mat img, int tx, int ty);


cv::Mat shiftBy(cv::Mat img, int dist, int axis);
cv::Mat shiftDiff(cv::Mat img, int dist, int axis);