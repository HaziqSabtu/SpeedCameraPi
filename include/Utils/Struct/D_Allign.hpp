#pragma once

#include <opencv2/core/mat.hpp>

enum Status { NONE, PROCESSING, DONE };

struct AllignData {
    cv::Mat image;
    cv::Mat homographyMatrix;

    Status status = NONE;

    AllignData() {}

    AllignData(cv::Mat image, cv::Mat homographyMatrix)
        : image(image), homographyMatrix(homographyMatrix) {}
};