#include <Thread/DemoThread.hpp>

DemoThread::DemoThread(bool *isCapturing, bool *isProcessing,
                       bool *isThreadRunning, std::vector<ImageData> *imgData)
    : wxThread(wxTHREAD_JOINABLE), isCapturing(isCapturing),
      isThreadRunning(isThreadRunning), isProcessing(isProcessing),
      imgData(imgData) {}

DemoThread::~DemoThread() { wxLogMessage("deleting thread"); }

void *DemoThread::Entry() {
    ThreadPool threadPool(2);

    imageCount = 0;

    *isCapturing = true;
    *isProcessing = true;

    while (imageCount < imgData->size()) {
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
    *isThreadRunning = false;
    return NULL;
};