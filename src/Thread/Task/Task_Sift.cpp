/**
 * @file Task_Sift.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Task Implementation for Sift Feature Detection
 * @version 1.0.0
 * @date 2023-03-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <Thread/Task/Task_Sift.hpp>

/**
 * @brief Construct a new Sift Task:: Sift Task object
 *
 * @param imgData pointer to vector of ImageData
 * @param id index of target image in vector
 */
SiftTask::SiftTask(std::vector<ImageData> *imgData, int id)
    : property(TaskType::TASK_SIFT), imgData(imgData), id(id) {}

/**
 * @brief Execute Sift Task
 * @details This method will be called automatically by the thread worker
 * <ul>
 * <li> 1. Create FeatureDetector object
 * <li> 2. Set DetectorType to SIFT
 * <li> 3. Run FeatureDetector::allign()
 * <li> 4. Set the image in vector to the alligned image
 * </ul>
 *
 */
void SiftTask::Execute() {
    ImageData firstImage = (*imgData)[0];
    ImageData targetImage = (*imgData)[id];
    FeatureDetector featureDetector = FeatureDetector(DetectorType::SIFT);
    featureDetector.allign(firstImage.image, targetImage.image);
    imgData->at(id).image = featureDetector.GetAllignedImage().clone();
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