#include "Event/Event_Calibration.hpp"
#include <Thread/Thread_Calibration.hpp>

CalibrationThread::CalibrationThread(wxEvtHandler *parent,
                                     std::unique_ptr<CameraBase> &camera)
    : wxThread(wxTHREAD_JOINABLE), camera(std::move(camera)) {
    this->parent = parent;
}

CalibrationThread::~CalibrationThread() {}

wxThread::ExitCode CalibrationThread::Entry() {

    wxCommandEvent startCalibrationEvent(c_CALIBRATION_EVENT,
                                         CALIBRATION_START);
    wxPostEvent(parent, startCalibrationEvent);

    while (!TestDestroy()) {
        cv::Mat frame;
        camera->getFrame(frame);

        if (frame.empty()) {
            std::cout << "Failed to capture frame" << std::endl;
            continue;
        }

        cv::Size s(320, 240);
        cv::resize(frame, frame, s);

        UpdatePreviewEvent updatePreviewEvent(c_UPDATE_PREVIEW_EVENT,
                                              UPDATE_PREVIEW);
        updatePreviewEvent.SetImage(frame);
        wxPostEvent(parent, updatePreviewEvent);
    }

    UpdatePreviewEvent clearPreviewEvent(c_UPDATE_PREVIEW_EVENT, CLEAR_PREVIEW);
    wxPostEvent(parent, clearPreviewEvent);

    wxCommandEvent endCalibrationEvent(c_CALIBRATION_EVENT, CALIBRATION_END);
    wxPostEvent(parent, endCalibrationEvent);
    return 0;
}

std::unique_ptr<CameraBase> CalibrationThread::getCamera() {
    return std::move(camera);
}