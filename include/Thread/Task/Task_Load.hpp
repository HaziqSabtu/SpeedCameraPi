/**
 * @file Task_Load.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Task Implementation for Loading H264 to ImageData
 * @version 1.0.0
 * @date 2023-03-06
 *
 * @copyright Copyright (c) 2023
 *
 */
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
    TaskProperty GetProperty() const override;
    std::string GetName() const override;

  private:
    const TaskProperty property;
    wxString path;
    const int maxCapture;
    std::vector<ImageData> *imgData;
};

#endif