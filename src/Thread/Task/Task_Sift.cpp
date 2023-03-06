#include <Thread/Task/Task_Sift.hpp>

SiftTask::SiftTask(std::vector<ImageData> *imgData, int id)
    : type(TaskType::TASK_SIFT), imgData(imgData), id(id) {}

void SiftTask::Execute() {
    ImageData firstImage = (*imgData)[0];
    ImageData targetImage = (*imgData)[id];
    FeatureDetector featureDetector = FeatureDetector(DetectorType::SIFT);
    featureDetector.allign(firstImage.image, targetImage.image);
    imgData->at(id).image = featureDetector.GetAllignedImage().clone();
}

TaskType SiftTask::GetType() const { return type; }