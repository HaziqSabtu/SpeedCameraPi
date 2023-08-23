#include "Model/SessionData.hpp"
#include <Thread/Task/Task_Sift.hpp>

SiftTask::SiftTask(DataPtr data, int id)
    : property(TaskType::TASK_SIFT), data(data), id(id) {}

void SiftTask::Execute() {
    // if (id == 0) {
    //     auto captureData = data->getCaptureData();
    //     auto firstFrame = captureData.at(0).image.clone();

    //     //empty homography matrix
    //     cv::Mat emptyhomo = cv::Mat::eye(3, 3, CV_64F);

    //     cv::Mat empty = cv::Mat(firstFrame.size(), CV_8UC1, cv::Scalar(0));

    //     AllignData aData(firstFrame, emptyhomo);
    //     data->setAllignDataAt(0, aData);
    //     return;
    // }
    if (id == 0) {
        auto captureData = data->getCaptureData();
        CaptureData firstImage = captureData.at(0);
        CaptureData targetImage = captureData.at(0);

        FeatureDetector featureDetector = FeatureDetector(DetectorType::SIFT);

        featureDetector.allign(firstImage.image, targetImage.image);

        auto allignImage = featureDetector.GetAllignedImage().clone();
        auto homographyMatrix = featureDetector.GetHomographyMatrix().clone();

        AllignData aData(allignImage, homographyMatrix);
        data->setAllignDataAt(id, aData);
        return;
    }

    auto captureData = data->getCaptureData();
    CaptureData firstImage = captureData.at(0);
    CaptureData targetImage = captureData.at(id);

    FeatureDetector featureDetector = FeatureDetector(DetectorType::SIFT);

    featureDetector.allign(firstImage.image, targetImage.image);

    auto allignImage = featureDetector.GetAllignedImage().clone();
    auto homographyMatrix = featureDetector.GetHomographyMatrix().clone();

    AllignData aData(allignImage, homographyMatrix);
    data->setAllignDataAt(id, aData);
}

/**
 * @brief Get the Type object
 *
 * @return TaskType
 */
TaskProperty SiftTask::GetProperty() const { return property; }

/**
 * @brief Get the Name object
 *
 * @return std::string
 */
std::string SiftTask::GetName() const { return "SiftTask"; }