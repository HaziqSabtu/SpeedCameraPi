#include <Thread/SIFTTask.hpp>

SiftTask::SiftTask(std::vector<ImageData> *imgData, int id)
    : imgData(imgData), id(id) {}

void SiftTask::Execute() {
    ImageData firstImage = (*imgData)[0];
    ImageData targetImage = (*imgData)[id];
    FeatureDetector featureDetector = FeatureDetector("SIFT", false, false);
    featureDetector.run(firstImage.image, targetImage.image);
    imgData->at(id).image = featureDetector.GetTransform().clone();
}