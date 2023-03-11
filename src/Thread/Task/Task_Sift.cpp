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
 *
 */
void SiftTask::Execute() {
    // std::cout << "Executing SiftTask" << std::endl;
    ImageData firstImage = (*imgData)[0];
    // std::cout << "First Image: " << firstImage.image.size() << std::endl;
    ImageData targetImage = (*imgData)[id];
    // std::cout << "Target Image: " << targetImage.image.size() << std::endl;
    FeatureDetector featureDetector = FeatureDetector(DetectorType::SIFT);
    // std::cout << "Feature Detector Created" << std::endl;
    featureDetector.allign(firstImage.image, targetImage.image);
    // std::cout << "Alligned" << std::endl;
    imgData->at(id).image = featureDetector.GetAllignedImage().clone();
    // std::cout << "Image Set" << std::endl;
    // imgData->at(id).keypoints = featureDetector.GetKeypoints();
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