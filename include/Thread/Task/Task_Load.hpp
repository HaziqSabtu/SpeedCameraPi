#ifndef LOAD_TASK_HPP
#define LOAD_TASK_HPP

#include <Thread/Task/Task.hpp>
#include <Utils/DataStruct.hpp>
#include <Utils/FileReader/fileH264.hpp>
#include <wx/string.h>

class LoadTask : public Task {
  public:
    LoadTask(std::vector<ImageData> *imgData, wxString path,
             const int maxCapture);
    void Execute() override;
    TaskType GetType() const override;

  private:
    const TaskType type;
    wxString path;
    const int maxCapture;
    std::vector<ImageData> *imgData;
};

#endif