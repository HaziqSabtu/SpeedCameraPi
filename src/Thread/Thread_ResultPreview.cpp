#include "Event/Event_Error.hpp"
#include "Event/Event_UpdatePreview.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/CalibrationData.hpp"
#include "Model/SessionData.hpp"
#include "Thread/ThreadPool.hpp"
#include <Thread/Thread_ResultPreview.hpp>
#include <wx/utils.h>

ResultPreviewThread::ResultPreviewThread(wxEvtHandler *parent, DataPtr data)
    : wxThread(wxTHREAD_JOINABLE), parent(parent), data(data) {}

ResultPreviewThread::~ResultPreviewThread() {}

wxThread::ExitCode ResultPreviewThread::Entry() {
    try {

        if (data->isCaptureDataEmpty()) {
            throw std::runtime_error("Capture Data is empty");
        }

        if (data->isAllignDataEmpty()) {
            throw std::runtime_error("Allign Data is empty");
        }

        auto allignData = data->getAllignData();

        for (auto &frame : allignData) {
            UpdatePreviewEvent::Submit(parent, frame.image);
            wxMilliSleep(300);
        }

    } catch (const std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }

    return 0;
}

ThreadID ResultPreviewThread::getID() const { return threadID; }