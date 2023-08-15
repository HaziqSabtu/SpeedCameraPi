/**
 * @file Task_HoughLine.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Task Implementation for Hough Line Detection
 * @version 1.0.0
 * @date 2023-03-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef HOUGH_TASK_HPP
#define HOUGH_TASK_HPP

#include <Thread/Task/Task.hpp>
#include <Utils/Config/AppConfig.hpp>

/**
 * @brief Task Implementation for Hough Line Detection
 *
 */
class HoughTask : public Task {
  public:
    HoughTask(ImageData &imgData, Detection::HoughData *houghData,
              CannyConfig cannyConfig, HoughConfig houghConfig);
    void Execute() override;
    TaskProperty GetProperty() const override;
    std::string GetName() const override;

  private:
    const TaskProperty property;
    ImageData &imgData;
    Detection::HoughData *houghData;
    CannyConfig cannyConfig;
    HoughConfig houghConfig;
};

#endif