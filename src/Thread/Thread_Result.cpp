#include <Thread/Thread_Result.hpp>

ResultThread::ResultThread(wxEvtHandler *parent,
                           std::vector<ImageData> *imgData)
    : wxThread(wxTHREAD_JOINABLE), parent(parent), imgData(imgData) {}

ResultThread::~ResultThread() {}

wxThread::ExitCode ResultThread::Entry() {
    try {
        for (int i = 1; i < imgData->size(); i++) {
            UpdateImageEvent event(c_UPDATE_IMAGE_EVENT, UPDATE_IMAGE);
            event.SetImageData(imgData->at(i));
            wxPostEvent(parent, event);
            if (TestDestroy()) {
                break;
            }
            wxMilliSleep(500);
        }
    } catch (const std::exception &e) {
        std::cout << "ResultThread::Entry() - Error: \n"
                  << e.what() << std::endl;
    }
    return 0;
}