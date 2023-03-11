#include <Thread/Thread_Hough.hpp>

HoughThread::HoughThread(wxEvtHandler *parent) : wxThread(wxTHREAD_JOINABLE) {
    this->m_parent = parent;
}

HoughThread::~HoughThread() {}

wxThread::ExitCode HoughThread::Entry() {
    std::cout << "HoughThread::Entry()" << std::endl;
    HoughEvent startHoughEvent(c_HOUGH_EVENT, HOUGH_START);
    wxPostEvent(m_parent, startHoughEvent);
    // do hough
    wxMilliSleep(5000);
    HoughEvent endHoughEvent(c_HOUGH_EVENT, HOUGH_END);
    wxPostEvent(m_parent, endHoughEvent);
    std::cout << "HoughThread::Entry(): end" << std::endl;
    return 0;
}