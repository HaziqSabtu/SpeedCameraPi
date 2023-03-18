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

#ifndef FILEWR_HPP
#define FILEWR_HPP

#include <Utils/DataStruct.hpp>
#include <Utils/ImageUtils.hpp>
#include <chrono>
#include <fstream>
#include <iostream>
#include <opencv2/core.hpp>

/**
 * @brief Utils Class for reading and writing binary file
 *
 */
class FILEWR {
  private:
    /* data */
  public:
    FILEWR(/* args */);
    ~FILEWR();
    static void ReadFile(std::string path, std::vector<ImageData> *imgData);
    static void WriteFile(std::vector<ImageData> *imgData);
};

#endif