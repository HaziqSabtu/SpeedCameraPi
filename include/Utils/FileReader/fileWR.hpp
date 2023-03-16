#ifndef FILEWR_HPP
#define FILEWR_HPP

#include <Utils/DataStruct.hpp>
#include <Utils/ImageUtils.hpp>
#include <chrono>
#include <fstream>
#include <iostream>
#include <opencv2/core.hpp>

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