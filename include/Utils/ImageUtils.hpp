#ifndef IMAGE_UTILS_HPP
#define IMAGE_UTILS_HPP

#include <Utils/DataStruct.hpp>
#include <opencv2/opencv.hpp>
#include <wx/log.h>
#include <wx/wx.h>

class ImageUtils {
  public:
    static void RotateImage(std::vector<ImageData> &imgData, int angle);
    static double TrimmedMean(const std::vector<double> &data,
                              double percentage);
};

#endif