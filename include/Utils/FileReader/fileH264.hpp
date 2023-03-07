#ifndef FILE_H264_HPP
#define FILE_H264_HPP

#include <Utils/DataStruct.hpp>
#include <chrono>
#include <fstream>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <wx/string.h>

class FILEH264 {
  private:
    /* data */
  public:
    FILEH264(/* args */);
    ~FILEH264();
    static void ReadFile(std::string path, std::vector<ImageData> &imgData);
    static void ReadFile(std::string path, std::vector<ImageData> *imgData);
    static void ReadFile(wxString path, std::vector<ImageData> &imgData);
    static void ReadFile(wxString path, std::vector<ImageData> *imgData);
    // static int WriteFile(std::string path, std::vector<ImageData> &imgData);
    static double
    getTimeDifference(std::chrono::high_resolution_clock::time_point time1,
                      std::chrono::high_resolution_clock::time_point time2);
};

#endif