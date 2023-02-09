#include <Thread/CaptureThread.hpp>

// CaptureThread::CaptureThread(Panel2 *p)
//     : wxThread(wxTHREAD_JOINABLE), m_parent(p) {
//     wxLogMessage("creating new thread");
// }
// CaptureThread::CaptureThread() : wxThread(wxTHREAD_JOINABLE) {
//     wxLogMessage("creating new thread");
// }

CaptureThread::CaptureThread(bool *isCapturing,
                             std::vector<std::pair<cv::Mat, time_t>> *imgData,
                             cv::Mat *frame)
    : wxThread(wxTHREAD_JOINABLE), isCapturing(isCapturing), imgData(imgData),
      frame(frame) {
    wxLogMessage("creating new thread");
}

CaptureThread::~CaptureThread() { wxLogMessage("deleting thread"); }

void *CaptureThread::Entry() {
    // cv::Mat f = *frame.clone();
    time_t start = time(0);
    time_t current;

    wxLogMessage("running on thread");

    while ((current = time(0)) - start < 2) {
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
        imgData->push_back(std::make_pair(frame->clone(), current));
        // m_pimgarent->m_capturedFrames.push_back(
        //     std::make_pair(frame.clone(), current));
        // wxLogMessage("done loop");
        wxThread::Sleep(100);
    }
    return NULL;
};