#include "Model/SessionData.hpp"
#include "Utils/Struct/D_Allign.hpp"
#include <Thread/Task/Task_Sift.hpp>

SiftTask::SiftTask(DataPtr data, int id)
    : property(TaskType::TASK_SIFT), data(data), id(id) {}

void SiftTask::Execute() {
    if (id == 0) {
        data->allignData.at(id).image = data->captureData.at(id).image.clone();
        data->allignData.at(id).transformMatrix = cv::Mat();
        return;
    }

    CaptureData firstImage = data->captureData.at(0);
    CaptureData targetImage = data->captureData.at(id);

    FeatureDetector featureDetector = FeatureDetector(DetectorType::SIFT);

    featureDetector.allign(firstImage.image, targetImage.image);

    data->allignData.at(id).image = featureDetector.GetAllignedImage().clone();
    data->allignData.at(id).transformMatrix =
        featureDetector.GetHomographyMatrix().clone();
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