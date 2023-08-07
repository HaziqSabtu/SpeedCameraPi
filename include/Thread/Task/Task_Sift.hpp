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

#include "Model/SessionData.hpp"
#include <Algorithm/image_allign/FeatureDetector.hpp>
#include <Thread/Task/Task.hpp>
#include <Utils/DataStruct.hpp>
#include <memory>

class SiftTask : public Task {
  public:
    SiftTask(DataPtr data, int id);
    void Execute() override;
    TaskProperty GetProperty() const override;
    std::string GetName() const override;

  private:
    const TaskProperty property;
    int id;
    DataPtr data;
};

#endif