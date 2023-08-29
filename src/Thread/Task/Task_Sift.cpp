#include "Algorithm/image_allign/FeatureDetector.hpp"
#include "Model/SessionData.hpp"
#include <Thread/Task/Task_Sift.hpp>

SiftTask::SiftTask(FeatureDetector &detector, DataPtr data, int id)
    : data(data), id(id), detector(detector) {
    property = TaskProperty(currentType);
    name = currentName;
}

void SiftTask::Execute() {

    auto captureData = data->getCaptureData();
    CaptureData targetImage = captureData.at(id);

    AllignData allignData;

    if (id == 0) {
        auto firstImage = targetImage.image.clone();
        allignData.image = firstImage.clone();
        allignData.transformMatrix = cv::Mat::eye(3, 3, CV_64F);
    } else {
        detector.Allign(targetImage.image);
        allignData.image = detector.GetAllignedImage().clone();
        allignData.transformMatrix = detector.GetHomographyMatrix().clone();
    }

    auto resultData = data->getResultData();
    auto vector = resultData.allignData;
    vector.at(id) = allignData;
    resultData.allignData = vector;
    data->setResultData(resultData);
}