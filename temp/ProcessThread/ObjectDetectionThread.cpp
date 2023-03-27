#include <Thread/ObjectDetectionThread.hpp>

ObjectDetectionThread::ObjectDetectionThread(ObjectDetection *objDetection,
                                             std::vector<ImageData> *imgData,
                                             bool *isRunning)
    : wxThread(wxTHREAD_JOINABLE), objDetection(objDetection), imgData(imgData),
      isRunning(isRunning) {}

ObjectDetectionThread::~ObjectDetectionThread() {}

void *ObjectDetectionThread::Entry() {
    *isRunning = true;
    objDetection->runDetection(*imgData);
    *isRunning = false;
    return NULL;
}