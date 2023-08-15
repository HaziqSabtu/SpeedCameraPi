/**
 * @file Task_HoughLine.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Task Implementation for Hough Line Detection
 * @version 1.0.0
 * @date 2023-03-07
 *
 * @copyright Copyright (c) 2023
 *
 */

/**
 * @brief Construct a new Hough Task:: Hough Task object
 *
 * @param imgData pointer to vector of ImageData
 * @param id index of target image in vector
 */
HoughTask::HoughTask(ImageData &imgData, Detection::HoughData *houghData,
                     CannyConfig cannyConfig, HoughConfig houghConfig)
    : property(TaskType::TASK_HOUGHLINE), imgData(imgData),
      houghData(houghData), cannyConfig(cannyConfig), houghConfig(houghConfig) {
}

/**
 * @brief Execute Hough Task
 * @details This method will be called automatically by the thread worker
 * <ul>
 * <li> 1. Create LineDetection object
 * <li> 2. Set Canny Parameters
 * <li> 3. Set HoughLinesP Parameters
 * <li> 4. Set Image and run Detection with LineDetection::SetImage()
 * <li> 5. Get HoughData
 * </ul>
 *
 */
void HoughTask::Execute() {
    LineDetection lineDetection;
    lineDetection.SetCannyParameters(
        cannyConfig.threshold1, cannyConfig.threshold2,
        cannyConfig.apertureSize, cannyConfig.L2gradient);
    lineDetection.SetHoughLinesPParameters(
        houghConfig.rho, houghConfig.theta, houghConfig.threshold,
        houghConfig.minLineLength, houghConfig.maxLineGap);
    lineDetection.SetImage(imgData.image);
    *houghData = lineDetection.GetHoughData();
}

/**
 * @brief Get the TaskProperty of the task
 *
 * @return TaskProperty
 */
TaskProperty HoughTask::GetProperty() const { return property; }

/**
 * @brief Get the Name object
 *
 * @return std::string
 */
std::string HoughTask::GetName() const { return "HoughTask"; }