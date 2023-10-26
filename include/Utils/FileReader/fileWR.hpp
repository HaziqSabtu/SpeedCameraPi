/**
 * @file fileWR.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Utils Class for reading and writing binary file
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <Model/SessionData.hpp>
#include <Utils/CommonUtils.hpp>

#include <chrono>
#include <fstream>
#include <iostream>
#include <opencv2/core.hpp>
#include <string>

#pragma once

namespace Utils {

/**
 * @brief Custom Struct for File Meta Data. Used within FileReadWrite class
 *
 */
struct FileMetaData {
    int vectorSize;
    int imgWidth;
    int imgHeight;

    Mode mode;

    bool isCalibrated;

    bool isROI;
};

/**
 * @brief Class for reading and writing binary file
 *
 */
class FileReadWrite {
  public:
    FileReadWrite();
    ~FileReadWrite();
    void WriteFile(DataPtr data, std::string filename = "");
    void ReadFile(DataPtr data, std::string filename);

  private:
    const std::string FILE_IDENTIFIER = "SPEEDCAMERAPI";
    const std::string DATA_DIVIDER = "DIVDIVDIV";
    const std::string FILE_EXTENSION = ".scpdata";

  private:
};

} // namespace Utils