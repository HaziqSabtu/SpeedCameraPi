#include <Utils/ImageUtils.hpp>

void ImageUtils::RotateImage(std::vector<ImageData> &imgData, int angle) {
    wxLogMessage("Rotating: %zd images on angle %d", imgData.size(), angle);
    for (int i = 0; i < imgData.size(); i++) {
        cv::Mat img = imgData[i].image;
        cv::Mat rotatedImg;
        cv::Point2f center(img.cols / 2.0, img.rows / 2.0);
        cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
        cv::warpAffine(img, rotatedImg, rot, img.size());
        imgData[i].image = rotatedImg;
        wxLogMessage("Rotated image %d", i);
    }
}

double ImageUtils::TrimmedMean(const std::vector<double> &data,
                               double percentage) {
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

namespace Utils {
double TimeDiff(std::chrono::high_resolution_clock::time_point time1,
                std::chrono::high_resolution_clock::time_point time2) {
    return std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1)
               .count() /
           1000.0;
};

std::string dateToString() {
    std::time_t t = std::time(0); // get time now
    std::tm *now = std::localtime(&t);
    std::string date =
        std::to_string(now->tm_year + 1900) + std::to_string(now->tm_mon + 1) +
        std::to_string(now->tm_mday) + "_" + std::to_string(now->tm_hour) +
        std::to_string(now->tm_min) + std::to_string(now->tm_sec);
    return date;
}

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
} // namespace Utils
