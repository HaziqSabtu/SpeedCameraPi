#ifndef FILEWR_HPP
#define FILEWR_HPP

#include <chrono>
#include <fstream>
#include <iostream>
#include <opencv2/core.hpp>

struct ImgData {
    cv::Mat image;
    std::chrono::high_resolution_clock::time_point time;
};

class FILEWR {
  private:
    /* data */
  public:
    FILEWR(/* args */);
    ~FILEWR();
    static int ReadFile(std::string path, std::vector<ImgData> &imgData);
    static int WriteFile(std::string path, std::vector<ImgData> &imgData);
    static double
    getTimeDifference(std::chrono::high_resolution_clock::time_point time1,
                      std::chrono::high_resolution_clock::time_point time2);
};

#endif