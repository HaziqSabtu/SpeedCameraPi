#include "Thread/Thread_Replay.hpp"
#include "Event/Event_Error.hpp"
#include "Event/Event_LoadImage.hpp"
#include "Event/Event_Replay.hpp"
#include "Thread/Thread_ID.hpp"
#include <Thread/Thread_LoadCapture.hpp>
#include <memory>

ReplayThread::ReplayThread(wxEvtHandler *parent,
                           std::shared_ptr<std::vector<ImageData>> imgData)
    : wxThread(wxTHREAD_JOINABLE), parent(parent), imgData(imgData) {}

ReplayThread::~ReplayThread() {}

wxThread::ExitCode ReplayThread::Entry() {
    try {

        wxCommandEvent startLoadEvent(c_REPLAY_EVENT, REPLAY_START);
        wxPostEvent(parent, startLoadEvent);

        if (imgData == nullptr) {
            throw std::runtime_error("imgData is null");
        }

        for (int i = 0; i < imgData->size(); i++) {

            cv::Mat frame = imgData->at(i).image;
            UpdatePreviewEvent::Submit(parent, frame);

            wxMilliSleep(200);

            if (TestDestroy()) {
                break;
            }
        }

    } catch (const std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }

    wxCommandEvent stopLoadEvent(c_REPLAY_EVENT, REPLAY_END);
    wxPostEvent(parent, stopLoadEvent);
    return 0;
}

ThreadID ReplayThread::getID() const { return id; }
