#ifndef OBJECT_DETECTION_THREAD
#define OBJECT_DETECTION_THREAD

#include <Algorithm/object_tracker/OpticalFlowTracker.hpp>
#include <wx/thread.h>
#include <wx/wx.h>

class ObjectDetectionThread : public wxThread {
  public:
    ObjectDetectionThread(ObjectDetection *objDetection,
                          std::vector<ImageData> *imgData, bool *isRunning);
    virtual ~ObjectDetectionThread();

  private:
    virtual void *Entry();

    ObjectDetection *objDetection;
    std::vector<ImageData> *imgData;
    bool *isRunning;
};
#endif