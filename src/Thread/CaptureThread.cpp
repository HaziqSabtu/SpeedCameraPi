#include <Thread/CaptureThread.hpp>

CaptureThread::CaptureThread(bool *isCapturing, bool *isProcessing,
                             std::vector<ImageData> *imgData, cv::Mat *frame)
    : wxThread(wxTHREAD_JOINABLE), isCapturing(isCapturing),
      isProcessing(isProcessing), imgData(imgData), frame(frame),
      maxFrameCount(20) {}

CaptureThread::~CaptureThread() { wxLogMessage("deleting thread"); }

void *CaptureThread::Entry() {
    ThreadPool threadPool(2);

    imageCount = 0;

    *isCapturing = true;
    *isProcessing = true;

    while (imageCount < maxFrameCount) {
        imgData->push_back(ImageData(frame->clone()));

        // first image does not need to be processed
        if (imageCount > 0) {
            threadPool.AddTask(new SiftTask(imgData, imageCount));
        }

        imageCount++;
        wxThread::Sleep(33);
    }

    *isCapturing = false;

    while (threadPool.HasTasks()) {
        wxThread::Sleep(33);
    }

    *isProcessing = false;
    return NULL;
};