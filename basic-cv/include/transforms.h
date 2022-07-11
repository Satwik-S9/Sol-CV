#include <opencv4/opencv2/core.hpp>

cv::Mat affineTransform(cv::Mat img, cv::Mat T);
cv::Mat getTransformMatrix(double paramX, double paramY, char operation);
cv::Mat getTransformMatrix(std::vector<double> &params, std::string opStr);
cv::Mat getTransformMatrix2(std::vector<double> &params, std::string opStr);

cv::Mat fillTransformMatrix(cv::Mat &T, double paramX, double paramY, char operation);

cv::Mat rotate(cv::Mat img, double theta, bool deg, bool aliasing);
cv::Mat rotate(cv::Mat img, double theta, bool deg);
std::pair<int, int> shearCoord(double theta, int x, int y);
cv::Mat shear(cv::Mat img, double theta, bool deg, int axis);
void scale(cv::Mat img, double tx, double ty);
cv::Mat reflect(cv::Mat img, double theta, double x0, double y0, bool deg);
cv::Mat reflect(cv::Mat img, int axis);


cv::Mat shiftDiff(cv::Mat img, int dist, int axis);