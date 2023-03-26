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

#include <Utils/ImageUtils.hpp>

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
void RotateImage(std::vector<ImageData> &imgData, int angle) {
    std::cout << "Rotating: " << imgData.size() << " images on angle " << angle
              << std::endl;
    for (int i = 0; i < imgData.size(); i++) {
        cv::Mat img = imgData[i].image;
        cv::Mat rotatedImg;
        cv::Point2f center(img.cols / 2.0, img.rows / 2.0);
        cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
        cv::warpAffine(img, rotatedImg, rot, img.size());
        imgData[i].image = rotatedImg;
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
} // namespace Utils
