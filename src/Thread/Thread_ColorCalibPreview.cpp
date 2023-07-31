
#include "Event/Event_Error.hpp"
#include "Model/ExtraModel.hpp"
#include <Thread/Thread_ColorCalibPreview.hpp>
#include <memory>
#include <opencv2/core/types.hpp>

ColorCalibPreviewThread::ColorCalibPreviewThread(
    wxEvtHandler *parent, std::unique_ptr<CameraBase> &camera,
    CCModelPtr ccExtraModel)
    : wxThread(wxTHREAD_JOINABLE), camera(std::move(camera)),
      ccExtraModel(ccExtraModel) {
    this->parent = parent;
}

ColorCalibPreviewThread::~ColorCalibPreviewThread() {}

wxThread::ExitCode ColorCalibPreviewThread::Entry() {

    wxCommandEvent startCaptureEvent(c_CAPTURE_EVENT, CAPTURE_START);
    wxPostEvent(parent, startCaptureEvent);

    try {
        while (!TestDestroy()) {
            cv::Mat frame;
            camera->getFrame(frame);

            if (frame.empty()) {
                std::cout << "Failed to capture frame" << std::endl;
                continue;
            }

            UpdatePreviewEvent::Submit(parent, frame);
        }
    } catch (const std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }

    UpdatePreviewEvent clearPreviewEvent(c_UPDATE_PREVIEW_EVENT, CLEAR_PREVIEW);
    wxPostEvent(parent, clearPreviewEvent);

    wxCommandEvent endCaptureEvent(c_CAPTURE_EVENT, CAPTURE_END);
    wxPostEvent(parent, endCaptureEvent);

    return 0;
}

std::unique_ptr<CameraBase> ColorCalibPreviewThread::getCamera() {
    return std::move(camera);
}

ThreadID ColorCalibPreviewThread::getID() const { return id; }