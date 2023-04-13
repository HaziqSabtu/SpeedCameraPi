/**
 * @file fileH264.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Utils Class for reading H264 file and convert it to vector of
 * ImageData
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef FILE_H264_HPP
#define FILE_H264_HPP

#include <Utils/DataStruct.hpp>
#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <wx/string.h>

/**
 * @brief Utils Class for reading H264 file and convert it to vector of
 * ImageData
 *
 */
class FILEH264 {
  private:
    /* data */
  public:
    FILEH264(/* args */);
    ~FILEH264();
    static void ReadFile(std::string path,
                         std::shared_ptr<std::vector<ImageData>> imgData);
};

#endif