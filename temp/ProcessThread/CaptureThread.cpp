#include <Thread/CaptureThread.hpp>

CaptureThread::CaptureThread(bool *isCapturing, bool *isProcessing,
                             bool *isThreadRunning,
                             std::vector<ImageData> *imgData, cv::Mat *frame)
    : wxThread(wxTHREAD_JOINABLE), isCapturing(isCapturing),
      isProcessing(isProcessing), isThreadRunning(isThreadRunning),
      imgData(imgData), frame(frame) {

    AppConfig *config = new AppConfig();
    CaptureConfig captureConfig = config->GetCaptureConfig();

    maxFrameCount = captureConfig.Max_Frame_Count;
    threadPoolCount = captureConfig.Thread_Pool_Size;
    frameInterval = captureConfig.Frame_Interval;
}

CaptureThread::~CaptureThread() { wxLogMessage("deleting thread"); }

void *CaptureThread::Entry() {
    ThreadPool threadPool(threadPoolCount);

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
        wxThread::Sleep(frameInterval);
    }

    *isCapturing = false;

    while (threadPool.isBusy()) {
        wxThread::Sleep(frameInterval);
    }

    *isProcessing = false;
    *isThreadRunning = false;
    return NULL;
};