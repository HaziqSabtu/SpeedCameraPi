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
#include <Utils/FileReader/fileWR.hpp>
#include <Utils/ImageUtils.hpp>
#include <memory>
#include <wx/string.h>

/**
 * @brief Task Implementation for Loading File to ImageData
 *
 */
class LoadTask : public Task {
  public:
    LoadTask(std::shared_ptr<std::vector<ImageData>> imgData,
             std::string path);
    void Execute() override;
    TaskProperty GetProperty() const override;
    std::string GetName() const override;

  private:
    const TaskProperty property;
    std::string path;
    std::shared_ptr<std::vector<ImageData>> imgData;
};

#endif