#include <Thread/Task/Task_Sift.hpp>

/**
 * @brief Construct a new Sift Task:: Sift Task object
 *
 * @param detector shared_ptr to the FeatureDetector
 * @param data shared_ptr to the SessionData
 * @param id the id of the image needed to be alligned
 */
SiftTask::SiftTask(DetectorPtr detector, DataPtr data, int id)
    : data(data), id(id), detector(detector) {
    property = TaskProperty(currentType);
    name = currentName;
}

/**
 * @brief Execute the Sift Task
 *
 */
void SiftTask::Execute() {

    auto captureData = data->getCaptureData();
    CaptureData targetImage = captureData.at(id);

    AllignData allignData;

    // if id == 0, then the first image is the target image
    // do not need to allign this, just clone the image
    if (id == 0) {
        auto firstImage = targetImage.image.clone();
        allignData.image = firstImage.clone();
        allignData.transformMatrix = cv::Mat::eye(3, 3, CV_64F);
    } else {
        detector->Allign(targetImage.image);
        allignData.image = detector->GetAllignedImage().clone();
        allignData.transformMatrix = detector->GetHomographyMatrix().clone();
    }

    // update the allignData
    auto resultData = data->getResultData();
    auto vector = resultData.allignData;
    vector.at(id) = allignData;
    resultData.allignData = vector;
    data->setResultData(resultData);
}