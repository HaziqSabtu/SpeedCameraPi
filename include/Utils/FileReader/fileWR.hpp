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

#include "Model/SessionData.hpp"
#include <Utils/CommonUtils.hpp>
#include <chrono>
#include <fstream>
#include <iostream>
#include <opencv2/core.hpp>
#include <string> // Include the necessary header for strings

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
    static CDVector ReadFileOld(std::string path);
};

struct FileMetaData {
    int vectorSize;
    int imgWidth;
    int imgHeight;

    bool isCalibrated;
};
class FileWR2 {
  public:
    FileWR2();
    ~FileWR2();
    //CDVector ReadFile(std::string path);
    void WriteFile(DataPtr data, std::string filename = "");
    DataPtr ReadFile(std::string filename);

  private:
    const std::string FILE_IDENTIFIER = "SPEEDCAMERAPI";
    const std::string DATA_DIVIDER = "DIVDIVDIV";
    const std::string FILE_EXTENSION = ".scpdata";

  private:
};

#endif