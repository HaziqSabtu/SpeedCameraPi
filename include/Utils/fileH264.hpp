#ifndef FILE_H264_HPP
#define FILE_H264_HPP

#include <Utils/fileAVI.hpp>
#include <chrono>
#include <fstream>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>


// struct ImgData {
//     cv::Mat image;
//     std::chrono::high_resolution_clock::time_point time;
// };

class FILEH264 {
  private:
    /* data */
  public:
    FILEH264(/* args */);
    ~FILEH264();
    static void ReadFile(std::string path, std::vector<ImgData> &imgData);
    // static int WriteFile(std::string path, std::vector<ImgData> &imgData);
    static double
    getTimeDifference(std::chrono::high_resolution_clock::time_point time1,
                      std::chrono::high_resolution_clock::time_point time2);
};

#endif