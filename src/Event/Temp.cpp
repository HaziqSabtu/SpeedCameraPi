// ImageThread.cpp
#include <Event/Temp.hpp>

ImageThread::ImageThread(wxEvtHandler *parent, cv::VideoCapture *cap)
    : wxThread(wxTHREAD_JOINABLE), m_cap(cap) {
    this->m_parent = parent;
}

ImageThread::~ImageThread() {}

wxThread::ExitCode ImageThread::Entry() {
    if (!m_cap->isOpened()) {
        std::cout << "Failed to open camera" << std::endl;
        return 0;
    }

    while (!TestDestroy()) {
        cv::Mat frame;
        m_cap->read(frame);
        if (frame.empty()) {
            std::cout << "Failed to capture frame" << std::endl;
            continue;
        }
        UpdateImageEvent event(c_UPDATE_IMAGE_EVENT);
        event.SetImageData(frame);
        wxPostEvent(m_parent, event);
        wxMilliSleep(30);
    }
    return 0;
}