/**
 * @file ImageUtils.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Utils Class
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <Utils/CommonUtils.hpp>

namespace Utils {
/**
 * @brief Calculate the difference between two time points
 *
 * @param time1 time point 1
 * @param time2 time point 2
 * @return double time difference in milliseconds
 */
double TimeDiff(std::chrono::high_resolution_clock::time_point time1,
                std::chrono::high_resolution_clock::time_point time2) {
    return std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1)
               .count() /
           1000.0;
};

/**
 * @brief Get the current date and time in string format
 *
 * @return std::string current date and time in string format
 */
std::string dateToString() {
    std::time_t t = std::time(0); // get time now
    std::tm *now = std::localtime(&t);
    std::string date =
        std::to_string(now->tm_year + 1900) + std::to_string(now->tm_mon + 1) +
        std::to_string(now->tm_mday) + "_" + std::to_string(now->tm_hour) +
        std::to_string(now->tm_min) + std::to_string(now->tm_sec);
    return date;
}

/**
 * @brief Get File Extension from path
 *
 * @param path path to file
 * @return FileExtension file extension
 */
FileExtension GetFileExtension(std::string &path) {
    std::string ext = path.substr(path.find_last_of(".") + 1);
    if (ext == "bin") {
        return BIN;
    } else if (ext == "h264") {
        return H264;
    } else {
        return UNSUPPORTED;
    }
}

/**
 * @brief Rotate image
 *
 * @param imgData image data
 * @param angle angle to rotate in degrees
 */
void RotateImage(std::vector<cv::Mat> &imgData, int angle) {
    for (int i = 0; i < imgData.size(); i++) {
        cv::Mat img = imgData[i];
        cv::Mat rotatedImg;
        cv::Point2f center(img.cols / 2.0, img.rows / 2.0);
        cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
        cv::warpAffine(img, rotatedImg, rot, img.size());
        imgData[i] = rotatedImg;
    }
}

/**
 * @brief Calculate trimmed mean
 *
 * @param data data to be trimmed
 * @param percentage percentage to be trimmed
 * @return double trimmed mean
 */
double TrimmedMean(const std::vector<double> &data, double percentage) {
    int n = data.size();
    int trim = (int)(percentage / 100.0 * n);

    std::vector<double> sortedData;
    sortedData.assign(data.begin(), data.end());
    std::sort(sortedData.begin(), sortedData.end(), std::less<double>());

    double sum = 0;
    for (int i = trim; i < n - trim; i++) {
        sum += sortedData[i];
    }
    return sum / (n - 2 * trim);
}

cv::Point getRelativePoint(const cv::Mat &src, const cv::Mat &target,
                           const cv::Point &point) {
    // Calculate the scale factors
    double scaleX = static_cast<double>(target.cols) / src.cols;
    double scaleY = static_cast<double>(target.rows) / src.rows;

    // Scale the point coordinates
    int relativeX = static_cast<int>(point.x * scaleX);
    int relativeY = static_cast<int>(point.y * scaleY);

    // Return the relative point
    return cv::Point(relativeX, relativeY);
}

cv::Rect scaleRect(const cv::Rect &rect, cv::Size src, cv::Size dst) {
    double scaleX = static_cast<double>(dst.width) / src.width;
    double scaleY = static_cast<double>(dst.height) / src.height;

    int relativeX = static_cast<int>(rect.x * scaleX);
    int relativeY = static_cast<int>(rect.y * scaleY);
    int relativeWidth = static_cast<int>(rect.width * scaleX);
    int relativeHeight = static_cast<int>(rect.height * scaleY);

    return cv::Rect(relativeX, relativeY, relativeWidth, relativeHeight);
}

int generateRandomID() {
    int id = rand() % 90000 + 10000;
    return id;
}

bool isCvMatSame(const cv::Mat &img1, const cv::Mat &img2) {
    if (img1.size() != img2.size()) {
        return false;
    }
    cv::Mat diff;
    cv::absdiff(img1, img2, diff);
    cv::Mat mask = cv::Mat::zeros(diff.rows, diff.cols, CV_8UC1);
    cv::Mat diff_gray;
    cv::cvtColor(diff, diff_gray, cv::COLOR_BGR2GRAY);
    cv::threshold(diff_gray, mask, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    int nz = cv::countNonZero(mask);
    if (nz == 0) {
        return true;
    }
    return false;
}

bool isCvMatSameRandom(const cv::Mat &img1, const cv::Mat &img2, int points) {
    if (img1.size() != img2.size()) {
        return false;
    }

    int width = img1.cols;
    int height = img1.rows;

    std::vector<cv::Point> randomPoints;

    for (int i = 0; i < points; i++) {
        int x = rand() % width;
        int y = rand() % height;
        randomPoints.push_back(cv::Point(x, y));
    }

    for (int i = 0; i < randomPoints.size(); i++) {
        cv::Point point = randomPoints[i];
        cv::Vec3b pixel1 = img1.at<cv::Vec3b>(point.y, point.x);
        cv::Vec3b pixel2 = img2.at<cv::Vec3b>(point.y, point.x);
        if (pixel1 != pixel2) {
            return false;
        }
    }

    return true;
}

bool isRangeCalibrated(const std::pair<cv::Scalar, cv::Scalar> &range) {
    return range.first != cv::Scalar(0, 0, 0) &&
           range.second != cv::Scalar(0, 0, 0);
}

} // namespace Utils
