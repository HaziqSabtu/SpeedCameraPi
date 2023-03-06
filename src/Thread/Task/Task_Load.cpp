#include <Thread/Task/Task_Load.hpp>

LoadTask::LoadTask(std::vector<ImageData> *imgData, std::string path,
                   const int maxCapture)
    : type(TaskType::TASK_LOAD), imgData(imgData), path(path),
      maxCapture(maxCapture) {}

void LoadTask::Execute() { FILEH264::ReadFile(path, imgData); }

TaskType LoadTask::GetType() const { return type; }