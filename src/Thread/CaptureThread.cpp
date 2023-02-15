#include <Thread/CaptureThread.hpp>

CaptureThread::CaptureThread(bool *isCapturing, std::vector<ImageData> *imgData,
                             cv::Mat *frame)
    : wxThread(wxTHREAD_JOINABLE), isCapturing(isCapturing), imgData(imgData),
      frame(frame) {}

CaptureThread::~CaptureThread() { wxLogMessage("deleting thread"); }

void *CaptureThread::Entry() {
    std::chrono::high_resolution_clock::time_point start =
        std::chrono::high_resolution_clock::now();

    ThreadPool threadPool(2);
    int MAXCOUNT = 20;
    int currentImage = 0;

    cv::Mat firstImage;
    cv::Mat cImg;

    while (imgData->size() < MAXCOUNT) {
        if (TestDestroy()) {
            wxLogMessage("break");
            break;
        }
        cImg = frame->clone();
        imgData->push_back(ImageData(cImg));
        if (currentImage != 0) {
            threadPool.AddTask(new SiftTask(imgData, currentImage));
        } else {
            firstImage = cImg;
        }
        currentImage++;
        wxThread::Sleep(33);
    }
    return NULL;
};