// ImageThread.cpp
#include <Event/Temp.hpp>

ImageThread::ImageThread(wxEvtHandler *parent) : wxThread(wxTHREAD_JOINABLE) {
    this->m_parent = parent;
}

ImageThread::~ImageThread() {}

wxThread::ExitCode ImageThread::Entry() {
    // cv::VideoCapture cap(0);
    // if (!cap.isOpened()) {
    //     wxPrintf("Failed to open camera\n");
    //     return 0;
    // }

    while (!TestDestroy()) {
        // cv::Mat frame;
        // cap >> frame;
        // if (frame.empty()) {
        //     wxPrintf("Failed to capture frame\n");
        //     continue;
        // }
        // std::cout << "test0" << std::endl;
        std::string tt = "test1212";
        // Trigger the custom event to update the image
        SetImageEvent event(SET_IMAGE_EVENT_TYPE);
        event.SetImageData(tt);
        wxPostEvent(m_parent, event);
        // use wxSleep
        wxMilliSleep(50);
    }
    return 0;
}