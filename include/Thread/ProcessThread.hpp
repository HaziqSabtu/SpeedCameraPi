#ifndef PROCESS_THREAD_HPP
#define PROCESS_THREAD_HPP

#include <Algorithm/image_stabilizer/FeatureDetector.hpp>
#include <Utils/DataStruct.hpp>
#include <chrono>
#include <opencv2/core.hpp>
#include <wx/thread.h>
#include <wx/wx.h>

class ProcessThread : public wxThread {
  public:
    ProcessThread(std::vector<ImageData> *imgData, int id);
    virtual ~ProcessThread();

  private:
    virtual void *Entry();
    FeatureDetector featureDetector;
    ImageData firstImage;
    ImageData targetImage;
    std::vector<ImageData> *imgData;
    int id;
};

#endif