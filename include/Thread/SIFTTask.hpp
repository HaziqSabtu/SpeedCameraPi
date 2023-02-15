#ifndef SIFT_TASK_HPP
#define SIFT_TASK_HPP

#include <Algorithm/image_stabilizer/FeatureDetector.hpp>
#include <Thread/Task.hpp>
#include <Utils/DataStruct.hpp>

class SiftTask : public Task {
  public:
    SiftTask(std::vector<ImageData> *imgData, int id);
    virtual void Execute();

  private:
    int id;
    std::vector<ImageData> *imgData;
};

#endif