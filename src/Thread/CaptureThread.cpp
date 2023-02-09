#include <Thread/CaptureThread.hpp>

// CaptureThread::CaptureThread(Panel2 *p)
//     : wxThread(wxTHREAD_JOINABLE), m_parent(p) {
//     wxLogMessage("creating new thread");
// }
CaptureThread::CaptureThread() : wxThread(wxTHREAD_JOINABLE) {
    wxLogMessage("creating new thread");
}
CaptureThread::~CaptureThread() { wxLogMessage("deleting thread"); }

void *CaptureThread::Entry() {
    cv::Mat frame;
    time_t start = time(0);
    time_t current;

    wxLogMessage("running on thread");

    while ((current = time(0)) - start < 2) {
        wxLogMessage("in while loop");
        // if (TestDestroy()) {
        //     wxLogMessage("break");
        //     break;
        // }
        // wxLogMessage("fetching camera");
        // frame = m_parent->m_frame;
        // wxLogMessage("lock");
        // wxCriticalSectionLocker lock(m_parent->m_criticalSection);
        // wxLogMessage("pushing");
        // m_parent->m_capturedFrames.push_back(
        //     std::make_pair(frame.clone(), current));
        // wxLogMessage("done loop");
        // wxThread::Sleep(100);
    }
    return NULL;
};