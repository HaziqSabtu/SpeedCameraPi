#include "Thread/Thread_Replay.hpp"
#include "Event/Event_Error.hpp"
#include "Event/Event_LoadImage.hpp"
#include "Event/Event_Replay.hpp"
#include "Thread/Thread_ID.hpp"
#include <Thread/Thread_LoadCapture.hpp>
#include <memory>

ReplayThread::ReplayThread(wxEvtHandler *parent, DataPtr data)
    : wxThread(wxTHREAD_JOINABLE), parent(parent), data(data) {}

ReplayThread::~ReplayThread() {}

wxThread::ExitCode ReplayThread::Entry() {
    try {

        wxCommandEvent startLoadEvent(c_REPLAY_EVENT, REPLAY_START);
        wxPostEvent(parent, startLoadEvent);

        if (data->isCaptureDataEmpty()) {
            throw std::runtime_error("capture data is empty");
        }

        auto captureData = data->getCaptureData();

        const int MAX_FRAME = captureData.size();

        for (int i = 0; i < MAX_FRAME; i++) {

            cv::Mat frame = captureData.at(i).image;
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
