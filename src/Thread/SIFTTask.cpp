#include <Thread/SIFTTask.hpp>

SiftTask::SiftTask(std::vector<ImageData> *imgData, int id)
    : imgData(imgData), id(id) {}

void SiftTask::Execute() {
    ImageData firstImage = (*imgData)[0];
    ImageData targetImage = (*imgData)[id];
    FeatureDetector featureDetector = FeatureDetector(DetectorType::SIFT);
    featureDetector.allign(firstImage.image, targetImage.image);
    imgData->at(id).image = featureDetector.GetAllignedImage().clone();
}