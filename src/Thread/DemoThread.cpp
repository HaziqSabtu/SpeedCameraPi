#include <Thread/DemoThread.hpp>

DemoThread::DemoThread(bool *isCapturing, bool *isProcessing,
                       bool *isThreadRunning, std::vector<ImageData> *imgData,
                       int maxLoadFrame)
    : wxThread(wxTHREAD_JOINABLE), isCapturing(isCapturing),
      isThreadRunning(isThreadRunning), isProcessing(isProcessing),
      imgData(imgData) {
    if (maxLoadFrame < imgData->size()) {
        imgData->erase(imgData->begin() + maxLoadFrame, imgData->end());
    }
}

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

    while (threadPool.isBusy()) {
        wxThread::Sleep(33);
    }
    *isProcessing = false;
    *isThreadRunning = false;
    return NULL;
};