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