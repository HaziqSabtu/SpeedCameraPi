#ifndef FILE_AVI_HPP
#define FILE_AVI_HPP

#include <chrono>
#include <fstream>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

struct ImgData {
    cv::Mat image;
    std::chrono::high_resolution_clock::time_point time;
};

class FILEAVI {
  private:
    /* data */
  public:
    FILEAVI(/* args */);
    ~FILEAVI();
    static void ReadFile(std::string path, std::vector<ImgData> &imgData);
    // static int WriteFile(std::string path, std::vector<ImgData> &imgData);
    static double
    getTimeDifference(std::chrono::high_resolution_clock::time_point time1,
                      std::chrono::high_resolution_clock::time_point time2);
};

#endif