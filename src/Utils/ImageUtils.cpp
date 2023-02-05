#include <Utils/ImageUtils.hpp>

void ImageUtils::RotateImage(std::vector<ImgData> &imgData, int angle) {
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
