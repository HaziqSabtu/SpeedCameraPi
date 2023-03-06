/**
 * @file Task_Sift.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Task Implementation for Sift Feature Detection
 * @version 1.0.0
 * @date 2023-03-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef SIFT_TASK_HPP
#define SIFT_TASK_HPP

#include <Algorithm/image_allign/FeatureDetector.hpp>
#include <Thread/Task/Task.hpp>
#include <Utils/DataStruct.hpp>

class SiftTask : public Task {
  public:
    SiftTask(std::vector<ImageData> *imgData, int id);
    void Execute() override;
    TaskType GetType() const override;
    std::string GetName() const override;

  private:
    const TaskType type;
    int id;
    std::vector<ImageData> *imgData;
};

#endif