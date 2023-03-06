#ifndef CAPTURE_TASK_HPP
#define CAPTURE_TASK_HPP

#include <Thread/Task/Task.hpp>
#include <Utils/DataStruct.hpp>
#include <Utils/FileReader/fileH264.hpp>

class LoadTask : public Task {
  public:
    LoadTask(std::vector<ImageData> *imgData, std::string path,
             const int maxCapture);
    void Execute() override;
    TaskType GetType() const override;

  private:
    const TaskType type;
    std::string path;
    const int maxCapture;
    std::vector<ImageData> *imgData;
};

#endif