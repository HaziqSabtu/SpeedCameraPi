#include <Thread/CaptureThread.hpp>

CaptureThread::CaptureThread(bool *isCapturing, std::vector<ImageData> *imgData,
                             cv::Mat *frame)
    : wxThread(wxTHREAD_JOINABLE), isCapturing(isCapturing), imgData(imgData),
      frame(frame) {
    wxLogMessage("creating new thread");
}

CaptureThread::~CaptureThread() { wxLogMessage("deleting thread"); }

void *CaptureThread::Entry() {
    std::chrono::high_resolution_clock::time_point start =
        std::chrono::high_resolution_clock::now();

    wxLogMessage("running on thread");

    int MAXCOUNT = 20;

    while (imgData->size() < MAXCOUNT) {
        wxLogMessage("in while loop");
        if (TestDestroy()) {
            wxLogMessage("break");
            break;
        }
        // wxLogMessage("fetching camera");
        // frame = m_parent->m_frame;
        wxLogMessage("lock");
        // wxCriticalSectionLocker lock(m_parent->m_criticalSection);
        wxLogMessage("pushing");
        imgData->push_back(ImageData(frame->clone()));
        // m_pimgarent->m_capturedFrames.push_back(
        //     std::make_pair(frame.clone(), current));
        // wxLogMessage("done loop");
        wxThread::Sleep(100);
    }
    return NULL;
};