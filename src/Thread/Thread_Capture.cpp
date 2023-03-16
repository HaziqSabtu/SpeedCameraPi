#include <Thread/Thread_Capture.hpp>

CaptureThread::CaptureThread(wxEvtHandler *parent, raspicam::RaspiCam_Cv *cap)
    : wxThread(wxTHREAD_JOINABLE), m_cap(cap) {
    this->m_parent = parent;
}

CaptureThread::~CaptureThread() {}

wxThread::ExitCode CaptureThread::Entry() {
    if (!m_cap->isOpened()) {
        std::cout << "Failed to open camera" << std::endl;
        return 0;
    }

    while (!TestDestroy()) {
        cv::Mat frame;
        m_cap->grab();
        m_cap->retrieve(frame);
        if (frame.empty()) {
            std::cout << "Failed to capture frame" << std::endl;
            continue;
        }
        UpdateImageEvent event(c_UPDATE_IMAGE_EVENT, UPDATE_IMAGE);
        event.SetImageData(ImageData(frame));
        wxPostEvent(m_parent, event);
    }

    UpdateImageEvent event(c_UPDATE_IMAGE_EVENT, CLEAR_IMAGE);
    wxPostEvent(m_parent, event);
    return 0;
}