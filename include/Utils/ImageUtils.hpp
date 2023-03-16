#ifndef IMAGE_UTILS_HPP
#define IMAGE_UTILS_HPP

#include <Utils/DataStruct.hpp>
#include <ctime>
#include <opencv2/opencv.hpp>
#include <wx/log.h>
#include <wx/wx.h>

class ImageUtils {
  public:
    static void RotateImage(std::vector<ImageData> &imgData, int angle);
    static double TrimmedMean(const std::vector<double> &data,
                              double percentage);
};

namespace Utils {
enum FileExtension { BIN, H264, UNSUPPORTED };
double TimeDiff(std::chrono::high_resolution_clock::time_point time1,
                std::chrono::high_resolution_clock::time_point time2);
std::string dateToString();
FileExtension GetFileExtension(std::string &path);
} // namespace Utils

#endif