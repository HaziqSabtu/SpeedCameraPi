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

  private:
    const TaskType type;
    int id;
    std::vector<ImageData> *imgData;
};

#endif